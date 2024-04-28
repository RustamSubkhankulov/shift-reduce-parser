#ifndef SR_VERBOSE_SUPPORT_HPP
#define SR_VERBOSE_SUPPORT_HPP

#ifdef VERBOSE

  #define VERBOSE_PROLOGUE()            \
    unsigned int iter_idx = 0U;         \
    verbose_write_header();       

  #define VERBOSE_ANNOTATE(tokens, token_idx, state_stack, iter_idx)  \
    verbose_annotate(tokens, token_idx, state_stack, iter_idx);

  #define VERBOSE_ITER()                \
    std::clog << std::endl;             \
    verbose_write_separator();          \
    ++iter_idx;

  #define VERBOSE_EPILOGUE()            \
    std::clog << std::endl;             \
    verbose_write_separator();

  #define VERBOSE_MSG_SHIFT(num)        \
    verbose_print_str_aligned("SHIFT "  + std::to_string(num));

  #define VERBOSE_MSG_REDUCE(num, str)  \
    verbose_print_str_aligned("REDUCE " + std::to_string(num) + " " + str);

  #define VERBOSE_MSG_ACCEPT()          \
    verbose_print_str_aligned("ACCEPT");

#else 

  #define VERBOSE_PROLOGUE()
  #define VERBOSE_ANNOTATE(tokens, token_idx, state_stack, iter_idx)
  #define VERBOSE_ITER()
  #define VERBOSE_EPILOGUE()

  #define VERBOSE_MSG_SHIFT(num)
  #define VERBOSE_MSG_REDUCE(num, str)
  #define VERBOSE_MSG_ACCEPT()

#endif

#endif // SR_VERBOSE_SUPPORT_HPP
