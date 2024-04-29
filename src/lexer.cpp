#include "lexer.hpp"

extern int yylex(void);

namespace Lexer {

std::vector<std::unique_ptr<Token>> Tokens_parsed;

const std::vector<std::unique_ptr<Token>>& get_tokens() {

  ::yylex();
  Tokens_parsed.push_back(std::make_unique<Token_punct>(Token_punct::END));
  return Tokens_parsed;
}

}; // namespace Lexer