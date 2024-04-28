#ifndef CONCRETE_ARITHM_AST_HPP
#define CONCRETE_ARITHM_AST_HPP

#include <string>

#include <ast.hpp>
#include <utility>
#include <concrete/arithm/grammar.hpp>

/*
 * Arithmetical grammar:
 *
 * - E -> E + T | E - T | T
 * - T -> T * F | T / F | F
 * - F -> (E) | id | num 
 */

namespace Arithm {

enum Aggr_node_type {
  EXPR = 0,
  TERM = 1,
  FACT = 2,
  NUM_AGGR_NODE_TYPES
};

const std::vector<AST::Production> Ast_productions = {

  /* (1) E -> E + T */
  {.header = Aggr_node_type::EXPR, .len = 3},

  /* (2) E -> E - T */
  {.header = Aggr_node_type::EXPR, .len = 3},

  /* (3) E -> T */
  {.header = Aggr_node_type::EXPR, .len = 1},

  /* (4) T -> T * F */
  {.header = Aggr_node_type::TERM, .len = 3},

  /* (5) T -> T / F */
  {.header = Aggr_node_type::TERM, .len = 3},

  /* (6) T -> F */
  {.header = Aggr_node_type::TERM, .len = 1},

  /* (7) F -> (E) */
  {.header = Aggr_node_type::FACT, .len = 1},

  /* (8) F -> id */
  {.header = Aggr_node_type::FACT, .len = 1},

  /* (9) F -> num */
  {.header = Aggr_node_type::FACT, .len = 1},

};

using Basic_ast_node = AST::Ast::Node;

class Id_node : public Basic_ast_node {

  std::string value_;

public:

  Id_node(const std::string& value):
    value_(value) {}

  void print(std::ostream& ostream) const override {
    ostream << value_;
  }

};

class Num_node : public Basic_ast_node {

  int value_;

public:

  Num_node(int value):
    value_(value) {}

  void print(std::ostream& ostream) const override {
    ostream << value_;
  }
};

class Op_node : public Basic_ast_node {

  unsigned int value_;

public:

  Op_node(unsigned int value):
    value_(value) {}

  void print(std::ostream& ostream) const override {
    
    char symb;

    switch(value_) {
      case ADD: symb = '+'; break;
      case SUB: symb = '-'; break;
      case MUL: symb = '*'; break;
      case DIV: symb = '/'; break;
      default:  symb = '?'; break;
    }

    ostream << symb;
  }
};

class Expr_node : public Basic_ast_node {

public:

  Expr_node(std::vector<std::unique_ptr<Node>>&& children):
    Basic_ast_node(std::move(children)) {}

  void print(std::ostream& ostream) const override {
    ostream << "E";
  }

};

class Term_node : public Basic_ast_node {

public:

  Term_node(std::vector<std::unique_ptr<Node>>&& children):
    Basic_ast_node(std::move(children)) {}

  void print(std::ostream& ostream) const override {
    ostream << "T";
  }

};

class Factor_node : public Basic_ast_node {

public:

  Factor_node(std::vector<std::unique_ptr<Node>>&& children):
    Basic_ast_node(std::move(children)) {}

  void print(std::ostream& ostream) const override {
    ostream << "F";
  }

};

}; // ARITHM

#endif // CONCRETE_ARITHM_AST_HPP
