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
  unsigned int nonterminal;
  unsigned int len;
  std::string str;
};

const std::vector<Production> Productions = {

  /* (1) E -> E + T */
  {.nonterminal = Nonterminal::E, .len = 3, .str = "E->E+T"},

  /* (2) E -> E - T */
  {.nonterminal = Nonterminal::E, .len = 3, .str = "E->E-T"},

  /* (3) E -> T */
  {.nonterminal = Nonterminal::E, .len = 1, .str = "E->T"},

  /* (4) T -> T * F */
  {.nonterminal = Nonterminal::T, .len = 3, .str = "T->T*F"},

  /* (5) T -> T / F */
  {.nonterminal = Nonterminal::T, .len = 3, .str = "T->T/F"},

  /* (6) T -> F */
  {.nonterminal = Nonterminal::T, .len = 1, .str = "T->F"},

  /* (7) F -> (E) */
  {.nonterminal = Nonterminal::F, .len = 3, .str = "F->(E)"},

  /* (8) F -> id */
  {.nonterminal = Nonterminal::F, .len = 1, .str = "F->id"},

  /* (9) F -> num */
  {.nonterminal = Nonterminal::F, .len = 1, .str = "F->num"},

};

}; // namespace Grammar

#endif // GRAMMAR_HPP