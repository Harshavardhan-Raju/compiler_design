import streamlit as st
import subprocess
import json
import os
import time

# Page configuration
st.set_page_config(
    page_title="C Execution Flow Visualizer",
    page_icon="🎬",
    layout="wide",
    initial_sidebar_state="expanded"
)

# Custom CSS
st.markdown("""
<style>
    .main-header {
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        padding: 2rem;
        border-radius: 15px;
        text-align: center;
        color: white;
        margin-bottom: 2rem;
    }
    
    .block-item {
        padding: 1rem;
        border-radius: 10px;
        margin: 0.5rem 0;
        font-weight: bold;
        box-shadow: 0 4px 6px rgba(0,0,0,0.1);
        transition: all 0.3s;
    }
    
    .block-start { background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%); color: white; }
    .block-call { background: linear-gradient(135deg, #a18cd1 0%, #fbc2eb 100%); color: white; }
    .block-enter { background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; }
    .block-condition { background: linear-gradient(135deg, #4facfe 0%, #00f2fe 100%); color: white; }
    .block-statement { background: linear-gradient(135deg, #a8edea 0%, #fed6e3 100%); color: #333; }
    .block-return { background: linear-gradient(135deg, #30cfd0 0%, #330867 100%); color: white; }
    .block-exit { background: linear-gradient(135deg, #fa709a 0%, #fee140 100%); color: white; }
    .block-end { background: linear-gradient(135deg, #43e97b 0%, #38f9d7 100%); color: white; }
    
    .block-executing {
        border: 4px solid gold;
        animation: pulse 1s infinite;
        transform: scale(1.05);
        box-shadow: 0 0 20px rgba(255, 215, 0, 0.8) !important;
    }
    
    .block-executed {
        opacity: 0.5;
        filter: brightness(0.7);
    }
    
    @keyframes pulse {
        0%, 100% { transform: scale(1.05); }
        50% { transform: scale(1.1); }
    }
    
    .nested-1 { margin-left: 30px; }
    .nested-2 { margin-left: 60px; }
    .nested-3 { margin-left: 90px; }
    .nested-4 { margin-left: 120px; }
    .nested-5 { margin-left: 150px; }
    
    .explanation-box {
        background: #fff3cd;
        border: 3px solid #ffc107;
        border-radius: 10px;
        padding: 1.5rem;
        font-size: 1.1rem;
        margin: 1rem 0;
    }
    
    .stats-box {
        background: #d1ecf1;
        border: 2px solid #0c5460;
        color: #0c5460;
        padding: 1rem;
        border-radius: 10px;
        text-align: center;
        font-weight: bold;
    }
</style>
""", unsafe_allow_html=True)

