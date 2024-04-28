#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <memory>
#include <iostream>

namespace AST {

class Ast {

public:

  class Node {

  std::vector<std::unique_ptr<Node*>> children_;

  public:

    Node() {}

    Node(std::vector<std::unique_ptr<Node*>>&& children):
      children_(std::move(children)) {}

    virtual ~Node() {}

    void add_child(std::unique_ptr<Node*>&& child) {
      children_.push_back(std::move(child));
    }

    void dump_node(std::ostream& ostream, unsigned depth = 0) const {
      
      auto children_ct = children_.size();
      auto half = std::ceil(children_ct / 2);

      for (decltype(children_ct) idx = 0; idx < half; ++idx) {
        (*children_[idx])->dump_node(ostream, depth + 1);
      }

      for (unsigned idx = 0; idx < depth; ++idx) {
        ostream << '\t';
      }

      print(ostream);

      for (decltype(children_ct) idx = half; idx < children_ct; ++idx) {
        (*children_[idx])->dump_node(ostream, depth + 1);
      }
    }

    virtual void print(std::ostream& ostream) const = 0;
  };

private:

  std::unique_ptr<Node*> root_;

public:

  Ast(std::unique_ptr<Node*>&& root = nullptr):
    root_(std::move(root)) {}

  virtual ~Ast() {}

  void dump_tree(std::ostream& ostream) const {
    (*root_)->dump_node(ostream);
  }
};

}; // namespace AST

#endif // AST_HPP
