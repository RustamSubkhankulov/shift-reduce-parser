#include <fstream>

#ifdef DUMP
#include <cassert>
#endif

#include "liblexer/lexer.hpp"
#include "grammar.hpp"
#include "shift_reduce.hpp"

int main(const int argc, char** argv) {

#ifndef DUMP
  /* Unused variables warning with -DDUMP=OFF */
  (void) argc;
  (void) argv;
#endif

  auto& tokens = Lexer::get_tokens();

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
