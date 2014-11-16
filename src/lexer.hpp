#ifndef _LEXER_H_
#define _LEXER_H_

#include <vector>
#include <string>

namespace kaleidoscope {
  namespace lexer {

    class Token
    {
    public:
      virtual std::string toString(void) const = 0;
      virtual ~Token() {}
    private:
      int line_;
      int column_;
    };

    class EofToken : public Token
    {
      virtual std::string toString(void) const { return ""; }
    };

    class DefToken : public Token
    {
    public:
      virtual std::string toString(void) const { return ""; }
      virtual ~DefToken() {}
      DefToken() {}
    };

    class ExternToken : public Token
    {
    public:
      virtual std::string toString(void) const { return ""; }
    };

    class IdentifierToken : public Token
    {
    public:
      IdentifierToken(std::string str) { str_ = str; }
      virtual std::string toString(void) const { return ""; }
    private:
      std::string str_;
    };

    class NumToken : public Token
    {
    public:
      NumToken(std::string str) { str_ = str; }
      virtual std::string toString(void) const { return ""; }
    private:
      std::string str_;
    };

    class Lexer {
    public:
      Lexer();
      Token* peek(int nth);
      Token* front(void);
      void pop(void);
    private:
      char readChar(void);
      Token* readToken(void);
      std::vector<Token*> tokens_;
    };

  }; // lexer
}; // kaleidoscope


#endif /* _LEXER_H_ */
