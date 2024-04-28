#ifndef CONCRETE_ARITHM_AST_HPP
#define CONCRETE_ARITHM_AST_HPP

#include <string>

#include <ast.hpp>

/*
 * Arithmetical grammar:
 *
 * - E -> E + T | E - T | T
 * - T -> T * F | T / F | F
 * - F -> (E) | id | num 
 */

namespace Arithm {

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

  Expr_node() {}

  void print(std::ostream& ostream) const override {
    ostream << "E";
  }

};

class Term_node : public Basic_ast_node {

public:

  Term_node() {}

  void print(std::ostream& ostream) const override {
    ostream << "T";
  }

};

class Factor_node : public Basic_ast_node {

public:

  Factor_node() {}

  void print(std::ostream& ostream) const override {
    ostream << "F";
  }

};

}; // ARITHM

#endif // CONCRETE_ARITHM_AST_HPP
