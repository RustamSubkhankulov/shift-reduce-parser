#ifndef SHIFT_REDUCE_HPP
#define SHIFT_REDUCE_HPP

#include <stack>
#include <unordered_map>

#include "grammar.hpp"
#include "parser.hpp"

namespace Syntax {

class Shift_reduce_parser : public Parser {

private:

  enum Action_type {
  
    SHIFT  = 0,
    REDUCE = 1,
    ACCEPT = 2,
  };

  struct Action {

    Action_type type;
    unsigned int num = 0U;
  };

  struct Syntax_table_key {
    
    unsigned int state;
    unsigned int symb;
    bool operator==(const Syntax_table_key&) const = default;
  };

  struct Syntax_table_key_hash
  {
      std::size_t operator()(const Syntax_table_key& key) const noexcept
      {
          std::size_t h1 = std::hash<unsigned int>{}(key.state);
          std::size_t h2 = std::hash<unsigned int>{}(key.symb);
          return h1 ^ (h2 << 1); // or use boost::hash_combine
      }
  };

  using Action_table = std::unordered_map<Syntax_table_key, Action, Syntax_table_key_hash>;
  using Goto_table   = std::unordered_map<Syntax_table_key, unsigned int, Syntax_table_key_hash>;

  static const Action_table action_table;
  static const Goto_table goto_table;

public:

  Shift_reduce_parser(const std::vector<Grammar::Production>& productions):
    Parser(productions) {}

  ~Shift_reduce_parser() {}

  void parse(const tokens_vector& tokens) override;

  void shift (std::vector<unsigned int>& state_stack, Action action);
  void reduce(std::vector<unsigned int>& state_stack, Action action);

#ifdef VERBOSE

  static constexpr unsigned int Table_entry_width = 32U;

  void verbose_annotate(
    const tokens_vector& tokens, 
    size_t token_idx, 
    const std::vector<unsigned int>& state_stack, 
    unsigned iter_idx
  );

  static void verbose_write_header();
  static void verbose_write_separator();

  static void verbose_print_str_aligned(const std::string& str);
#endif

private:

  unsigned int token_to_terminal(const Lexer::Token& token);
};

}; // namespace Syntax

#endif // SHIFT_REDUCE_HPP