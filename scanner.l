
%{
#include <stdio.h>
#include <string.h>
#include "compiler.h"
#include "parser.tab.h"

int line_num = 1;

// Process escape sequences in strings
char *processEscapes(const char *str) {
    static char buffer[1024];
    char *out = buffer;
    const char *p = str;
    
    // Skip opening quote
    if (*p == '"') p++;
    
    while (*p && *p != '"') {
        if (*p == '\\' && *(p+1)) {
            p++;
            switch (*p) {
                case 'n': *out++ = '\n'; break;
                case 't': *out++ = '\t'; break;
                case 'r': *out++ = '\r'; break;
                case '\\': *out++ = '\\'; break;
                case '"': *out++ = '"'; break;
                case '0': *out++ = '\0'; break;
                default: *out++ = *p; break;
            }
            p++;
        } else {
            *out++ = *p++;
        }
    }
    *out = '\0';
    return buffer;
}
%}

%option noyywrap

%%

"//".*                  { /* Single-line comment */ }
"/*"([^*]|\*+[^*/])*"*"+"/" { /* Multi-line comment */ }

"int"                   { return INT; }
"float"                 { return FLOAT; }
"void"                  { return VOID; }
"if"                    { return IF; }
"else"                  { return ELSE; }
"while"                 { return WHILE; }
"for"                   { return FOR; }
"return"                { return RETURN; }
"printf"                { return PRINTF; }
"scanf"                 { return SCANF; }

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return ID; }
[0-9]+                  { yylval.int_val = atoi(yytext); return INT_CONST; }
[0-9]+"."[0-9]+         { yylval.float_val = atof(yytext); return FLOAT_CONST; }

"+"                     { return PLUS; }
"-"                     { return MINUS; }
"*"                     { return MULT; }
"/"                     { return DIV; }
"%"                     { return MOD; }
"=="                    { return EQ; }
"!="                    { return NE; }
"<"                     { return LT; }
">"                     { return GT; }
"<="                    { return LE; }
">="                    { return GE; }
"&&"                    { return AND; }
"||"                    { return OR; }
"!"                     { return NOT; }
"="                     { return ASSIGN; }
";"                     { return SEMICOLON; }
","                     { return COMMA; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
"{"                     { return LBRACE; }
"}"                     { return RBRACE; }
"&"                     { return AMPERSAND; }

\"([^\\\"]|\\.)*\"      { 
    yylval.str = strdup(processEscapes(yytext)); 
    return STRING; 
}

[ \t]+                  { /* Skip whitespace */ }
\n                      { line_num++; }
.                       { printf("Unknown character: %s\n", yytext); }

%%
