import streamlit as st
import subprocess
import json
import os
import time
import re

# Page configuration
st.set_page_config(
    page_title="Mini C Compiler & Block Visualizer",
    page_icon="🎬",
    layout="wide",
    initial_sidebar_state="expanded"
)

# Custom CSS for beautiful styling
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
    
    .block-function {
        background: linear-gradient(135deg, #f093fb 0%, #f5576c 100%);
        color: white;
    }
    
    .block-if {
        background: linear-gradient(135deg, #4facfe 0%, #00f2fe 100%);
        color: white;
    }
    
    .block-while {
        background: linear-gradient(135deg, #43e97b 0%, #38f9d7 100%);
        color: white;
    }
    
    .block-for {
        background: linear-gradient(135deg, #fa709a 0%, #fee140 100%);
        color: white;
    }
    
    .block-return {
        background: linear-gradient(135deg, #30cfd0 0%, #330867 100%);
        color: white;
    }
    
    .block-assignment {
        background: linear-gradient(135deg, #a8edea 0%, #fed6e3 100%);
        color: #333;
    }
    
    .block-print {
        background: linear-gradient(135deg, #ff9a9e 0%, #fecfef 100%);
        color: #333;
    }
    
    .block-declaration {
        background: linear-gradient(135deg, #ffecd2 0%, #fcb69f 100%);
        color: #333;
    }
    
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
    
    .nested-1 {
        margin-left: 30px;
    }
    
    .nested-2 {
        margin-left: 60px;
    }
    
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

# Helper function to parse code into blocks - DEFINE BEFORE USE
def parse_code_to_blocks(code):
    """Parse C code into visual blocks"""
    blocks = []
    lines = code.split('\n')
    nest_level = 0
    
    for line in lines:
        line_stripped = line.strip()
        if not line_stripped or line_stripped.startswith('//'):
            continue
        
        # Function declaration
        if re.match(r'^(int|void|float)\s+\w+\s*\([^)]*\)\s*\{?', line_stripped):
            match = re.match(r'^(int|void|float)\s+(\w+)', line_stripped)
            func_name = match.group(2) if match else 'function'
            blocks.append({
                'type': 'function',
                'text': f'📦 Function: {func_name}()',
                'explanation': f'This starts the {func_name} function. Functions are like machines that do specific jobs!',
                'nest_level': 0,
                'icon': '📦'
            })
            if '{' in line_stripped:
                nest_level += 1
            continue
        
        # If statement
        if re.match(r'^if\s*\(', line_stripped):
            condition = re.search(r'if\s*\(([^)]+)\)', line_stripped)
            cond_text = condition.group(1) if condition else '...'
            blocks.append({
                'type': 'if',
                'text': f'🔀 If ({cond_text})',
                'explanation': 'Check if the condition is true. If yes, do what\'s inside!',
                'nest_level': nest_level,
                'icon': '🔀'
            })
            if '{' in line_stripped:
                nest_level += 1
            continue
        
        # Else statement
        if re.match(r'^else', line_stripped):
            blocks.append({
                'type': 'if',
                'text': '🔄 Else',
                'explanation': 'If the condition above was false, do this instead!',
                'nest_level': max(0, nest_level - 1),
                'icon': '🔄'
            })
            if '{' in line_stripped:
                nest_level += 1
            continue
        
        # While loop
        if re.match(r'^while\s*\(', line_stripped):
            condition = re.search(r'while\s*\(([^)]+)\)', line_stripped)
            cond_text = condition.group(1) if condition else '...'
            blocks.append({
                'type': 'while',
                'text': f'🔄 While ({cond_text})',
                'explanation': 'Keep repeating as long as this condition is true!',
                'nest_level': nest_level,
                'icon': '🔄'
            })
            if '{' in line_stripped:
                nest_level += 1
            continue
        
        # For loop
        if re.match(r'^for\s*\(', line_stripped):
            blocks.append({
                'type': 'for',
                'text': '🔁 For loop',
                'explanation': 'Repeat a specific number of times!',
                'nest_level': nest_level,
                'icon': '🔁'
            })
            if '{' in line_stripped:
                nest_level += 1
            continue
        
        # Return statement
        if re.match(r'^return', line_stripped):
            value = re.search(r'return\s+([^;]+)', line_stripped)
            val_text = value.group(1) if value else ''
            blocks.append({
                'type': 'return',
                'text': f'↩️ Return {val_text}',
                'explanation': 'Send this value back and exit the function!',
                'nest_level': nest_level,
                'icon': '↩️'
            })
            continue
        
        # Variable declaration
        if re.match(r'^(int|float|char)\s+\w+', line_stripped):
            match = re.search(r'^(int|float|char)\s+(\w+)', line_stripped)
            var_name = match.group(2) if match else 'var'
            blocks.append({
                'type': 'declaration',
                'text': f'📝 Create variable: {var_name}',
                'explanation': 'Make a new box to store a value!',
                'nest_level': nest_level,
                'icon': '📝'
            })
            continue
        
        # Assignment
        if re.match(r'^\w+\s*=', line_stripped):
            match = re.search(r'^(\w+)\s*=\s*([^;]+)', line_stripped)
            if match:
                var_name = match.group(1)
                value = match.group(2)
                blocks.append({
                    'type': 'assignment',
                    'text': f'✏️ {var_name} = {value}',
                    'explanation': 'Put a value into the variable box!',
                    'nest_level': nest_level,
                    'icon': '✏️'
                })
            continue
        
        # Printf
        if 'printf' in line_stripped:
            blocks.append({
                'type': 'print',
                'text': '🖨️ Print to screen',
                'explanation': 'Show something on the screen!',
                'nest_level': nest_level,
                'icon': '🖨️'
            })
            continue
        
        # Closing brace
        if line_stripped == '}':
            nest_level = max(0, nest_level - 1)
    
    return blocks

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
    <h1>🎬 Mini C Compiler & Block Visualizer</h1>
    <p style="font-size: 1.2rem;">Learn C programming visually, just like Scratch!</p>
</div>
""", unsafe_allow_html=True)

# Sidebar - Code Input and Controls
with st.sidebar:
    st.header("📝 Your C Code")
    
    # File uploader
    uploaded_file = st.file_uploader("Upload C file", type=["c"])
    
    # Code editor
    default_code = """int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int result;
    result = factorial(5);
    printf("Factorial = %d\\n", result);
    return 0;
}"""
    
    code_input = st.text_area(
        "Or type your code here:",
        height=300,
        value=default_code
    )
    
    # Save code to file
    temp_code_file = "temp_code.c"
    if uploaded_file:
        with open(temp_code_file, "wb") as f:
            f.write(uploaded_file.getbuffer())
    elif code_input:
        with open(temp_code_file, "w") as f:
            f.write(code_input)
    
    st.markdown("---")
    
    # Action buttons
    col1, col2 = st.columns(2)
    
    with col1:
        if st.button("🚀 Load Blocks", use_container_width=True):
            st.session_state.blocks = parse_code_to_blocks(code_input)
            st.session_state.current_step = 0
            st.session_state.is_playing = False
            st.session_state.code_loaded = True
            st.rerun()
    
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
    
    # Display run output if available
    if 'run_output' in st.session_state:
        st.markdown("---")
        st.subheader("📤 Output")
        st.code(st.session_state.run_output, language="text")
        if st.session_state.run_errors:
            st.subheader("⚠️ Errors")
            st.code(st.session_state.run_errors, language="text")

# Main content area
if st.session_state.code_loaded and st.session_state.blocks:
    # Control panel
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
        speed = st.slider("⚡ Speed (ms)", 100, 2000, 800, 100, label_visibility="collapsed")
    
    # Progress bar
    progress = (st.session_state.current_step + 1) / len(st.session_state.blocks)
    st.progress(progress, text=f"Step {st.session_state.current_step + 1} / {len(st.session_state.blocks)}")
    
    # Auto-play logic
    if st.session_state.is_playing:
        if st.session_state.current_step < len(st.session_state.blocks) - 1:
            time.sleep(speed / 1000)
            st.session_state.current_step += 1
            st.rerun()
        else:
            st.session_state.is_playing = False
            st.rerun()
    
    st.markdown("---")
    
    # Two column layout
    col_left, col_right = st.columns([2, 1])
    
    with col_left:
        st.markdown("### 🎨 Code Blocks")
        
        # Display blocks
        for idx, block in enumerate(st.session_state.blocks):
            status_class = ""
            if idx == st.session_state.current_step:
                status_class = "block-executing"
            elif idx < st.session_state.current_step:
                status_class = "block-executed"
            
            nest_class = f"nested-{min(block['nest_level'], 2)}" if block['nest_level'] > 0 else ""
            
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
            <h3>{current_block['icon']} {current_block['type'].title()}</h3>
            <p>{current_block['explanation']}</p>
        </div>
        """, unsafe_allow_html=True)
        
        st.markdown("### 📊 Stats")
        st.markdown(f"""
        <div class="stats-box">
            Total Blocks: {len(st.session_state.blocks)}<br>
            Executed: {st.session_state.current_step}<br>
            Remaining: {len(st.session_state.blocks) - st.session_state.current_step - 1}
        </div>
        """, unsafe_allow_html=True)
        
        st.markdown("### 🎨 Block Types")
        st.markdown("""
        - 📦 **Function** (Pink)
        - 🔀 **If/Else** (Blue)
        - 🔄 **While** (Green)
        - 🔁 **For** (Orange)
        - ↩️ **Return** (Purple)
        - ✏️ **Assignment** (Light Blue)
        - 🖨️ **Print** (Pink)
        - 📝 **Declaration** (Peach)
        """)

else:
    # Welcome screen
    st.markdown("""
    <div style="text-align: center; padding: 3rem;">
        <h2>👋 Welcome to the Block Visualizer!</h2>
        <p style="font-size: 1.2rem; margin: 2rem 0;">
            This tool helps you understand C code by showing it as colorful blocks,
            just like Scratch programming!
        </p>
        <p style="font-size: 1.1rem; color: #666;">
            👈 Enter your C code in the sidebar and click <strong>"Load Blocks"</strong> to start!
        </p>
    </div>
    """, unsafe_allow_html=True)
    
    # Example showcase
    col1, col2, col3 = st.columns(3)
    
    with col1:
        st.markdown("""
        <div class="block-item block-function">
            📦 Function: main()
        </div>
        """, unsafe_allow_html=True)
        st.caption("Functions are the building blocks of your program")
    
    with col2:
        st.markdown("""
        <div class="block-item block-if">
            🔀 If (x > 5)
        </div>
        """, unsafe_allow_html=True)
        st.caption("Make decisions in your code")
    
    with col3:
        st.markdown("""
        <div class="block-item block-while">
            🔄 While (count < 10)
        </div>
        """, unsafe_allow_html=True)
        st.caption("Repeat code multiple times")

# Footer
st.markdown("---")
st.markdown("""
<div style="text-align: center; color: #666; padding: 1rem;">
    Made with ❤️ for learning C programming | 🎬 Block Visualizer v1.0
</div>
""", unsafe_allow_html=True)