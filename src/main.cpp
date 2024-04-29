#include <fstream>

#ifdef DUMP
#include <cassert>
#endif

#include "lexer.hpp"
#include "grammar.hpp"
#include "shift_reduce.hpp"

#ifdef DUMP_JSON
static void dump_tokens(const std::vector<std::unique_ptr<Lexer::Token>>& tokens) {

  std::cout << "{\"tokens\":[";

  for (unsigned long ind = 0; ind < tokens.size(); ++ind) {
    
    std::cout << *tokens[ind];
    if (ind != tokens.size() - 1) {
      std::cout << ',';
    }
  }

  std::cout << "]}";
  
  return;
}
#endif

int main(const int argc, char** argv) {

#ifndef DUMP
  /* Unused variables warning with -DDUMP=OFF */
  (void) argc;
  (void) argv;
#endif

  auto& tokens = Lexer::get_tokens();

#ifdef DUMP_JSON
  dump_tokens(tokens);
#endif

  Syntax::Shift_reduce_parser parser{Arithm::Grammar_productions, Arithm::Ast_productions};
  AST::Ast ast;

  parser.parse(tokens, ast);

#ifdef DUMP
  assert(argc >= 2);
  std::ofstream dump{argv[1]};
  ast.dump_tree(dump);
#endif

  return 0;
}
