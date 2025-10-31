from flask import Flask, render_template, request, jsonify
import subprocess
import tempfile
import os
import json
import time
from pathlib import Path
from typing import Dict, List, Any, Optional

app = Flask(__name__)

# ==================== CONFIGURATION ====================
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
# Prefer Windows binary if present
MYCC_EXE = os.path.join(BASE_DIR, "mycc.exe")
MYCC_BIN = os.path.join(BASE_DIR, "mycc")
MYCC_PATH = MYCC_EXE if os.path.exists(MYCC_EXE) else MYCC_BIN
TIMEOUT = 10  # Timeout in seconds
MAX_CODE_SIZE = 50000  # Max code size in bytes

# ==================== HELPER FUNCTIONS ====================

def validate_code(code: str) -> tuple[bool, Optional[str]]:
    """Validate input code"""
    if not code or not code.strip():
        return False, "No code provided"
    
    if len(code.encode('utf-8')) > MAX_CODE_SIZE:
        return False, f"Code size exceeds maximum limit of {MAX_CODE_SIZE} bytes"
    
    return True, None


def run_mycc_command(args: List[str], code: str, stdin_input: str = "") -> Dict[str, Any]:
    """
    Run mycc with given arguments
    
    Args:
        args: Command line arguments (e.g., ['-i', '-a'])
        code: C source code
        stdin_input: Input to pipe to stdin (optional)
    
    Returns:
        Dictionary with stdout, stderr, returncode, and execution_time
    """
    # Create temporary file
    with tempfile.NamedTemporaryFile(mode='w', suffix='.c', delete=False) as tmp:
        tmp.write(code)
        tmp_path = tmp.name
    
    try:
        # Build command
        cmd = [MYCC_PATH] + args + [tmp_path]
        
        # Start timing
        start_time = time.time()
        
        # Run process
        process = subprocess.Popen(
            cmd,
            stdin=subprocess.PIPE if stdin_input else None,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        
        # Communicate with timeout
        try:
            stdout, stderr = process.communicate(
                input=stdin_input if stdin_input else None,
                timeout=TIMEOUT
            )
            execution_time = time.time() - start_time
            returncode = process.returncode
            
            return {
                'stdout': stdout,
                'stderr': stderr,
                'returncode': returncode,
                'execution_time': round(execution_time * 1000, 2),  # Convert to ms
                'timeout': False
            }
            
        except subprocess.TimeoutExpired:
            process.kill()
            return {
                'stdout': '',
                'stderr': f'Execution timed out after {TIMEOUT} seconds',
                'returncode': -1,
                'execution_time': TIMEOUT * 1000,
                'timeout': True
            }
    
    finally:
        # Clean up temporary file
        if os.path.exists(tmp_path):
            os.unlink(tmp_path)


def build_ast_hierarchy(ast_json: Dict) -> Dict:
    """
    Convert flat AST JSON to hierarchical format for D3.js visualization
    """
    # This is a placeholder - adjust based on your mycc's actual AST format
    if not ast_json:
        return {}
    
    return ast_json


def build_cfg_data(ast_json: Dict) -> Dict[str, Any]:
    """
    Build Control Flow Graph data from AST
    Returns format compatible with D3.js CFG visualizer
    """
    # This is a simplified example - implement based on your AST structure
    nodes = []
    edges = []
    node_counter = 0
    
    def process_node(node, parent_id=None):
        nonlocal node_counter
        
        node_id = f"node{node_counter}"
        node_counter += 1
        
        node_type = node.get('type', 'Unknown')
        label = node.get('name', node_type)
        
        nodes.append({'id': node_id, 'label': label, 'type': node_type})
        
        if parent_id:
            edges.append({'from': parent_id, 'to': node_id})
        
        # Process children
        children = node.get('children', [])
        for child in children:
            process_node(child, node_id)
        
        return node_id
    
    if ast_json:
        process_node(ast_json)
    
    return {'nodes': nodes, 'edges': edges}


def extract_execution_trace(output: str, code: str) -> List[Dict[str, Any]]:
    """
    Extract execution trace from program output
    Preferred: parse structured TRACE JSON lines emitted by interpreter.
    Fallback: heuristic based on code when no TRACE found.
    """
    trace: List[Dict[str, Any]] = []
    if not output:
        return trace
    
    # First pass: try to parse structured TRACE JSON lines
    for raw in output.splitlines():
        line = raw.strip()
        if not line:
            continue
        # Allow optional 'TRACE ' prefix
        if line.upper().startswith('TRACE '):
            line = line[6:].strip()
        try:
            obj = json.loads(line)
            if isinstance(obj, dict) and (
                'line' in obj or 'type' in obj or 'block' in obj
            ):
                trace.append(obj)
        except json.JSONDecodeError:
            continue
    
    if trace:
        # Ensure step numbering if not provided
        for i, step in enumerate(trace, start=1):
            if 'step' not in step:
                step['step'] = i
        return trace
    
    # Fallback heuristic (very light) if no TRACE was parsed
    lines = code.split('\n')
    variables: Dict[str, Any] = {}
    for i, src in enumerate(lines, 1):
        s = src.strip()
        if not s:
            continue
        if s.startswith('int') and '=' in s:
            try:
                name_part = s.replace('int', '').replace(';', '')
                var_name, var_value = [p.strip() for p in name_part.split('=', 1)]
                variables[var_name] = int(var_value)
                trace.append({
                    'step': len(trace) + 1,
                    'type': 'execute',
                    'block': 'declaration',
                    'content': s,
                    'line': i,
                    'variables': dict(variables)
                })
            except Exception:
                pass
        elif s.startswith('if'):
            cond = s
            trace.append({
                'step': len(trace) + 1,
                'type': 'enter',
                'block': 'if',
                'condition': cond,
                'line': i,
                'variables': dict(variables)
            })
    return trace


def parse_syntax_errors(stderr: str) -> List[Dict[str, Any]]:
    """Parse syntax errors emitted as JSON objects: { "line": n, "message": "..." } per line."""
    errors: List[Dict[str, Any]] = []
    if not stderr:
        return errors
    for raw in stderr.splitlines():
        s = raw.strip()
        if not s:
            continue
        # Allow non-JSON noise; only collect valid JSON with required keys
        try:
            obj = json.loads(s)
            if isinstance(obj, dict) and 'line' in obj and 'message' in obj:
                errors.append({
                    'line': int(obj['line']),
                    'message': str(obj['message'])
                })
        except Exception:
            continue
    return errors


# ==================== ROUTES ====================

@app.route('/')
def index():
    """Serve the main HTML page"""
    return render_template('index.html')


@app.route('/compile', methods=['POST'])
def compile_code():
    """
    Compile and run C code with input
    Expects: { code: string, input: string }
    Returns: { success: bool, output: string, errors: string, execution_time: float }
    """
    try:
        data = request.get_json()
        code = data.get('code', '')
        user_input = data.get('input', '')
        
        # Validate code
        is_valid, error_msg = validate_code(code)
        if not is_valid:
            return jsonify({
                'success': False,
                'output': '',
                'errors': error_msg,
                'execution_time': 0
            })
        
        # Run mycc with -i flag for interpretation
        result = run_mycc_command(['-i'], code, user_input)
        syntax_errors = parse_syntax_errors(result.get('stderr', ''))
        
        return jsonify({
            'success': result['returncode'] == 0 and not result['timeout'] and not syntax_errors,
            'output': result.get('stdout', ''),
            'errors': syntax_errors if syntax_errors else result.get('stderr', ''),
            'execution_time': result.get('execution_time', 0)
        })
        
    except Exception as e:
        return jsonify({
            'success': False,
            'output': '',
            'errors': f'Server error: {str(e)}',
            'execution_time': 0
        }), 500


@app.route('/get_trace', methods=['GET', 'POST'])
def get_trace():
    """
    Get execution trace for visualization
    Expects: { code: string, input: string } (POST) or uses example data (GET)
    Returns: { code: string, trace: array, ast: object, cfg: object }
    """
    try:
        # Handle GET for initial load (example data)
        if request.method == 'GET':
            return jsonify({
                'code': """int main() {
    int x = 5;
    int y = 10;
    if (x > 3) {
        x = x * 2;
        y = y + x;
    }
    return x;
}""",
                'trace': [
                    {
                        'step': 1,
                        'type': 'enter',
                        'block': 'function',
                        'name': 'main',
                        'line': 1,
                        'timing': 0.0,
                        'variables': {},
                        'cfgNode': 'node1'
                    },
                    {
                        'step': 2,
                        'type': 'execute',
                        'block': 'declaration',
                        'content': 'int x = 5',
                        'line': 2,
                        'timing': 0.2,
                        'variables': {'x': 5},
                        'cfgNode': 'node2'
                    },
                    {
                        'step': 3,
                        'type': 'execute',
                        'block': 'declaration',
                        'content': 'int y = 10',
                        'line': 3,
                        'timing': 0.2,
                        'variables': {'x': 5, 'y': 10},
                        'cfgNode': 'node3'
                    },
                    {
                        'step': 4,
                        'type': 'enter',
                        'block': 'if',
                        'condition': 'x > 3',
                        'line': 4,
                        'timing': 0.3,
                        'variables': {'x': 5, 'y': 10},
                        'cfgNode': 'node4'
                    },
                    {
                        'step': 5,
                        'type': 'execute',
                        'block': 'assignment',
                        'content': 'x = x * 2',
                        'line': 5,
                        'timing': 0.2,
                        'variables': {'x': 10, 'y': 10},
                        'cfgNode': 'node5'
                    },
                    {
                        'step': 6,
                        'type': 'execute',
                        'block': 'assignment',
                        'content': 'y = y + x',
                        'line': 6,
                        'timing': 0.2,
                        'variables': {'x': 10, 'y': 20},
                        'cfgNode': 'node6'
                    },
                    {
                        'step': 7,
                        'type': 'exit',
                        'block': 'if',
                        'line': 7,
                        'timing': 0.1,
                        'variables': {'x': 10, 'y': 20},
                        'cfgNode': 'node7'
                    },
                    {
                        'step': 8,
                        'type': 'execute',
                        'block': 'return',
                        'content': 'return x',
                        'line': 8,
                        'timing': 0.1,
                        'variables': {'x': 10, 'y': 20},
                        'cfgNode': 'node8'
                    }
                ],
                'ast': {
                    'type': 'Program',
                    'name': 'main',
                    'children': [
                        {
                            'type': 'Function',
                            'name': 'main',
                            'children': [
                                {'type': 'Decl', 'name': 'x'},
                                {'type': 'Decl', 'name': 'y'},
                                {
                                    'type': 'If',
                                    'name': 'x > 3',
                                    'children': [
                                        {'type': 'Assign', 'name': 'x = x * 2'},
                                        {'type': 'Assign', 'name': 'y = y + x'}
                                    ]
                                },
                                {'type': 'Return', 'name': 'x'}
                            ]
                        }
                    ]
                },
                'cfg': {
                    'nodes': [
                        {'id': 'node1', 'label': 'Start', 'type': 'entry'},
                        {'id': 'node2', 'label': 'x = 5', 'type': 'statement'},
                        {'id': 'node3', 'label': 'y = 10', 'type': 'statement'},
                        {'id': 'node4', 'label': 'if (x > 3)', 'type': 'condition'},
                        {'id': 'node5', 'label': 'x = x * 2', 'type': 'statement'},
                        {'id': 'node6', 'label': 'y = y + x', 'type': 'statement'},
                        {'id': 'node7', 'label': 'return x', 'type': 'return'},
                        {'id': 'node8', 'label': 'End', 'type': 'exit'}
                    ],
                    'edges': [
                        {'from': 'node1', 'to': 'node2'},
                        {'from': 'node2', 'to': 'node3'},
                        {'from': 'node3', 'to': 'node4'},
                        {'from': 'node4', 'to': 'node5', 'type': 'true-branch'},
                        {'from': 'node4', 'to': 'node7', 'type': 'false-branch'},
                        {'from': 'node5', 'to': 'node6'},
                        {'from': 'node6', 'to': 'node7'},
                        {'from': 'node7', 'to': 'node8'}
                    ]
                }
            })
        
        # Handle POST for user code
        data = request.get_json()
        code = data.get('code', '')
        user_input = data.get('input', '')
        
        # Validate code
        is_valid, error_msg = validate_code(code)
        if not is_valid:
            return jsonify({'error': error_msg}), 400
        
        # Run compiler to get AST (fallback gracefully if unavailable)
        ast_data = {}
        cfg_data = {'nodes': [], 'edges': []}
        try:
            ast_result = run_mycc_command(['-a'], code)
            if ast_result['returncode'] == 0 and ast_result.get('stdout'):
                try:
                    ast_data = json.loads(ast_result['stdout'])
                except json.JSONDecodeError:
                    ast_data = {}
        except Exception:
            ast_data = {}
        
        # Build CFG from AST (or placeholder if AST missing)
        try:
            cfg_data = build_cfg_data(ast_data)
        except Exception:
            cfg_data = {'nodes': [], 'edges': []}
        
        # Run code and extract trace (fallback to heuristic on failure)
        exec_stdout = ''
        exec_stderr = ''
        exec_time = 0
        try:
            exec_result = run_mycc_command(['-i'], code, user_input)
            exec_stdout = exec_result.get('stdout', '')
            exec_stderr = exec_result.get('stderr', '')
            exec_time = exec_result.get('execution_time', 0)
        except Exception:
            exec_stdout = ''
            exec_stderr = ''
            exec_time = 0
        
        trace_data = extract_execution_trace(exec_stdout, code)
        syntax_errors = parse_syntax_errors(exec_stderr)
        
        return jsonify({
            'code': code,
            'trace': trace_data,
            'ast': build_ast_hierarchy(ast_data),
            'cfg': cfg_data,
            'output': exec_stdout,
            'execution_time': exec_time,
            'errors': syntax_errors
        })
        
    except Exception as e:
        return jsonify({'error': f'Server error: {str(e)}'}), 500
def visualize_ast():
    """
    Generate AST visualization (legacy endpoint - kept for compatibility)
    Expects: { code: string }
    Returns: { success: bool, ast: object, cfg: object }
    """
    try:
        data = request.get_json()
        code = data.get('code', '')
        
        # Validate code
        is_valid, error_msg = validate_code(code)
        if not is_valid:
            return jsonify({
                'success': False,
                'error': error_msg
            })
        
        # Run mycc with -a flag for AST
        result = run_mycc_command(['-a'], code)
        
        if result['returncode'] != 0 or result['timeout']:
            return jsonify({
                'success': False,
                'error': result['stderr'] or 'Failed to generate AST'
            })
        
        # Parse AST JSON
        try:
            ast_data = json.loads(result['stdout']) if result['stdout'] else {}
            cfg_data = build_cfg_data(ast_data)
            
            return jsonify({
                'success': True,
                'ast': build_ast_hierarchy(ast_data),
                'cfg': cfg_data
            })
        except json.JSONDecodeError as e:
            return jsonify({
                'success': False,
                'error': f'Invalid AST JSON: {str(e)}'
            })
            
    except Exception as e:
        return jsonify({
            'success': False,
            'error': f'Server error: {str(e)}'
        }), 500


@app.route('/analyze', methods=['POST'])
def analyze_code():
    """
    Perform semantic analysis
    Expects: { code: string }
    Returns: { success: bool, output: string, execution_time: float }
    """
    try:
        data = request.get_json()
        code = data.get('code', '')
        
        # Validate code
        is_valid, error_msg = validate_code(code)
        if not is_valid:
            return jsonify({
                'success': False,
                'output': error_msg,
                'execution_time': 0
            })
        
        # Run mycc with -s flag for semantic analysis
        result = run_mycc_command(['-s'], code)
        
        # Combine stdout and stderr
        output = (result['stdout'] + '\n' + result['stderr']).strip()
        
        return jsonify({
            'success': result['returncode'] == 0 and not result['timeout'],
            'output': output or 'Analysis completed successfully',
            'execution_time': result['execution_time']
        })
        
    except Exception as e:
        return jsonify({
            'success': False,
            'output': f'Server error: {str(e)}',
            'execution_time': 0
        }), 500


@app.route('/health', methods=['GET'])
def health_check():
    """Health check endpoint"""
    mycc_exists = Path(MYCC_PATH).exists()
    
    return jsonify({
        'status': 'healthy' if mycc_exists else 'degraded',
        'mycc_available': mycc_exists,
        'mycc_path': MYCC_PATH
    })


# ==================== ERROR HANDLERS ====================

@app.errorhandler(404)
def not_found(error):
    return jsonify({'error': 'Endpoint not found'}), 404


@app.errorhandler(500)
def internal_error(error):
    return jsonify({'error': 'Internal server error'}), 500


# ==================== MAIN ====================

if __name__ == '__main__':
    # Check if mycc exists
    if not Path(MYCC_PATH).exists():
        print(f"⚠️  Warning: {MYCC_PATH} not found!")
        print(f"   Please ensure 'mycc' is in the directory: {BASE_DIR}")
    else:
        print(f"✓ Found mycc at: {MYCC_PATH}")
    
    print("\n" + "="*60)
    print("🚀 Advanced Execution Path Visualizer")
    print("="*60)
    print(f"📁 Base Directory: {BASE_DIR}")
    print(f"🔧 Compiler Path: {MYCC_PATH}")
    print(f"⏱️  Timeout: {TIMEOUT}s")
    print(f"📊 Max Code Size: {MAX_CODE_SIZE} bytes")
    print("="*60 + "\n")
    
    # Run Flask app
    app.run(debug=True, host='0.0.0.0', port=5000)