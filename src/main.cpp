#include <iostream>
#include <set>
#include <map>
#include <vector>

#include "../lib/Sphingid/src/parser/parser.hpp"

using namespace std;
using namespace sphingid::parser;
using namespace sphingid::ast;

Parser* makeKaleidoscopeParser()
{
  Parser* identifierexpr = Parser::rule("<IDENTIFIEREXPR>")
  Parser* parenexpr      = Parser::rule("<PARENEXPR>");
  Parser* primary        = Parser::rule("<PRIMARY>");
  Parser* binoprhs       = Parser::rule("<BINOPRHS>");
  Parser* expression     = Parser::rule("<EXPRESSION>");
  Parser* prototype      = Parser::rule("<PROTOTYPE>");
  Parser* definition     = Parser::rule("<DEFINITION>");
  Parser* toplevelexpr   = Parser::rule("<TOPLEVELEXPR>");
  Parser* external       = Parser::rule("<EXTERNAL>");
  Parser* numberexp      = Parser::rule("<NUMBEREXP>")->num();

  // identifierexpr
  //   ::= identifier
  //   ::= identifier '(' expression* ')'
  identifierexpr->oneOf(Parser::rule()->id(),
                        Parser::rule()->id()->cons("(")->cons(")"),
                        Parser::rule()->id()->cons("(")->rep(expression)->cons(")"));

  // parenexpr ::= '(' expression ')'
  parenexpr->cons("(")->nt(expression)->cons(")");

  // primary
  //   ::= identifierexpr
  //   ::= numberexpr
  //   ::= parenexpr
  primary->oneOf(identifierexpr, numberexpr, parenexpr);

  // binoprhs
  //   ::= ('+' primary)*
  binoprhs->rep(Parser::rule()->cons("+")->nt(primary));


  // expression
  //   ::= primary binoprhs
  expression->nt(primary)->nt(binoprhs);

  // prototype
  //   ::= id '(' id* ')'
  prototype->id()->cons("(")->rep(Parser::rule()->id())->cons(")");

  // definition ::= 'def' prototype expression
  definition->cons("def")->nt(prototype)->nt(expression);

  /// toplevelexpr ::= expression
  toplevelexpr->nt(expression);

  return toplevelexpr;
}

int main(int argc, char *argv[])
{
  // arithmetic();
  // add_op();
  // sphingid_syntax();
  Parser* kaleidoscope = makeKaleidoscopeParser();

  return 0;
}
