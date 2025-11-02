from flask import Flask, render_template, request, jsonify
import subprocess
import tempfile
import os
import json
from pathlib import Path

app = Flask(__name__)

# Configuration
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
MYCC_PATH = os.path.join(BASE_DIR, "mycc")
TIMEOUT = 10

@app.route('/')
def index():
    """Serve the main HTML page"""
    return render_template('index.html')

@app.route('/compile', methods=['POST'])
def compile_code():
    """Compile and run C code with input"""
    try:
        data = request.get_json()
        code = data.get('code', '')
        user_input = data.get('input', '')
        
        if not code:
            return jsonify({
                'success': False,
                'output': '',
                'errors': 'No code provided',
                'returncode': 1
            })
        
        with tempfile.NamedTemporaryFile(mode='w', suffix='.c', delete=False) as tmp:
            tmp.write(code)
            tmp_path = tmp.name
        
        try:
            process = subprocess.Popen(
                [MYCC_PATH, '-i', tmp_path],
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            
            stdout, stderr = process.communicate(input=user_input, timeout=TIMEOUT)
            returncode = process.returncode
            
            return jsonify({
                'success': returncode == 0,
                'output': stdout,
                'errors': stderr,
                'returncode': returncode
            })
            
        except subprocess.TimeoutExpired:
            process.kill()
            return jsonify({
                'success': False,
                'output': '',
                'errors': f'Execution timed out after {TIMEOUT} seconds',
                'returncode': -1
            })
        finally:
            os.unlink(tmp_path)
            
    except Exception as e:
        return jsonify({
            'success': False,
            'output': '',
            'errors': f'Server error: {str(e)}',
            'returncode': -1
        })

@app.route('/visualize', methods=['POST'])
def visualize_ast():
    """Generate AST visualization with execution flow"""
    try:
        data = request.get_json()
        code = data.get('code', '')
        
        if not code:
            return jsonify({
                'success': False,
                'error': 'No code provided'
            })
        
        with tempfile.NamedTemporaryFile(mode='w', suffix='.c', delete=False) as tmp:
            tmp.write(code)
            tmp_path = tmp.name
        
        try:
            process = subprocess.Popen(
                [MYCC_PATH, '-a', tmp_path],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            
            stdout, stderr = process.communicate(timeout=TIMEOUT)
            
            if process.returncode != 0:
                return jsonify({
                    'success': False,
                    'error': stderr or 'Failed to parse AST'
                })
            
            try:
                ast_data = json.loads(stdout)
                
                # Generate execution flow from AST
                execution_steps = generate_execution_flow(ast_data)
                
                return jsonify({
                    'success': True,
                    'ast': ast_data,
                    'execution_steps': execution_steps
                })
            except json.JSONDecodeError as e:
                return jsonify({
                    'success': False,
                    'error': f'Invalid JSON output: {str(e)}'
                })
            
        except subprocess.TimeoutExpired:
            process.kill()
            return jsonify({
                'success': False,
                'error': f'AST generation timed out after {TIMEOUT} seconds'
            })
        finally:
            os.unlink(tmp_path)
            
    except Exception as e:
        return jsonify({
            'success': False,
            'error': f'Server error: {str(e)}'
        })

def generate_execution_flow(ast_node):
    """
    Generate step-by-step execution flow from AST
    Returns a list of execution steps with proper control flow
    """
    steps = []
    step_id = [0]  # Use list to allow modification in nested functions
    call_stack = []
    all_functions = {}
    MAX_RECURSION_DEPTH = 10
    MAX_STEPS = 200
    
    def add_step(step_type, function, description, depth=0, callee=None):
        if step_id[0] >= MAX_STEPS:
            return
        steps.append({
            'id': step_id[0],
            'type': step_type,
            'function': function,
            'callee': callee,
            'description': description,
            'stack': [frame.copy() for frame in call_stack],
            'depth': depth
        })
        step_id[0] += 1
    
    def collect_functions(node):
        """Collect all function definitions"""
        if not node or not isinstance(node, dict):
            return
        
        if node.get('type') == 'Program' and 'children' in node:
            decl_list = node['children'][0] if node['children'] else None
            if decl_list and 'children' in decl_list:
                for child in decl_list['children']:
                    if child.get('type') == 'FunctionDecl' and 'name' in child:
                        all_functions[child['name']] = child
    
    def process_expression(node, current_func, depth=0):
        """Process expressions, handling function calls"""
        if not node or not isinstance(node, dict):
            return
        
        if step_id[0] >= MAX_STEPS:
            return
        
        # Handle function calls - MOST IMPORTANT
        if node.get('type') == 'FuncCall':
            func_name = node.get('name', 'unknown')
            
            if depth >= MAX_RECURSION_DEPTH:
                add_step('warning', current_func, 
                        f'⚠️ Max recursion depth reached for {func_name}()', 
                        depth, func_name)
                return
            
            # Step 1: Call function
            add_step('function_call', current_func,
                    f'→ Calling {func_name}() (depth: {depth + 1})',
                    depth, func_name)
            
            # Step 2: Enter function
            call_stack.append({'func': func_name, 'depth': depth + 1})
            add_step('function_enter', func_name,
                    f'▶ Enter {func_name}()',
                    depth + 1)
            
            # Step 3: Execute function body
            if func_name in all_functions:
                func_def = all_functions[func_name]
                if 'children' in func_def and len(func_def['children']) >= 2:
                    body = func_def['children'][1]
                    if 'children' in body:
                        for stmt in body['children']:
                            if step_id[0] >= MAX_STEPS:
                                break
                            process_statement(stmt, func_name, depth + 1)
            
            # Step 4: Exit function
            add_step('function_exit', func_name,
                    f'◀ Exit {func_name}()',
                    depth + 1)
            
            if call_stack:
                call_stack.pop()
            
            # Step 5: Return to caller
            add_step('function_return', current_func,
                    f'← Back to {current_func}() from {func_name}()',
                    depth, func_name)
            return
        
        # Handle binary operations
        if node.get('type') == 'BinaryOp':
            children = node.get('children', [])
            for child in children:
                process_expression(child, current_func, depth)
            return
        
        # Handle unary operations
        if node.get('type') == 'UnaryOp':
            children = node.get('children', [])
            for child in children:
                process_expression(child, current_func, depth)
            return
        
        # Recursively process children
        if 'children' in node:
            for child in node['children']:
                if step_id[0] >= MAX_STEPS:
                    break
                process_expression(child, current_func, depth)
    
    def process_statement(node, current_func, depth=0):
        """Process statements in order"""
        if not node or not isinstance(node, dict):
            return
        
        if step_id[0] >= MAX_STEPS:
            return
        
        node_type = node.get('type')
        
        if node_type == 'VarDecl':
            var_name = node.get('name', 'var')
            has_init = 'children' in node and len(node['children']) > 0
            
            add_step('var_decl', current_func,
                    f'Declare: int {var_name}{"= ..." if has_init else ""}',
                    depth)
            
            if has_init:
                process_expression(node['children'][0], current_func, depth)
                add_step('assignment', current_func,
                        f'Assign value to {var_name}',
                        depth)
        
        elif node_type == 'Assignment' or node_type == 'Assign':
            add_step('assignment', current_func, 'Assignment operation', depth)
            if 'children' in node and len(node['children']) > 1:
                process_expression(node['children'][1], current_func, depth)
        
        elif node_type == 'IfStmt':
            add_step('condition', current_func, 'Evaluate if condition', depth)
            
            children = node.get('children', [])
            if children:
                # Process condition
                process_expression(children[0], current_func, depth)
                
                # Process branches (simplified - just show structure)
                add_step('condition', current_func,
                        'Check condition result',
                        depth)
                
                # Process then/else branches
                for child in children[1:]:
                    process_statement(child, current_func, depth)
        
        elif node_type == 'WhileStmt':
            add_step('loop', current_func, 'While loop', depth)
            children = node.get('children', [])
            if len(children) >= 2:
                process_expression(children[0], current_func, depth)
                # Note: Not fully executing loop body to avoid infinite loops
        
        elif node_type == 'ForStmt':
            add_step('loop', current_func, 'For loop', depth)
            # Simplified - just show structure
        
        elif node_type == 'ReturnStmt':
            children = node.get('children', [])
            if children:
                add_step('eval', current_func, 'Evaluate return expression', depth)
                process_expression(children[0], current_func, depth)
            
            add_step('return', current_func,
                    f'⏎ Return from {current_func}()',
                    depth)
        
        elif node_type == 'PrintStmt':
            add_step('print', current_func, 'Execute printf()', depth)
            children = node.get('children', [])
            if len(children) > 1:
                process_expression(children[1], current_func, depth)
        
        elif node_type == 'ScanStmt':
            add_step('scan', current_func, 'Execute scanf()', depth)
        
        elif node_type == 'ExprStmt':
            if 'children' in node:
                for child in node['children']:
                    if step_id[0] >= MAX_STEPS:
                        break
                    process_expression(child, current_func, depth)
        
        elif node_type == 'CompoundStmt':
            if 'children' in node:
                for child in node['children']:
                    if step_id[0] >= MAX_STEPS:
                        break
                    process_statement(child, current_func, depth)
        
        else:
            # For other node types, recursively process children
            if 'children' in node:
                for child in node['children']:
                    if step_id[0] >= MAX_STEPS:
                        break
                    process_statement(child, current_func, depth)
    
    # Main execution starts here
    collect_functions(ast_node)
    
    # Find and execute main
    if 'main' in all_functions:
        call_stack.append({'func': 'main', 'depth': 0})
        add_step('function_enter', 'main',
                '🚀 Program starts - entering main()',
                0)
        
        main_func = all_functions['main']
        if 'children' in main_func and len(main_func['children']) >= 2:
            body = main_func['children'][1]
            if 'children' in body:
                for stmt in body['children']:
                    if step_id[0] >= MAX_STEPS:
                        break
                    process_statement(stmt, 'main', 0)
        
        add_step('function_exit', 'main',
                '🏁 Exit main() - program ends',
                0)
        call_stack.pop()
    
    return steps

@app.route('/analyze', methods=['POST'])
def analyze_code():
    """Perform semantic analysis"""
    try:
        data = request.get_json()
        code = data.get('code', '')
        
        if not code:
            return jsonify({
                'success': False,
                'output': 'No code provided',
                'returncode': 1
            })
        
        with tempfile.NamedTemporaryFile(mode='w', suffix='.c', delete=False) as tmp:
            tmp.write(code)
            tmp_path = tmp.name
        
        try:
            process = subprocess.Popen(
                [MYCC_PATH, '-s', tmp_path],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            
            stdout, stderr = process.communicate(timeout=TIMEOUT)
            returncode = process.returncode
            
            output = stdout + stderr
            
            return jsonify({
                'success': returncode == 0,
                'output': output,
                'returncode': returncode
            })
            
        except subprocess.TimeoutExpired:
            process.kill()
            return jsonify({
                'success': False,
                'output': f'Analysis timed out after {TIMEOUT} seconds',
                'returncode': -1
            })
        finally:
            os.unlink(tmp_path)
            
    except Exception as e:
        return jsonify({
            'success': False,
            'output': f'Server error: {str(e)}',
            'returncode': -1
        })

if __name__ == '__main__':
    if not Path(MYCC_PATH).exists():
        print(f"Warning: {MYCC_PATH} not found. Please ensure mycc is in the current directory.")
    
    app.run(debug=True, host='0.0.0.0', port=5000)