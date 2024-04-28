#ifndef PARSER_HPP
#define PARSER_HPP

#include "liblexer/lexer.hpp"
#include "grammar.hpp"
#include "ast.hpp"

namespace Syntax {

class Parser {

protected:

  std::vector<Grammar::Production> productions_;

  Parser(const std::vector<Grammar::Production>& productions):
  productions_(productions) {}

  virtual ~Parser() {}

public:

  using tokens_vector = std::vector<std::unique_ptr<Lexer::Token>>;
  virtual void parse(const tokens_vector& tokens, AST::Ast& ast) = 0;

};

}; // namespace Syntax

#endif // PARSER_HPP