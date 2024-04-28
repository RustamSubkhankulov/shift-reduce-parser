#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <memory>
#include <iostream>

namespace AST {

struct Production {
  unsigned int header;
  unsigned int len;
};

extern const std::vector<Production> Ast_productions;

class Ast {

public:

  class Node {

  std::vector<std::unique_ptr<Node>> children_;

  public:

    Node() {}

    Node(std::vector<std::unique_ptr<Node>>&& children):
      children_(std::move(children)) {}

    virtual ~Node() {}

    void add_child(std::unique_ptr<Node>&& child) {
      children_.push_back(std::move(child));
    }

#ifdef DUMP
    void dump_node(std::ostream& os) const;
#endif

  virtual void print(std::ostream& os) const = 0;
  };

private:

  std::unique_ptr<Node> root_;

public:

  Ast(std::unique_ptr<Node>&& root = nullptr):
    root_(std::move(root)) {}

  void set_root(std::unique_ptr<Node>&& root) {
    root_ = std::move(root);
  }

  virtual ~Ast() {}

#ifdef DUMP
  void dump_tree(std::ostream& os) const;
#endif
};

}; // namespace AST

#endif // AST_HPP
