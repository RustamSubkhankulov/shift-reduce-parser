#include "liblexer/lexer.hpp"
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
#endif // DUMP_JSON

int main() {

  auto& tokens = Lexer::get_tokens();

#ifdef DUMP_JSON
  dump_tokens(tokens);
#endif

  Syntax::Shift_reduce_parser parser{Grammar::Productions};
  parser.parse(tokens);

  return 0;
}