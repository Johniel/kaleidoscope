#include "parser.hpp"

using namespace kaleidoscope::parser;

namespace {};

Parser::Parser()
{
  this->lexer_ = new Lexer();
}

Token* Parser::getNextToken(void)
{
  curr_token_ = this->lexer_->front();
  this->lexer_->pop();
  return this->curr_token_;
}

/// expression
///   ::= primary binoprhs
///
Exp* Parser::parseExpression(void)
{
  Exp* left = this->parsePrimary();
  if (!left) return NULL;

  return this->parseBinOpR(NULL, left);
}

/// prototype
///   ::= id '(' id* ')'
kaleidoscope::ast::Prototype* Parser::parsePrototype(void)
{
  if (dynamic_cast<IdentifierToken*>(this->curr_token_) == NULL) {
    return errorProt("Expected function name in prototype");
  }

  std::string fn_name = IdentifierStr;
  getNextToken();

  if (CurTok != '(')
    return ErrorP("Expected '(' in prototype");

  std::vector<std::string> ArgNames;
  while (getNextToken() == tok_identifier)
    ArgNames.push_back(IdentifierStr);
  if (CurTok != ')')
    return ErrorP("Expected ')' in prototype");

  // success.
  getNextToken();  // eat ')'.

  return new Prototype(fn_name, ArgNames);
}
