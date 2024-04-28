#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include <vector>

namespace Grammar {

struct Production {
  unsigned int header;
  unsigned int len;
  std::string str;
};

}; // namespace Grammar

#endif // GRAMMAR_HPP
