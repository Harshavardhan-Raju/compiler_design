from flask import Flask, render_template, request, jsonify
import subprocess
import tempfile
import os
import json
from pathlib import Path

app = Flask(__name__)

# Configuration
# Get the directory where app.py is located
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
MYCC_PATH = os.path.join(BASE_DIR, "mycc")  # Path to your custom compiler
TIMEOUT = 10  # Timeout for compilation/execution in seconds

@app.route('/')
def index():
    """Serve the main HTML page"""
    return render_template('index.html')

@app.route('/compile', methods=['POST'])
def compile_code():
    """
    Compile and run C code with input
    Expects: { code: string, input: string }
    Returns: { success: bool, output: string, errors: string, returncode: int }
    """
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
        
        # Create temporary file for C code
        with tempfile.NamedTemporaryFile(mode='w', suffix='.c', delete=False) as tmp:
            tmp.write(code)
            tmp_path = tmp.name
        
        try:
            # Run mycc -i with input piped to stdin
            process = subprocess.Popen(
                [MYCC_PATH, '-i', tmp_path],
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            
            # Communicate with timeout
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
            # Clean up temporary file
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
    """
    Generate AST visualization
    Expects: { code: string }
    Returns: { success: bool, ast: object } or { success: false, error: string }
    """
    try:
        data = request.get_json()
        code = data.get('code', '')
        
        if not code:
            return jsonify({
                'success': False,
                'error': 'No code provided'
            })
        
        # Create temporary file for C code
        with tempfile.NamedTemporaryFile(mode='w', suffix='.c', delete=False) as tmp:
            tmp.write(code)
            tmp_path = tmp.name
        
        try:
            # Run mycc -a to get JSON AST
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
            
            # Parse JSON output
            try:
                ast_data = json.loads(stdout)
                return jsonify({
                    'success': True,
                    'ast': ast_data
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
            # Clean up temporary file
            os.unlink(tmp_path)
            
    except Exception as e:
        return jsonify({
            'success': False,
            'error': f'Server error: {str(e)}'
        })

@app.route('/analyze', methods=['POST'])
def analyze_code():
    """
    Perform semantic analysis
    Expects: { code: string }
    Returns: { success: bool, output: string, returncode: int }
    """
    try:
        data = request.get_json()
        code = data.get('code', '')
        
        if not code:
            return jsonify({
                'success': False,
                'output': 'No code provided',
                'returncode': 1
            })
        
        # Create temporary file for C code
        with tempfile.NamedTemporaryFile(mode='w', suffix='.c', delete=False) as tmp:
            tmp.write(code)
            tmp_path = tmp.name
        
        try:
            # Run mycc -s for semantic analysis
            process = subprocess.Popen(
                [MYCC_PATH, '-s', tmp_path],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            
            stdout, stderr = process.communicate(timeout=TIMEOUT)
            returncode = process.returncode
            
            # Combine stdout and stderr for analysis output
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
            # Clean up temporary file
            os.unlink(tmp_path)
            
    except Exception as e:
        return jsonify({
            'success': False,
            'output': f'Server error: {str(e)}',
            'returncode': -1
        })

if __name__ == '__main__':
    # Check if mycc exists
    if not Path(MYCC_PATH).exists():
        print(f"Warning: {MYCC_PATH} not found. Please ensure mycc is in the current directory.")
    
    # Run Flask app
    app.run(debug=True, host='0.0.0.0', port=5000)