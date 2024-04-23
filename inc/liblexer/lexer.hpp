#ifndef LEXER_HPP
#define LEXER_HPP

#include <cstdlib>
#include <string>
#include <iostream>
#include <typeinfo>
#include <iomanip>
#include <vector>
#include <memory>

namespace Lexer {

enum class Token_class {

  KWORD,    /* Keyword. */
  TYPE_ID,  /* Type identifier. */
  VAR_ID,   /* Variable identifier. */
  NUM,      /* Constant number. */
  STR,      /* String literal. */
  OPER,     /* Operator. */
  PUNCT     /* Punctuator. */
};

class Token {

private:

  Token_class token_class_;

protected:

  Token(Token_class token_class):
    token_class_(token_class) {}

public:

  virtual ~Token() {}

  Token_class token_class() const {
    return token_class_;
  }

  virtual std::string class_str() const = 0;
  virtual std::string value_str() const = 0;
};

template<typename CharT>
std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const Token& token) {

  os << "{\"class\":\"" << token.class_str() << "\",\"value\":\"" << token.value_str() << "\"}";
  return os;
}

//--------------------

class Token_kword : public Token {

public:

  enum Value {
    TRUE, FALSE, ELSE, IF, LOOP, THEN, WHILE, NOT, PRINT, PRINTLN
  };

private:

  Value value_;

public:

  Token_kword(Value value):
    Token(Token_class::KWORD),
    value_(value) {}

  std::string class_str() const override {
    return std::string("KWORD");
  }

  std::string value_str() const override {
    
    switch(value_) {
      case Value::ELSE:    return "ELSE";
      case Value::FALSE:   return "FALSE";
      case Value::IF:      return "IF";
      case Value::LOOP:    return "LOOP";
      case Value::THEN:    return "THEN";
      case Value::WHILE:   return "WHILE";
      case Value::NOT:     return "NOT";
      case Value::TRUE:    return "TRUE";
      case Value::PRINT:   return "PRINT";
      case Value::PRINTLN: return "PRINTLN";
      default: exit(EXIT_FAILURE);
    }
  }
};

//--------------------

class Token_type_id : public Token {

private:

  std::string value_;

public:

  Token_type_id(std::string value):
    Token(Token_class::TYPE_ID),
    value_(value) {}

  std::string class_str() const override {
    return std::string("TYPE_ID");
  }

  std::string value_str() const override {
    return value_;
  }
};

//--------------------

class Token_var_id : public Token {

private:

  std::string value_;

public:

  Token_var_id(std::string value):
    Token(Token_class::VAR_ID),
    value_(value) {}

  std::string class_str() const override {
    return std::string("VAR_ID");
  }

  std::string value_str() const override {
    return value_;
  }
};

//--------------------

template<typename T>
class Token_num : public Token {

private:

  T value_;

public:

  Token_num(T value):
    Token(Token_class::NUM),
    value_(value) {}

  std::string class_str() const override {
    return std::string("NUM") + typeid(T).name();
  }

  std::string value_str() const override {
    return std::to_string(value_);
  }
};


//--------------------

class Token_str : public Token {

private:

  std::string value_;

public:

  Token_str(std::string value):
    Token(Token_class::STR),
    value_(value) {}

  std::string class_str() const override {
    return std::string("STR");
  }

  std::string value_str() const override {
    return value_;
  }
};

//--------------------

class Token_oper : public Token {

public:

  enum Value {
    ADD, SUB, MUL, DIV, ASS, AND, OR, XOR, NEG
  };

private:

  Value value_;

public:

  Token_oper(Value value):
    Token(Token_class::OPER),
    value_(value) {}

  std::string class_str() const override {
    return std::string("OPER");
  }

  std::string value_str() const override {
    
    switch(value_) {
      case Value::ADD: return "ADD";
      case Value::SUB: return "ADD";
      case Value::MUL: return "MUL";
      case Value::DIV: return "DIV";
      case Value::ASS: return "ASS";
      case Value::NEG: return "NEG";
      case Value::AND: return "AND";
      case Value::XOR: return "XOR";
      case Value::OR:  return "OR";
      default: exit(EXIT_FAILURE);
    }
  }
};

//--------------------

class Token_punct : public Token {

public:

  enum Value {
    OPENING_BR, CLOSING_BR
  };

private:

  Value value_;

public:

  Token_punct(Value value):
    Token(Token_class::TYPE_ID),
    value_(value) {}

  std::string class_str() const override {
    return std::string("PUNCT");
  }

  std::string value_str() const override {
    
    switch(value_) {
      case Value::OPENING_BR: return "OPENING_BR";
      case Value::CLOSING_BR: return "CLOSING_BR";
      default: exit(EXIT_FAILURE);
    }
  }
};

extern std::vector<std::unique_ptr<Token>> Tokens_parsed;
const std::vector<std::unique_ptr<Token>>& get_tokens();

}; // namespace Lexer

#endif