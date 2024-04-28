#ifndef CONCRETE_ARITHM_GRAMMAR_HPP
#define CONCRETE_ARITHM_GRAMMAR_HPP

#include <grammar.hpp>

/*
 * Arithmetical grammar:
 *
 * - E -> E + T | E - T | T
 * - T -> T * F | T / F | F
 * - F -> (E) | id | num 
 */

namespace Arithm {

enum Nonterminal {
  E = 0,
  T = 1,
  F = 2,
  NUM_NONTERNINALS
};

enum Terminal {
  ID    = 0,
  NUM   = 1,
  ADD   = 3,
  SUB   = 4,
  MUL   = 5,
  DIV   = 6,
  OP_BR = 7,
  CL_BR = 8,
  END   = 9,
  NUM_TERMINALS
};

const std::vector<Grammar::Production> Productions = {

  /* (1) E -> E + T */
  {.header = Nonterminal::E, .len = 3, .str = "E->E+T"},

  /* (2) E -> E - T */
  {.header = Nonterminal::E, .len = 3, .str = "E->E-T"},

  /* (3) E -> T */
  {.header = Nonterminal::E, .len = 1, .str = "E->T"},

  /* (4) T -> T * F */
  {.header = Nonterminal::T, .len = 3, .str = "T->T*F"},

  /* (5) T -> T / F */
  {.header = Nonterminal::T, .len = 3, .str = "T->T/F"},

  /* (6) T -> F */
  {.header = Nonterminal::T, .len = 1, .str = "T->F"},

  /* (7) F -> (E) */
  {.header = Nonterminal::F, .len = 3, .str = "F->(E)"},

  /* (8) F -> id */
  {.header = Nonterminal::F, .len = 1, .str = "F->id"},

  /* (9) F -> num */
  {.header = Nonterminal::F, .len = 1, .str = "F->num"},

};

}; // ARITHM

#endif // CONCRETE_ARITHM_GRAMMAR_HPP
