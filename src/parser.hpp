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
      Token* curr_token_ = NULL;
    public:
      std::map<char, int> binop_precedence_;
      kaleidoscope::lexer::Lexer* lexer_;

      Parser();

      Exp *error(const char *str) { fprintf(stderr, "Error: %s\n", str); return NULL; }
      Prototype *errorProt(const char *str) { error(str); return NULL; }

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
