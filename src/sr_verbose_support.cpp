#include <stdexcept>
#include <cstring>
#include <string>

#include "shift_reduce.hpp"
#include "sr_verbose_support.hpp"

namespace Syntax {

#ifdef VERBOSE

void Shift_reduce_parser::verbose_write_header() {

  verbose_write_separator();

  std::clog << "|ITER|" 
            << std::setw(Table_entry_width) << std::left << "STACK" << "|"
            << std::setw(Table_entry_width) << std::left << "INPUT" << "|"
            << std::setw(Table_entry_width) << std::left << "ACTION"
            << "|\n";

  verbose_write_separator();
}

void Shift_reduce_parser::verbose_write_separator() {

  std::clog << " ";
  for (unsigned idx = 0; idx < Table_entry_width * 3 + 7; ++idx) {
    std::clog << "-";
  }
  std::clog << std::endl;
}

void Shift_reduce_parser::verbose_print_str_aligned(const std::string& str) {

  std::string to_print = str + std::string(Table_entry_width - str.size(), ' ');
  std::clog << to_print << "|";
}

void Shift_reduce_parser::verbose_annotate(const tokens_vector& tokens, size_t token_idx, 
                                           const std::vector<unsigned int>& state_stack, 
                                           unsigned iter_idx) {

  std::clog << "|" << std::setw(4) << iter_idx << "|";

  std::string str;

  for (auto it = state_stack.begin(); it != state_stack.end(); ++it) {
    str += std::to_string(*it) + " ";
  }
  
  verbose_print_str_aligned(str);
  str.clear();

  for (size_t idx = token_idx; idx < tokens.size(); ++idx) {
    str += tokens[idx]->value_str() + " ";
  }

  verbose_print_str_aligned(str);
}

#endif // VERBOSE

}; // namespace Syntax
