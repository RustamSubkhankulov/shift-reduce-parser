/* Options. */
%option noyywrap nounput

/* Includes. */
%top {
  #include <iostream>
  #include <vector>
  #include <memory>
  #include <string>
  #include <cctype>
  #include "lexer.hpp"
}

/* Definitions. */
%{

using namespace Lexer;

std::string Multi_line_strlit;

#define ADD_TOKEN(TYPE, ARG) Tokens_parsed.push_back(std::make_unique<TYPE>(ARG))

[[noreturn]] static void lexical_error(const std::string& token, const std::string& what = "Lexical error") {
  
  std::cerr << what << " at line " << yylineno << ": |" << token << "|\n";
  exit(EXIT_FAILURE);
}

#ifdef DUMP_JSON
  void dump_tokens();
#endif

%}

/* Conditinons. */

/* Currently parsing multi-line comment. */
%x MULTI_LINE_COMMENT

/* Currently parsing string literal. */
%x STRLIT

/* Categories. */

DIGIT0  [0-9]
DIGIT1  [1-9]
ALPHALC [a-z]
ALPHAUC [A-Z]
ALPHA   {ALPHALC}|{ALPHAUC}

DECINT  {DIGIT0}|({DIGIT1}{DIGIT0}*)
NUMINT  [-+]?{DECINT}

DECFLT  ({DECINT}?[.]{DIGIT0}{1,6})|({DECINT}[.]({DIGIT0}{0,6})?)
NUMFLT  [-+]?{DECFLT}

NM_TAIL ({ALPHA}|{DECINT})*
NAMEUC  {ALPHAUC}{NM_TAIL}
NAMELC  {ALPHALC}{NM_TAIL}
NAME    {NAMEUC}|{NAMELC}

ID_TAIL (_|{NAME}|{DECINT}|\$)*

VAR_ID  {NAMELC}{ID_TAIL}
TYPE_ID {NAMEUC}{ID_TAIL}  

ESCAPED (\\a)|(\\b)|(\\f)|(\\n)|(\\r)|(\\t)|(\\v)|(\\\\)|(\\\')|(\\\")

/* Rules section. */
%%

(?i:if)       ADD_TOKEN(Token_kword, Token_kword::IF);
(?i:not)      ADD_TOKEN(Token_kword, Token_kword::NOT);
(?i:else)     ADD_TOKEN(Token_kword, Token_kword::ELSE);
(?i:loop)     ADD_TOKEN(Token_kword, Token_kword::LOOP);
(?i:then)     ADD_TOKEN(Token_kword, Token_kword::THEN);
(?i:while)    ADD_TOKEN(Token_kword, Token_kword::WHILE);
(?i:print)    ADD_TOKEN(Token_kword, Token_kword::PRINT);
(?i:println)  ADD_TOKEN(Token_kword, Token_kword::PRINTLN);

t(?i:rue)     ADD_TOKEN(Token_kword, Token_kword::TRUE);
f(?i:alse)    ADD_TOKEN(Token_kword, Token_kword::FALSE);

{NUMINT}      ADD_TOKEN(Token_numint, std::stoi(yytext));
{NUMFLT}      ADD_TOKEN(Token_numflt, std::stof(yytext)); 

{VAR_ID}      ADD_TOKEN(Token_var_id, yytext);
{TYPE_ID}     ADD_TOKEN(Token_type_id, yytext);

\+            ADD_TOKEN(Token_oper, Token_oper::ADD);
\-            ADD_TOKEN(Token_oper, Token_oper::SUB);
\/            ADD_TOKEN(Token_oper, Token_oper::DIV);
\*            ADD_TOKEN(Token_oper, Token_oper::MUL);
\=            ADD_TOKEN(Token_oper, Token_oper::ASS);
\&            ADD_TOKEN(Token_oper, Token_oper::AND);
\^            ADD_TOKEN(Token_oper, Token_oper::XOR);
\~            ADD_TOKEN(Token_oper, Token_oper::NEG);
\|            ADD_TOKEN(Token_oper, Token_oper::OR);

\(            ADD_TOKEN(Token_punct, Token_punct::OPENING_BR);
\)            ADD_TOKEN(Token_punct, Token_punct::CLOSING_BR);

--.*        { }

<INITIAL>\" BEGIN(STRLIT);

<STRLIT>\\ {
  
  int sym = yyinput();
  if (sym == 'a' || sym == 'b' || sym == 'f'  || sym == 'n'  || sym == 'r'
   || sym == 't' || sym == 'v' || sym == '\\' || sym == '\'' || sym == '\"') {
    
    Multi_line_strlit.push_back('\\');
    Multi_line_strlit.push_back(sym);

  } else {

    while (sym != '\n') {

      if (sym == 0) {
        lexical_error(yytext, "Unclosed multi-line string literal");
      }

      if (sym != ' ' && sym != '\t' && sym != '\r') {
        lexical_error(yytext, "Invalid multi-line string literal");
      }

      sym = yyinput();
    }
  }
}

<STRLIT>\n {
  lexical_error(yytext, "Split multi-line string literal");
}

<STRLIT>[^\\\"] Multi_line_strlit.append(yytext);

<STRLIT>\" {
  ADD_TOKEN(Token_str, Multi_line_strlit);
  Multi_line_strlit.clear();
  BEGIN(INITIAL);
}

<INITIAL>\/\* BEGIN(MULTI_LINE_COMMENT);

<MULTI_LINE_COMMENT>.|\n { /*  Skip skip skip. */ }

<MULTI_LINE_COMMENT><<EOF>> {
  lexical_error(yytext, "Unclosed multi-line comment.");
}

<MULTI_LINE_COMMENT>\*\/ BEGIN(INITIAL);

[[:space:]]+
.|\n lexical_error(yytext);

%%
