#include "shift_reduce.hpp"

namespace Syntax {

using namespace Grammar;

const Shift_reduce_parser::Action_table Shift_reduce_parser::action_table = {

  { {.state = 0U,  .symb = ID    }, { .type = SHIFT,  .num = 5U } },
  { {.state = 0U,  .symb = OP_BR }, { .type = SHIFT,  .num = 4U } },

  { {.state = 1U,  .symb = ADD   }, { .type = SHIFT,  .num = 6U } },
  { {.state = 1U,  .symb = END   }, { .type = ACCEPT            } },

  { {.state = 2U,  .symb = ADD   }, { .type = REDUCE, .num = 2U } },
  { {.state = 2U,  .symb = MUL   }, { .type = SHIFT,  .num = 7U } },
  { {.state = 2U,  .symb = CL_BR }, { .type = REDUCE, .num = 2U } },
  { {.state = 2U,  .symb = END   }, { .type = REDUCE, .num = 2U } },

  { {.state = 3U,  .symb = ADD   }, { .type = REDUCE, .num = 4U } },
  { {.state = 3U,  .symb = MUL   }, { .type = REDUCE, .num = 4U } },
  { {.state = 3U,  .symb = CL_BR }, { .type = REDUCE, .num = 4U } },
  { {.state = 3U,  .symb = END   }, { .type = REDUCE, .num = 4U } },

  { {.state = 4U,  .symb = ID    }, { .type = SHIFT,  .num = 5U } },
  { {.state = 4U,  .symb = OP_BR }, { .type = SHIFT,  .num = 4U } },

  { {.state = 5U,  .symb = ADD   }, { .type = REDUCE, .num = 6U } },
  { {.state = 5U,  .symb = MUL   }, { .type = REDUCE, .num = 6U } },
  { {.state = 5U,  .symb = CL_BR }, { .type = REDUCE, .num = 6U } },
  { {.state = 5U,  .symb = END   }, { .type = REDUCE, .num = 6U } },

  { {.state = 6U,  .symb = ID    }, { .type = SHIFT,  .num = 5U } },
  { {.state = 6U,  .symb = OP_BR }, { .type = SHIFT,  .num = 4U } },

  { {.state = 7U,  .symb = ID    }, { .type = SHIFT,  .num = 5U } },
  { {.state = 7U,  .symb = OP_BR }, { .type = SHIFT,  .num = 4U } },

  { {.state = 8U,  .symb = ADD   }, { .type = SHIFT,  .num = 6U } },
  { {.state = 8U,  .symb = CL_BR }, { .type = SHIFT,  .num = 11U} },

  { {.state = 9U,  .symb = ADD   }, { .type = REDUCE, .num = 1U } },
  { {.state = 9U,  .symb = MUL   }, { .type = SHIFT,  .num = 7U } },
  { {.state = 9U,  .symb = CL_BR }, { .type = REDUCE, .num = 1U } },
  { {.state = 9U,  .symb = END   }, { .type = REDUCE, .num = 1U } },

  { {.state = 10U, .symb = ADD   }, { .type = REDUCE, .num = 3U } },
  { {.state = 10U, .symb = MUL   }, { .type = REDUCE, .num = 3U } },
  { {.state = 10U, .symb = CL_BR }, { .type = REDUCE, .num = 3U } },
  { {.state = 10U, .symb = END   }, { .type = REDUCE, .num = 3U } },

  { {.state = 11U, .symb = ADD   }, { .type = REDUCE, .num = 5U } },
  { {.state = 11U, .symb = MUL   }, { .type = REDUCE, .num = 5U } },
  { {.state = 11U, .symb = CL_BR }, { .type = REDUCE, .num = 5U } },
  { {.state = 11U, .symb = END   }, { .type = REDUCE, .num = 5U } }
};

const Shift_reduce_parser::Goto_table Shift_reduce_parser::goto_table = {

  { {.state = 0U, .symb = E}, 1U },
  { {.state = 0U, .symb = T}, 2U },
  { {.state = 0U, .symb = F}, 3U },

  { {.state = 4U, .symb = E}, 8U },
  { {.state = 4U, .symb = T}, 2U },
  { {.state = 4U, .symb = F}, 3U },

  { {.state = 6U, .symb = E}, 9U },
  { {.state = 6U, .symb = T}, 3U },

  { {.state = 7U, .symb = E}, 10U}
};

void Shift_reduce_parser::parse(const tokens_vector& tokens) {
  
  std::stack<unsigned int> state_stack;
  size_t token_idx = 0;

  while (true) {

    
  }
}

}; // namespace Syntax