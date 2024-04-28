#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include <vector>

namespace Grammar {

struct Production {
  unsigned int header;
  unsigned int len;
  std::string str;
};

extern const std::vector<Production> Grammar_productions;

}; // namespace Grammar

#endif // GRAMMAR_HPP
