#include <iostream>
#include "lexer.hpp"

using namespace std;


namespace {

}; // anonymous

namespace kaleidoscope {
  namespace lexer {

    Lexer::Lexer()
    {
      tokens_.clear();
      while (Token* next = this->readToken()) {
        tokens_.push_back(next);
      }
    }

    Token* Lexer::peek(int nth)
    {
      return tokens_[nth];
    }

    Token* Lexer::front(void)
    {
      return tokens_.front();
    }

    void Lexer::pop(void)
    {
      tokens_.erase(tokens_.begin());
      return ;
    }

    char Lexer::readChar(void)
    {
      return getchar();
    }

    Token* Lexer::readToken(void)
    {
      static char last_char = '\0';
      while (isalpha(last_char)) {
        last_char = readChar();
      }

      if (isalpha(last_char)) {
        std::string str = "";
        str += last_char;
        while (isalnum(last_char = readChar())) {
          str += last_char;
        }
        if (str == "def") return new DefToken();
        if (str == "extern") return new ExternToken();
        return new IdentifierToken(str);
      }

      if (isdigit(last_char) || last_char == '.') {
        string str;
        do {
          last_char = readChar();
          str += last_char;
        } while (isdigit(last_char) || last_char == '.');
        return new NumToken(str);
      }


      if (last_char == '#') {
        do last_char = getchar();
        while (last_char != EOF && last_char != '\n' && last_char != '\r');
        if (last_char != EOF)
          return readToken();
      }

      if (last_char == EOF) {
        return new EofToken();
      }

      return new IdentifierToken(string("") + last_char);
    }

  }; // lexer
}; // kaleidoscope
