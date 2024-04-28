#ifndef PARSER_HPP
#define PARSER_HPP

#include "liblexer/lexer.hpp"
#include "grammar.hpp"
#include "ast.hpp"

namespace Syntax {

class Parser {

protected:

  std::vector<Grammar::Production> grammar_productions_;
  std::vector<AST::Production> ast_productions_;

  Parser(const std::vector<Grammar::Production>& grammar_productions,
         const std::vector<AST::Production>& ast_productions):
  grammar_productions_(grammar_productions),
  ast_productions_(ast_productions) {}

  virtual ~Parser() {}

public:

  using tokens_vector = std::vector<std::unique_ptr<Lexer::Token>>;
  virtual void parse(const tokens_vector& tokens, AST::Ast& ast) = 0;
};

}; // namespace Syntax

#endif // PARSER_HPP