# AST-based execution tracer
class ExecutionTracer:
    def __init__(self):
        self.trace = []
        self.depth = 0
        self.variables = {}
        
    def add_trace(self, trace_type, text, explanation):
        self.trace.append({
            'type': trace_type,
            'text': text,
            'explanation': explanation,
            'depth': self.depth
        })
    
    def trace_ast(self, ast):
        """Trace execution from AST"""
        if not ast:
            return
        
        # Start at Program node
        if ast.get('type') == 'Program':
            self.add_trace('start', '🎬 Program Start', 'Program execution begins')
            
            # Find main function in children
            if 'children' in ast:
                for child in ast['children']:
                    if child.get('type') == 'CompoundStmt':
                        # This is the declaration list
                        main_func = self.find_main(child)
                        if main_func:
                            self.trace_function_call('main', main_func, [])
            
            self.add_trace('end', '🏁 Program End', 'Program execution complete')
    
    def find_main(self, decl_list):
        """Find main function in declaration list"""
        if decl_list.get('type') == 'CompoundStmt' and 'children' in decl_list:
            for child in decl_list['children']:
                if child.get('type') == 'FunctionDecl' and child.get('name') == 'main':
                    return child
        return None
    
    def find_function(self, ast, func_name):
        """Find function definition by name"""
        if ast.get('type') == 'Program' and 'children' in ast:
            for child in ast['children']:
                if child.get('type') == 'CompoundStmt' and 'children' in child:
                    for decl in child['children']:
                        if decl.get('type') == 'FunctionDecl' and decl.get('name') == func_name:
                            return decl
        return None
    
    def trace_function_call(self, func_name, func_node, args):
        """Trace a function call"""
        self.add_trace('enter', f'📦 Enter {func_name}()', f'Starting execution of {func_name} function')
        self.depth += 1
        
        # Get function body (last child is usually the body)
        if 'children' in func_node and len(func_node['children']) > 0:
            body = func_node['children'][-1]  # Last child is body
            if body.get('type') == 'CompoundStmt':
                result = self.trace_compound_stmt(body)
                self.depth -= 1
                self.add_trace('exit', f'🚪 Exit {func_name}()', f'Returning from {func_name}')
                return result
        
        self.depth -= 1
        self.add_trace('exit', f'🚪 Exit {func_name}()', f'Returning from {func_name}')
        return None
    
    def trace_compound_stmt(self, node):
        """Trace compound statement (block of code)"""
        if 'children' not in node:
            return None
        
        for stmt in node['children']:
            result = self.trace_statement(stmt)
            if result is not None and result.get('return'):
                return result
        return None
    
    def trace_statement(self, node):
        """Trace individual statement"""
        stmt_type = node.get('type')
        
        if stmt_type == 'VarDecl':
            var_name = node.get('name', 'var')
            self.add_trace('statement', f'📝 Declare: {var_name}', 
                          f'Create variable "{var_name}"')
            return None
        
        elif stmt_type == 'Assignment':
            if 'children' in node and len(node['children']) >= 2:
                var_node = node['children'][0]
                expr_node = node['children'][1]
                var_name = var_node.get('name', 'var')
                
                # Try to evaluate expression
                value_str = self.expr_to_string(expr_node)
                self.add_trace('statement', f'✏️ {var_name} = {value_str}',
                              f'Assign value to {var_name}')
            return None
        
        elif stmt_type == 'IfStmt':
            if 'children' in node and len(node['children']) >= 1:
                condition = node['children'][0]
                cond_str = self.expr_to_string(condition)
                self.add_trace('condition', f'🔀 if ({cond_str})', 
                              f'Check condition: {cond_str}')
                
                # Trace then branch
                if len(node['children']) >= 2:
                    self.depth += 1
                    self.trace_statement(node['children'][1])
                    self.depth -= 1
                
                # Trace else branch if exists
                if len(node['children']) >= 3:
                    self.add_trace('condition', f'🔄 else', 'Execute else branch')
                    self.depth += 1
                    self.trace_statement(node['children'][2])
                    self.depth -= 1
            return None
        
        elif stmt_type == 'WhileStmt':
            if 'children' in node and len(node['children']) >= 2:
                condition = node['children'][0]
                body = node['children'][1]
                cond_str = self.expr_to_string(condition)
                self.add_trace('condition', f'🔄 while ({cond_str})',
                              f'Loop while {cond_str} is true')
                self.depth += 1
                self.trace_statement(body)
                self.depth -= 1
            return None
        
        elif stmt_type == 'ReturnStmt':
            if 'children' in node and len(node['children']) > 0:
                expr = node['children'][0]
                value_str = self.expr_to_string(expr)
                self.add_trace('return', f'↩️ return {value_str}',
                              f'Return value: {value_str}')
            else:
                self.add_trace('return', f'↩️ return', 'Return from function')
            return {'return': True}
        
        elif stmt_type == 'ExprStmt':
            if 'children' in node:
                for child in node['children']:
                    self.trace_statement(child)
            return None
        
        elif stmt_type == 'PrintStmt':
            if 'children' in node and len(node['children']) > 0:
                format_node = node['children'][0]
                format_str = format_node.get('name', 'output')
                self.add_trace('statement', f'🖨️ printf("{format_str}")',
                              'Print output to screen')
            return None
        
        elif stmt_type == 'FuncCall':
            func_name = node.get('name', 'function')
            
            # Get arguments
            args = []
            if 'children' in node and len(node['children']) > 0:
                arg_list = node['children'][0]
                if arg_list.get('type') == 'CompoundStmt' and 'children' in arg_list:
                    args = [self.expr_to_string(arg) for arg in arg_list['children']]
            
            args_str = ', '.join(args) if args else ''
            self.add_trace('call', f'📞 Call {func_name}({args_str})',
                          f'Calling function {func_name}')
            
            # Note: In a real interpreter, we'd recursively call the function here
            # For now, we just show the call
            return None
        
        elif stmt_type == 'CompoundStmt':
            return self.trace_compound_stmt(node)
        
        return None
    
    def expr_to_string(self, node):
        """Convert expression AST to string"""
        if not node:
            return ''
        
        node_type = node.get('type')
        
        if node_type == 'IntLiteral':
            return str(node.get('value', 0))
        
        elif node_type == 'FloatLiteral':
            return str(node.get('value', 0.0))
        
        elif node_type == 'Identifier':
            return node.get('name', 'var')
        
        elif node_type == 'BinaryOp':
            if 'children' in node and len(node['children']) >= 2:
                left = self.expr_to_string(node['children'][0])
                right = self.expr_to_string(node['children'][1])
                op = node.get('operator', '?')
                return f'{left} {op} {right}'
        
        elif node_type == 'UnaryOp':
            if 'children' in node and len(node['children']) > 0:
                operand = self.expr_to_string(node['children'][0])
                op = node.get('operator', '?')
                return f'{op}{operand}'
        
        elif node_type == 'FuncCall':
            func_name = node.get('name', 'func')
            if 'children' in node and len(node['children']) > 0:
                arg_list = node['children'][0]
                if arg_list.get('type') == 'CompoundStmt' and 'children' in arg_list:
                    args = [self.expr_to_string(arg) for arg in arg_list['children']]
                    return f'{func_name}({", ".join(args)})'
            return f'{func_name}()'
        
        return '???'

