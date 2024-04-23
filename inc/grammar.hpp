#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include <vector>

namespace Grammar {

enum Nonterminal {
  E = 0,
  T = 1,
  F = 2,
  NUM_NONTERNINALS
};

enum Terminal {
  ID    = 0,
  NUM   = 1,
  ADD   = 2,
  SUB   = 3,
  MUL   = 4,
  DIV   = 5,
  OP_BR = 6,
  CL_BR = 7,
  END   = 8,
  NUM_TERMINALS
};

struct Production {
  Nonterminal left_side;
  unsigned len;
};

const std::vector<Production> Productions = {

  /* (0) E -> E + T */
  {.left_side = Nonterminal::E, .len = 3},

  /* (1) E -> E - T */
  {.left_side = Nonterminal::E, .len = 3},

  /* (2) E -> T */
  {.left_side = Nonterminal::E, .len = 1},

  /* (3) T -> T * F */
  {.left_side = Nonterminal::T, .len = 3},

  /* (4) T -> T / F */
  {.left_side = Nonterminal::T, .len = 3},

  /* (5) T -> F */
  {.left_side = Nonterminal::T, .len = 1},

  /* (6) F -> (E) */
  {.left_side = Nonterminal::F, .len = 3},

  /* (7) F -> id */
  {.left_side = Nonterminal::F, .len = 1},

  /* (8) F -> num */
  {.left_side = Nonterminal::F, .len = 1},

};

}; // namespace Grammar

#endif // GRAMMAR_HPP