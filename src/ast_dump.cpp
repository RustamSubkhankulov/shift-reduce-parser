#include <ast.hpp>

namespace AST {

#ifdef DUMP

void Ast::Node::dump_node(std::ostream& os) const {
      
  os << "NODE" << this << " [ label = \"";
  print(os);
  os << "\" ]; \n";

  for (const auto& child_ptr : children_) {

    os << "NODE" << this << " -> "
       << "NODE" << child_ptr.get() << std::endl;

    child_ptr->dump_node(os);
  }
}

void Ast::dump_tree(std::ostream& os) const {
    
  os << "digraph G{\n rankdir=TB;\n "
     << "node[ shape = doubleoctagon; style = filled ];\n"
     << "edge[ arrowhead = vee ];\n";

  root_->dump_node(os);

  os << "\n}\n";
}

#endif // DUMP

}; // namespace AST