# Initialize session state
if 'blocks' not in st.session_state:
    st.session_state.blocks = []
if 'current_step' not in st.session_state:
    st.session_state.current_step = 0
if 'is_playing' not in st.session_state:
    st.session_state.is_playing = False
if 'code_loaded' not in st.session_state:
    st.session_state.code_loaded = False

# Header
st.markdown("""
<div class="main-header">
    <h1>🎬 C Code Execution Flow Visualizer</h1>
    <p style="font-size: 1.2rem;">AST-based execution trace from your compiler!</p>
</div>
""", unsafe_allow_html=True)

# Sidebar
with st.sidebar:
    st.header("📝 Your C Code")
    
    uploaded_file = st.file_uploader("Upload C file", type=["c"])
    
    default_code = """int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int result;
    result = factorial(5);
    printf("Result = %d\\n", result);
    return 0;
}"""
    
    code_input = st.text_area(
        "Or type your code here:",
        height=300,
        value=default_code
    )
    
    temp_code_file = "temp_code.c"
    if uploaded_file:
        with open(temp_code_file, "wb") as f:
            f.write(uploaded_file.getbuffer())
    elif code_input:
        with open(temp_code_file, "w") as f:
            f.write(code_input)
    
    st.markdown("---")
    
    col1, col2 = st.columns(2)
    
    with col1:
        if st.button("🚀 Trace Flow", use_container_width=True):
            if not os.path.exists("./mycc"):
                st.error("⚠️ Compiler not found!")
            else:
                try:
                    # Generate AST
                    result = subprocess.run(
                        ["./mycc", "-a", temp_code_file],
                        stdout=subprocess.PIPE,
                        stderr=subprocess.PIPE,
                        text=True,
                        check=True
                    )
                    
                    # Parse AST
                    ast = json.loads(result.stdout)
                    
                    # Trace execution
                    tracer = ExecutionTracer()
                    tracer.trace_ast(ast)
                    
                    st.session_state.blocks = tracer.trace
                    st.session_state.current_step = 0
                    st.session_state.is_playing = False
                    st.session_state.code_loaded = True
                    
                    st.success(f"✅ Traced {len(tracer.trace)} execution steps!")
                    st.rerun()
                    
                except subprocess.CalledProcessError as e:
                    st.error(f"Compilation error: {e}")
                except json.JSONDecodeError as e:
                    st.error(f"AST parse error: {e}")
                except Exception as e:
                    st.error(f"Error: {e}")
    
    with col2:
        if st.button("▶️ Run Code", use_container_width=True):
            if os.path.exists("./mycc"):
                result = subprocess.run(
                    ["./mycc", "-i", temp_code_file],
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE,
                    text=True
                )
                st.session_state.run_output = result.stdout
                st.session_state.run_errors = result.stderr
            else:
                st.error("⚠️ Compiler not found!")
    
    if 'run_output' in st.session_state:
        st.markdown("---")
        st.subheader("📤 Output")
        st.code(st.session_state.run_output, language="text")
        if st.session_state.run_errors:
            st.subheader("⚠️ Errors")
            st.code(st.session_state.run_errors, language="text")

