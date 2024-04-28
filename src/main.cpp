#include "liblexer/lexer.hpp"
#include "grammar.hpp"
#include "shift_reduce.hpp"

int main() {

  auto& tokens = Lexer::get_tokens();

  Syntax::Shift_reduce_parser parser{Arithm::Productions};
  AST::Ast ast;

  parser.parse(tokens, ast);
  ast.dump_tree(std::cout);

  return 0;
}