#include <stdexcept>
#include <cstring>
#include <string>

#include "shift_reduce.hpp"
#include "sr_verbose_support.hpp"

namespace Syntax {

using namespace Arithm;

const Shift_reduce_parser::Action_table Shift_reduce_parser::action_table = {

  { {.state = 0U,  .symb = ID    }, { .type = SHIFT,  .num = 5U } },
  { {.state = 0U,  .symb = NUM   }, { .type = SHIFT,  .num = 12U} }, // 
  { {.state = 0U,  .symb = OP_BR }, { .type = SHIFT,  .num = 4U } },

  { {.state = 1U,  .symb = ADD   }, { .type = SHIFT,  .num = 6U } },
  { {.state = 1U,  .symb = SUB   }, { .type = SHIFT,  .num = 13U} }, //
  { {.state = 1U,  .symb = END   }, { .type = ACCEPT            } },

  { {.state = 2U,  .symb = ADD   }, { .type = REDUCE, .num = 3U } },
  { {.state = 2U,  .symb = SUB   }, { .type = REDUCE, .num = 3U } }, //
  { {.state = 2U,  .symb = MUL   }, { .type = SHIFT,  .num = 7U } },
  { {.state = 2U,  .symb = DIV   }, { .type = SHIFT,  .num = 15U} }, // 
  { {.state = 2U,  .symb = CL_BR }, { .type = REDUCE, .num = 3U } },
  { {.state = 2U,  .symb = END   }, { .type = REDUCE, .num = 3U } },

  { {.state = 3U,  .symb = ADD   }, { .type = REDUCE, .num = 6U } },
  { {.state = 3U,  .symb = SUB   }, { .type = REDUCE, .num = 6U } }, //
  { {.state = 3U,  .symb = MUL   }, { .type = REDUCE, .num = 6U } },
  { {.state = 3U,  .symb = DIV   }, { .type = REDUCE, .num = 6U } }, //
  { {.state = 3U,  .symb = CL_BR }, { .type = REDUCE, .num = 6U } },
  { {.state = 3U,  .symb = END   }, { .type = REDUCE, .num = 6U } },

  { {.state = 4U,  .symb = ID    }, { .type = SHIFT,  .num = 5U } },
  { {.state = 4U,  .symb = NUM   }, { .type = SHIFT,  .num = 12U} }, //
  { {.state = 4U,  .symb = OP_BR }, { .type = SHIFT,  .num = 4U } },

  { {.state = 5U,  .symb = ADD   }, { .type = REDUCE, .num = 8U } },
  { {.state = 5U,  .symb = SUB   }, { .type = REDUCE, .num = 8U } }, //
  { {.state = 5U,  .symb = MUL   }, { .type = REDUCE, .num = 8U } },
  { {.state = 5U,  .symb = DIV   }, { .type = REDUCE, .num = 8U } }, //
  { {.state = 5U,  .symb = CL_BR }, { .type = REDUCE, .num = 8U } },
  { {.state = 5U,  .symb = END   }, { .type = REDUCE, .num = 8U } },

  { {.state = 6U,  .symb = ID    }, { .type = SHIFT,  .num = 5U } },
  { {.state = 6U,  .symb = NUM   }, { .type = SHIFT,  .num = 12U} }, //
  { {.state = 6U,  .symb = OP_BR }, { .type = SHIFT,  .num = 4U } },

  { {.state = 7U,  .symb = ID    }, { .type = SHIFT,  .num = 5U } },
  { {.state = 7U,  .symb = NUM   }, { .type = SHIFT,  .num = 12U} }, //
  { {.state = 7U,  .symb = OP_BR }, { .type = SHIFT,  .num = 4U } },

  { {.state = 8U,  .symb = ADD   }, { .type = SHIFT,  .num = 6U } },
  { {.state = 8U,  .symb = SUB   }, { .type = SHIFT,  .num = 13U} }, //
  { {.state = 8U,  .symb = CL_BR }, { .type = SHIFT,  .num = 11U} },

  { {.state = 9U,  .symb = ADD   }, { .type = REDUCE, .num = 1U } },
  { {.state = 9U,  .symb = SUB   }, { .type = REDUCE, .num = 1U } }, //
  { {.state = 9U,  .symb = MUL   }, { .type = SHIFT,  .num = 7U } },
  { {.state = 9U,  .symb = DIV   }, { .type = SHIFT,  .num = 15U} }, //
  { {.state = 9U,  .symb = CL_BR }, { .type = REDUCE, .num = 1U } },
  { {.state = 9U,  .symb = END   }, { .type = REDUCE, .num = 1U } },

  { {.state = 10U, .symb = ADD   }, { .type = REDUCE, .num = 4U } },
  { {.state = 10U, .symb = SUB   }, { .type = REDUCE, .num = 4U } }, //
  { {.state = 10U, .symb = MUL   }, { .type = REDUCE, .num = 4U } },
  { {.state = 10U, .symb = DIV   }, { .type = REDUCE, .num = 4U } }, //
  { {.state = 10U, .symb = CL_BR }, { .type = REDUCE, .num = 4U } },
  { {.state = 10U, .symb = END   }, { .type = REDUCE, .num = 4U } },

  { {.state = 11U, .symb = ADD   }, { .type = REDUCE, .num = 7U } },
  { {.state = 11U, .symb = SUB   }, { .type = REDUCE, .num = 7U } }, //
  { {.state = 11U, .symb = MUL   }, { .type = REDUCE, .num = 7U } },
  { {.state = 11U, .symb = DIV   }, { .type = REDUCE, .num = 7U } }, //
  { {.state = 11U, .symb = CL_BR }, { .type = REDUCE, .num = 7U } },
  { {.state = 11U, .symb = END   }, { .type = REDUCE, .num = 7U } },

  { {.state = 12U, .symb = ADD   }, { .type = REDUCE, .num = 6U } }, //
  { {.state = 12U, .symb = SUB   }, { .type = REDUCE, .num = 6U } }, //
  { {.state = 12U, .symb = MUL   }, { .type = REDUCE, .num = 6U } }, //
  { {.state = 12U, .symb = DIV   }, { .type = REDUCE, .num = 6U } }, //
  { {.state = 12U, .symb = CL_BR }, { .type = REDUCE, .num = 6U } }, //
  { {.state = 12U, .symb = END   }, { .type = REDUCE, .num = 6U } }, //

  { {.state = 13U, .symb = ID    }, { .type = SHIFT,  .num = 5U } }, //
  { {.state = 13U, .symb = NUM   }, { .type = SHIFT,  .num = 12U} }, //
  { {.state = 13U, .symb = OP_BR }, { .type = SHIFT,  .num = 4U } }, //

  { {.state = 14U, .symb = ADD   }, { .type = REDUCE, .num = 2U } }, //
  { {.state = 14U, .symb = SUB   }, { .type = REDUCE, .num = 2U } }, //
  { {.state = 14U, .symb = MUL   }, { .type = SHIFT,  .num = 7U } }, //
  { {.state = 14U, .symb = DIV   }, { .type = SHIFT,  .num = 15U} }, //
  { {.state = 14U, .symb = CL_BR }, { .type = REDUCE, .num = 2U } }, //
  { {.state = 14U, .symb = END   }, { .type = REDUCE, .num = 2U } }, //

  { {.state = 15U, .symb = ID    }, { .type = SHIFT,  .num = 5U } }, //
  { {.state = 15U, .symb = NUM   }, { .type = SHIFT,  .num = 12U} }, //
  { {.state = 15U, .symb = OP_BR }, { .type = SHIFT,  .num = 4U } }, //

  { {.state = 16U, .symb = ADD   }, { .type = REDUCE, .num = 5U } },
  { {.state = 16U, .symb = SUB   }, { .type = REDUCE, .num = 5U } }, //
  { {.state = 16U, .symb = MUL   }, { .type = REDUCE, .num = 5U } },
  { {.state = 16U, .symb = DIV   }, { .type = REDUCE, .num = 5U } }, //
  { {.state = 16U, .symb = CL_BR }, { .type = REDUCE, .num = 5U } },
  { {.state = 16U, .symb = END   }, { .type = REDUCE, .num = 5U } },
};

const Shift_reduce_parser::Goto_table Shift_reduce_parser::goto_table = {

  { {.state = 0U,  .symb = E}, 1U },
  { {.state = 0U,  .symb = T}, 2U },
  { {.state = 0U,  .symb = F}, 3U },

  { {.state = 4U,  .symb = E}, 8U },
  { {.state = 4U,  .symb = T}, 2U },
  { {.state = 4U,  .symb = F}, 3U },

  { {.state = 6U,  .symb = T}, 9U },
  { {.state = 6U,  .symb = F}, 3U },

  { {.state = 7U,  .symb = F}, 10U},

  { {.state = 13U, .symb = T}, 14U}, //
  { {.state = 13U, .symb = F}, 3U }, //

  { {.state = 15U, .symb = F}, 16U}, //
};

void Shift_reduce_parser::parse(const tokens_vector& tokens) {
  
  std::vector<unsigned int> state_stack;
  state_stack.push_back(0);

  size_t token_idx = 0;
  VERBOSE_PROLOGUE();

  while (true) {

    VERBOSE_ANNOTATE(tokens, token_idx, state_stack, iter_idx);

    unsigned int cur_state = state_stack.back();
    unsigned int cur_symb = token_to_terminal(*tokens[token_idx]);
  
    auto action_it = action_table.find({cur_state, cur_symb});

    if (action_it == action_table.end()) {
      throw std::runtime_error{"Syntax error"};
    }

    auto action = action_it->second;

    if (action.type == SHIFT) {
      
      shift(state_stack, action);
      ++token_idx;

    } else if (action.type == REDUCE) {
      reduce(state_stack, action);

    } else { 

      VERBOSE_MSG_ACCEPT();
      break;
    }

    VERBOSE_ITER();
  }
}

void Shift_reduce_parser::shift(std::vector<unsigned int>& state_stack, 
                                Shift_reduce_parser::Action action) {

  VERBOSE_MSG_SHIFT(action.num);
  state_stack.push_back(action.num);
}

void Shift_reduce_parser::reduce(std::vector<unsigned int>& state_stack,
                                 Shift_reduce_parser::Action action) {

  unsigned int prod_idx = action.num - 1;
  auto production = Parser::productions_[prod_idx];

  VERBOSE_MSG_REDUCE(action.num, production.str);

  for (unsigned int ct = 0; ct < production.len; ++ct) {
    state_stack.pop_back();
  }

  auto new_state = goto_table.find({state_stack.back(), production.header});

  if (new_state == goto_table.end()) {
    throw std::runtime_error{"Syntax error"};
  }

  state_stack.push_back(new_state->second);
}

unsigned int Shift_reduce_parser::token_to_terminal(const Lexer::Token& token) {

  auto token_class = token.token_class();

  if (token_class == Lexer::VAR_ID) {
    return Arithm::ID;

  } else if (token_class == Lexer::NUM) {
    return Arithm::NUM;

  } else if (token_class == Lexer::OPER) {

    auto token_value = dynamic_cast<const Lexer::Token_oper&>(token).value();

    switch (token_value) {
      case Lexer::Token_oper::ADD: return Arithm::ADD;
      case Lexer::Token_oper::SUB: return Arithm::SUB;
      case Lexer::Token_oper::MUL: return Arithm::MUL;
      case Lexer::Token_oper::DIV: return Arithm::DIV;

      default: throw std::invalid_argument{"Invalid token"};
    }

  } else if (token_class == Lexer::PUNCT) {

    auto token_value = dynamic_cast<const Lexer::Token_punct&>(token).value();

    switch (token_value) {
      case Lexer::Token_punct::OPENING_BR: return Arithm::OP_BR;
      case Lexer::Token_punct::CLOSING_BR: return Arithm::CL_BR;
      case Lexer::Token_punct::END:        return Arithm::END;

      default: throw std::invalid_argument{"Invalid token"};
    }
  } 

  throw std::invalid_argument{"Invalid token"};
}

}; // namespace Syntax