# Main content
if st.session_state.code_loaded and st.session_state.blocks:
    st.markdown("### 🎮 Playback Controls")
    
    col1, col2, col3, col4, col5 = st.columns([1, 1, 1, 1, 2])
    
    with col1:
        if st.button("⏮️ Reset", use_container_width=True):
            st.session_state.current_step = 0
            st.session_state.is_playing = False
            st.rerun()
    
    with col2:
        if st.button("⏪ Previous", use_container_width=True, 
                     disabled=(st.session_state.current_step == 0)):
            st.session_state.current_step = max(0, st.session_state.current_step - 1)
            st.session_state.is_playing = False
            st.rerun()
    
    with col3:
        play_label = "⏸️ Pause" if st.session_state.is_playing else "▶️ Play"
        if st.button(play_label, use_container_width=True):
            st.session_state.is_playing = not st.session_state.is_playing
            st.rerun()
    
    with col4:
        if st.button("⏩ Next", use_container_width=True,
                     disabled=(st.session_state.current_step >= len(st.session_state.blocks) - 1)):
            st.session_state.current_step = min(len(st.session_state.blocks) - 1, 
                                                st.session_state.current_step + 1)
            st.session_state.is_playing = False
            st.rerun()
    
    with col5:
        speed = st.slider("⚡ Speed (ms)", 100, 2000, 1000, 100, label_visibility="collapsed")
    
    progress = (st.session_state.current_step + 1) / len(st.session_state.blocks)
    st.progress(progress, text=f"Step {st.session_state.current_step + 1} / {len(st.session_state.blocks)}")
    
    if st.session_state.is_playing:
        if st.session_state.current_step < len(st.session_state.blocks) - 1:
            time.sleep(speed / 1000)
            st.session_state.current_step += 1
            st.rerun()
        else:
            st.session_state.is_playing = False
            st.rerun()
    
    st.markdown("---")
    
    col_left, col_right = st.columns([2, 1])
    
    with col_left:
        st.markdown("### 🎨 Execution Trace (From AST)")
        
        for idx, block in enumerate(st.session_state.blocks):
            status_class = ""
            if idx == st.session_state.current_step:
                status_class = "block-executing"
            elif idx < st.session_state.current_step:
                status_class = "block-executed"
            
            nest_class = f"nested-{min(block['depth'], 5)}"
            
            st.markdown(f"""
            <div class="block-item block-{block['type']} {status_class} {nest_class}">
                {block['text']}
            </div>
            """, unsafe_allow_html=True)
    
    with col_right:
        st.markdown("### 💡 Current Step")
        
        current_block = st.session_state.blocks[st.session_state.current_step]
        
        st.markdown(f"""
        <div class="explanation-box">
            <h3>Step {st.session_state.current_step + 1}</h3>
            <p>{current_block['explanation']}</p>
        </div>
        """, unsafe_allow_html=True)
        
        st.markdown("### 📊 Stats")
        st.markdown(f"""
        <div class="stats-box">
            Depth: {current_block['depth']}<br>
            Step: {st.session_state.current_step + 1} / {len(st.session_state.blocks)}<br>
            Progress: {int(progress * 100)}%
        </div>
        """, unsafe_allow_html=True)

else:
    st.markdown("""
    <div style="text-align: center; padding: 3rem;">
        <h2>👋 Welcome!</h2>
        <p style="font-size: 1.2rem; margin: 2rem 0;">
            This visualizer traces execution flow from your compiler's AST!
        </p>
        <p style="font-size: 1.1rem; color: #666;">
            👈 Click <strong>"Trace Flow"</strong> to see how your code executes!
        </p>
    </div>
    """, unsafe_allow_html=True)

st.markdown("---")
st.markdown("""
<div style="text-align: center; color: #666; padding: 1rem;">
    🎬 AST-Based Execution Visualizer - Powered by your compiler!
</div>
""", unsafe_allow_html=True)