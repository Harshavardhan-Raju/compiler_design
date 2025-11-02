import React, { useState, useEffect } from 'react';
import { Play, Pause, RotateCcw, ChevronRight, CheckCircle, ArrowRight } from 'lucide-react';

const ControlFlowVisualizer = () => {
  const [executionSteps, setExecutionSteps] = useState([]);
  const [currentStep, setCurrentStep] = useState(0);
  const [isPlaying, setIsPlaying] = useState(false);
  const [speed, setSpeed] = useState(1000);

  // Sample C code for demonstration
  const sampleCode = `int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    int num = 5;
    int result = factorial(num);
    printf("Result: %d", result);
    return 0;
}`;

  // Sample AST
  const sampleAST = {
    type: "Program",
    children: [{
      type: "CompoundStmt",
      name: "DeclarationList",
      children: [
        {
          type: "FunctionDecl",
          name: "factorial",
          children: [
            {
              type: "CompoundStmt",
              name: "ParamList",
              children: [{ type: "Param", name: "n" }]
            },
            {
              type: "CompoundStmt",
              name: "StmtList",
              children: [
                {
                  type: "IfStmt",
                  name: "If",
                  children: [
                    { 
                      type: "BinaryOp", 
                      operator: "<=", 
                      children: [
                        { type: "Identifier", name: "n" },
                        { type: "IntLiteral", value: 1 }
                      ]
                    },
                    { 
                      type: "ReturnStmt", 
                      children: [{ type: "IntLiteral", value: 1 }] 
                    }
                  ]
                },
                {
                  type: "ReturnStmt",
                  children: [{
                    type: "BinaryOp",
                    operator: "*",
                    children: [
                      { type: "Identifier", name: "n" },
                      {
                        type: "FuncCall",
                        name: "factorial",
                        children: [{
                          type: "CompoundStmt",
                          name: "ArgList",
                          children: [{
                            type: "BinaryOp",
                            operator: "-",
                            children: [
                              { type: "Identifier", name: "n" },
                              { type: "IntLiteral", value: 1 }
                            ]
                          }]
                        }]
                      }
                    ]
                  }]
                }
              ]
            }
          ]
        },
        {
          type: "FunctionDecl",
          name: "main",
          children: [
            { type: "Param", name: "empty" },
            {
              type: "CompoundStmt",
              name: "StmtList",
              children: [
                {
                  type: "VarDecl",
                  name: "num",
                  children: [{ type: "IntLiteral", value: 5 }]
                },
                {
                  type: "VarDecl",
                  name: "result",
                  children: [{
                    type: "FuncCall",
                    name: "factorial",
                    children: [{
                      type: "CompoundStmt",
                      name: "ArgList",
                      children: [{ type: "Identifier", name: "num" }]
                    }]
                  }]
                },
                {
                  type: "PrintStmt",
                  children: [
                    { type: "Identifier", name: '"Result: %d"' },
                    {
                      type: "CompoundStmt",
                      name: "ArgList",
                      children: [{ type: "Identifier", name: "result" }]
                    }
                  ]
                },
                { 
                  type: "ReturnStmt", 
                  children: [{ type: "IntLiteral", value: 0 }] 
                }
              ]
            }
          ]
        }
      ]
    }]
  };

  // Generate execution steps from AST with CORRECT control flow
  const generateExecutionSteps = (astNode) => {
    const steps = [];
    let stepId = 0;
    const callStack = [];
    const allFunctions = new Map();
    const MAX_RECURSION_DEPTH = 6; // Limit recursion to prevent infinite loops
    const MAX_STEPS = 100; // Maximum total steps

    // Collect all function definitions
    if (astNode.type === "Program" && astNode.children) {
      const declList = astNode.children[0];
      if (declList && declList.children) {
        declList.children.forEach(child => {
          if (child.type === "FunctionDecl" && child.name) {
            allFunctions.set(child.name, child);
          }
        });
      }
    }

    // Process expression - CRITICAL: This must handle function calls correctly
    const processExpression = (node, currentFunc, depth = 0) => {
      if (!node) return;
      
      // Safety check
      if (stepId >= MAX_STEPS) {
        steps.push({
          id: stepId++,
          type: "warning",
          function: currentFunc,
          description: "⚠️ Maximum steps reached (truncated for display)",
          stack: [...callStack],
          depth: depth
        });
        return;
      }

      // MOST IMPORTANT: Handle function calls FIRST and COMPLETELY
      if (node.type === "FuncCall") {
        const funcName = node.name;
        
        // Check recursion depth limit
        if (depth >= MAX_RECURSION_DEPTH) {
          steps.push({
            id: stepId++,
            type: "warning",
            function: currentFunc,
            callee: funcName,
            description: `⚠️ Max recursion depth reached, stopping at ${funcName}()`,
            stack: [...callStack],
            depth: depth
          });
          return;
        }
        
        const callValue = depth > 0 ? ` (depth: ${depth + 1})` : '';
        
        // Step 1: About to call function
        steps.push({
          id: stepId++,
          type: "function_call",
          function: currentFunc,
          callee: funcName,
          description: `→ Calling ${funcName}()${callValue}`,
          stack: [...callStack],
          depth: depth
        });

        // Step 2: Push to call stack and ENTER the function
        callStack.push({ func: funcName, step: stepId, depth: depth + 1 });
        steps.push({
          id: stepId++,
          type: "function_enter",
          function: funcName,
          description: `▶ Enter ${funcName}()${callValue}`,
          stack: [...callStack],
          depth: depth + 1
        });

        // Step 3: EXECUTE THE ENTIRE FUNCTION BODY
        const funcDef = allFunctions.get(funcName);
        if (funcDef && funcDef.children && funcDef.children.length >= 2) {
          const body = funcDef.children[1];
          if (body && body.children) {
            // Execute every statement in the function
            for (const stmt of body.children) {
              if (stepId >= MAX_STEPS) break;
              processStatement(stmt, funcName, depth + 1);
            }
          }
        }

        // Step 4: Exit the function
        steps.push({
          id: stepId++,
          type: "function_exit",
          function: funcName,
          description: `◀ Exit ${funcName}()${callValue}`,
          stack: [...callStack],
          depth: depth + 1
        });

        // Step 5: Pop from call stack
        callStack.pop();

        // Step 6: Return to caller
        steps.push({
          id: stepId++,
          type: "function_return",
          function: currentFunc,
          callee: funcName,
          description: `← Back to ${currentFunc}() from ${funcName}()`,
          stack: [...callStack],
          depth: depth
        });

        return;
      }

      // For binary operations, process in left-to-right order
      if (node.type === "BinaryOp" && node.children) {
        // Process left operand (may contain function call)
        if (node.children[0]) {
          processExpression(node.children[0], currentFunc, depth);
        }
        // Process right operand (may contain function call)
        if (node.children[1]) {
          processExpression(node.children[1], currentFunc, depth);
        }
        return;
      }

      // For other nodes, recursively check children
      if (node.children) {
        for (const child of node.children) {
          if (stepId >= MAX_STEPS) break;
          processExpression(child, currentFunc, depth);
        }
      }
    };

    // Process a statement
    const processStatement = (node, currentFunc, depth = 0) => {
      if (!node) return;

      switch (node.type) {
        case "VarDecl":
          steps.push({
            id: stepId++,
            type: "var_decl",
            function: currentFunc,
            description: `Declare: int ${node.name}${node.children && node.children[0] ? ' = ...' : ''}`,
            stack: [...callStack],
            depth: depth
          });
          
          // IMPORTANT: Process initialization expression
          // This may contain a function call!
          if (node.children && node.children[0]) {
            processExpression(node.children[0], currentFunc, depth);
            
            steps.push({
              id: stepId++,
              type: "assignment",
              function: currentFunc,
              description: `Assign value to ${node.name}`,
              stack: [...callStack],
              depth: depth
            });
          }
          break;

        case "IfStmt":
          steps.push({
            id: stepId++,
            type: "condition",
            function: currentFunc,
            description: "Evaluate if condition",
            stack: [...callStack],
            depth: depth
          });
          
          // Process condition
          if (node.children && node.children[0]) {
            processExpression(node.children[0], currentFunc, depth);
          }
          
          // In this example, we'll assume true path
          if (node.children && node.children[1]) {
            steps.push({
              id: stepId++,
              type: "condition",
              function: currentFunc,
              description: "Condition is false, skip if block",
              stack: [...callStack],
              depth: depth
            });
          }
          break;

        case "WhileStmt":
        case "ForStmt":
          steps.push({
            id: stepId++,
            type: "loop",
            function: currentFunc,
            description: node.type === "WhileStmt" ? "While loop" : "For loop",
            stack: [...callStack],
            depth: depth
          });
          break;

        case "ReturnStmt":
          // CRITICAL: Process return expression FIRST
          // This may trigger more function calls!
          if (node.children && node.children[0]) {
            steps.push({
              id: stepId++,
              type: "eval",
              function: currentFunc,
              description: "Evaluate return expression",
              stack: [...callStack],
              depth: depth
            });
            
            processExpression(node.children[0], currentFunc, depth);
          }
          
          steps.push({
            id: stepId++,
            type: "return",
            function: currentFunc,
            description: `⏎ Return from ${currentFunc}()`,
            stack: [...callStack],
            depth: depth
          });
          break;

        case "PrintStmt":
          steps.push({
            id: stepId++,
            type: "print",
            function: currentFunc,
            description: "Execute printf()",
            stack: [...callStack],
            depth: depth
          });
          break;

        case "ExprStmt":
          if (node.children) {
            for (const child of node.children) {
              processExpression(child, currentFunc, depth);
            }
          }
          break;

        case "CompoundStmt":
          if (node.children) {
            for (const child of node.children) {
              processStatement(child, currentFunc, depth);
            }
          }
          break;

        default:
          if (node.children) {
            for (const child of node.children) {
              processStatement(child, currentFunc, depth);
            }
          }
      }
    };

    // START: Find and execute main
    const mainFunc = allFunctions.get("main");
    if (mainFunc) {
      callStack.push({ func: "main", step: stepId, depth: 0 });
      
      steps.push({
        id: stepId++,
        type: "function_enter",
        function: "main",
        description: "🚀 Program starts - entering main()",
        stack: [...callStack],
        depth: 0
      });

      // Execute main function body
      if (mainFunc.children && mainFunc.children.length >= 2) {
        const body = mainFunc.children[1];
        if (body && body.children) {
          for (const stmt of body.children) {
            processStatement(stmt, "main", 0);
          }
        }
      }

      // Exit main
      steps.push({
        id: stepId++,
        type: "function_exit",
        function: "main",
        description: "🏁 Exit main() - program ends",
        stack: [...callStack],
        depth: 0
      });
      callStack.pop();
    }

    return steps;
  };

  useEffect(() => {
    const steps = generateExecutionSteps(sampleAST);
    setExecutionSteps(steps);
  }, []);

  useEffect(() => {
    if (isPlaying && currentStep < executionSteps.length - 1) {
      const timer = setTimeout(() => {
        setCurrentStep(prev => prev + 1);
      }, speed);
      return () => clearTimeout(timer);
    } else if (currentStep >= executionSteps.length - 1) {
      setIsPlaying(false);
    }
  }, [isPlaying, currentStep, executionSteps, speed]);

  const handlePlay = () => setIsPlaying(!isPlaying);
  const handleReset = () => {
    setCurrentStep(0);
    setIsPlaying(false);
  };
  const handleNext = () => {
    if (currentStep < executionSteps.length - 1) {
      setCurrentStep(prev => prev + 1);
    }
  };

  const getStepColor = (type) => {
    const colors = {
      function_enter: "bg-blue-100 border-blue-500",
      function_exit: "bg-blue-50 border-blue-400",
      function_call: "bg-green-100 border-green-500",
      function_return: "bg-green-50 border-green-400",
      var_decl: "bg-purple-100 border-purple-500",
      assignment: "bg-purple-50 border-purple-400",
      condition: "bg-yellow-100 border-yellow-500",
      loop: "bg-orange-100 border-orange-500",
      return: "bg-red-100 border-red-500",
      eval: "bg-pink-100 border-pink-500",
      print: "bg-cyan-100 border-cyan-500"
    };
    return colors[type] || "bg-gray-100 border-gray-400";
  };

  const currentCallStack = executionSteps[currentStep]?.stack || [];

  return (
    <div className="w-full h-screen bg-gradient-to-br from-slate-50 to-slate-100 p-6">
      <div className="max-w-7xl mx-auto h-full flex flex-col gap-4">
        {/* Header */}
        <div className="bg-white rounded-lg shadow-lg p-6">
          <h1 className="text-3xl font-bold text-gray-800 mb-2">
            C Control Flow Visualizer
          </h1>
          <p className="text-gray-600">
            Step-by-step execution with proper function call handling
          </p>
        </div>

        <div className="flex-1 grid grid-cols-12 gap-4 overflow-hidden">
          {/* Left: Code Display */}
          <div className="col-span-4 bg-white rounded-lg shadow-lg p-6 flex flex-col">
            <h2 className="text-xl font-bold text-gray-800 mb-4">Source Code</h2>
            <pre className="flex-1 bg-gray-900 text-green-400 p-4 rounded-lg overflow-auto font-mono text-sm leading-relaxed">
              {sampleCode}
            </pre>
          </div>

          {/* Middle: Execution Steps */}
          <div className="col-span-5 bg-white rounded-lg shadow-lg p-6 flex flex-col">
            <h2 className="text-xl font-bold text-gray-800 mb-4">Execution Flow</h2>
            
            {/* Controls */}
            <div className="flex items-center gap-3 mb-4 pb-4 border-b">
              <button
                onClick={handlePlay}
                className="flex items-center gap-2 px-4 py-2 bg-blue-500 text-white rounded-lg hover:bg-blue-600 transition"
              >
                {isPlaying ? <Pause size={18} /> : <Play size={18} />}
                {isPlaying ? "Pause" : "Play"}
              </button>
              <button
                onClick={handleNext}
                disabled={currentStep >= executionSteps.length - 1}
                className="flex items-center gap-2 px-4 py-2 bg-green-500 text-white rounded-lg hover:bg-green-600 transition disabled:opacity-50 disabled:cursor-not-allowed"
              >
                <ChevronRight size={18} />
                Next
              </button>
              <button
                onClick={handleReset}
                className="flex items-center gap-2 px-4 py-2 bg-gray-500 text-white rounded-lg hover:bg-gray-600 transition"
              >
                <RotateCcw size={18} />
                Reset
              </button>
              <div className="ml-auto flex items-center gap-2">
                <label className="text-sm text-gray-600">Speed:</label>
                <input
                  type="range"
                  min="200"
                  max="2000"
                  step="200"
                  value={speed}
                  onChange={(e) => setSpeed(Number(e.target.value))}
                  className="w-24"
                />
                <span className="text-sm text-gray-600">{speed}ms</span>
              </div>
            </div>

            {/* Progress */}
            <div className="mb-4">
              <div className="flex justify-between text-sm text-gray-600 mb-1">
                <span>Step {currentStep + 1} of {executionSteps.length}</span>
                <span>{Math.round(((currentStep + 1) / executionSteps.length) * 100)}%</span>
              </div>
              <div className="w-full bg-gray-200 rounded-full h-2">
                <div
                  className="bg-blue-500 h-2 rounded-full transition-all duration-300"
                  style={{ width: `${((currentStep + 1) / executionSteps.length) * 100}%` }}
                />
              </div>
            </div>

            {/* Steps List */}
            <div className="flex-1 overflow-auto space-y-2">
              {executionSteps.map((step, idx) => {
                const indentLevel = step.depth || 0;
                return (
                  <div
                    key={step.id}
                    className={`p-3 rounded-lg border-2 transition-all ${
                      idx === currentStep
                        ? `${getStepColor(step.type)} shadow-lg scale-[1.02] font-semibold`
                        : idx < currentStep
                        ? "bg-gray-50 border-gray-200 opacity-50"
                        : "bg-white border-gray-200 opacity-30"
                    }`}
                    style={{ marginLeft: `${indentLevel * 20}px` }}
                  >
                    <div className="flex items-start gap-3">
                      <span className="text-lg min-w-[24px]">
                        {step.type === "function_enter" && "▶"}
                        {step.type === "function_exit" && "◀"}
                        {step.type === "function_call" && "→"}
                        {step.type === "function_return" && "←"}
                        {step.type === "return" && "⏎"}
                        {!["function_enter", "function_exit", "function_call", "function_return", "return"].includes(step.type) && "•"}
                      </span>
                      <div className="flex-1 min-w-0">
                        <div className="text-gray-800 break-words">
                          {step.description}
                        </div>
                        <div className="text-xs text-gray-500 mt-1">
                          Step {idx + 1} • in {step.function}()
                        </div>
                      </div>
                      {idx === currentStep && (
                        <ArrowRight className="text-blue-500 animate-pulse flex-shrink-0" size={20} />
                      )}
                      {idx < currentStep && (
                        <CheckCircle className="text-green-500 flex-shrink-0" size={20} />
                      )}
                    </div>
                  </div>
                );
              })}
            </div>
          </div>

          {/* Right: Call Stack */}
          <div className="col-span-3 bg-white rounded-lg shadow-lg p-6 flex flex-col">
            <h2 className="text-xl font-bold text-gray-800 mb-4">Call Stack</h2>
            <div className="flex-1 space-y-2 overflow-auto">
              {currentCallStack.length === 0 ? (
                <div className="text-center text-gray-400 py-8">
                  Stack is empty
                </div>
              ) : (
                [...currentCallStack].reverse().map((frame, idx) => (
                  <div
                    key={idx}
                    className={`p-4 rounded-lg border-2 transition-all ${
                      idx === 0
                        ? "bg-blue-100 border-blue-500 shadow-md scale-105"
                        : "bg-gray-50 border-gray-300"
                    }`}
                  >
                    <div className="flex items-center gap-2">
                      <span className="text-2xl">
                        {idx === 0 ? "→" : "•"}
                      </span>
                      <div className="flex-1">
                        <div className="font-bold text-gray-800">
                          {frame.func}()
                        </div>
                        <div className="text-xs text-gray-500">
                          {idx === 0 ? "← Active" : `Caller (depth ${currentCallStack.length - idx - 1})`}
                        </div>
                      </div>
                    </div>
                  </div>
                ))
              )}
            </div>
            
            <div className="mt-4 pt-4 border-t">
              <div className="text-sm text-gray-600">
                <div className="font-semibold mb-2">Stack Depth:</div>
                <div className="text-3xl font-bold text-blue-600">
                  {currentCallStack.length}
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default ControlFlowVisualizer;
