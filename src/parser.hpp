#ifndef _PARSER_H_
#define _PARSER_H_

#include <map>
#include <string>

#include "ast.hpp"
#include "lexer.hpp"

using namespace kaleidoscope::ast;
using namespace kaleidoscope::lexer;

namespace kaleidoscope {
  namespace parser {

    class Parser {
    private:
      std::map<char, int> binop_precedence_;
    public:
      Token* getNextToken(void);
      kaleidoscope::ast::Exp* parseExpression(void);
      kaleidoscope::ast::Exp* parseIdentifierExpr(void);
      kaleidoscope::ast::Exp* parseNumberExpr(void);
      kaleidoscope::ast::Exp* parseParenExpr(void);
      kaleidoscope::ast::Exp* parsePrimary(void);
      kaleidoscope::ast::Exp* parseBinOpR(int, Exp*);
      kaleidoscope::ast::Prototype* parsePrototype(void);
      kaleidoscope::ast::Function*  parseDefinition(void);
      kaleidoscope::ast::Function*  parseTopLevelExpr(void);
      kaleidoscope::ast::Prototype* parseExtern(void);
    };

  };
};

#endif /* _PARSER_H_ */
