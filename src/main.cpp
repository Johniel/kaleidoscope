#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <cassert>

#include "../lib/Sphingid/src/parser/parser.hpp"

#include "./ast/ast.hpp"

using namespace std;

using namespace kaleidoscope::ast;
using namespace sphingid::parser;

Parser* makeKaleidoscopeParser()
{
  Parser* identifierexp = Parser::rule("<IDENTIFIEREXPR>");
  Parser* parenexp      = Parser::rule("<PARENEXPR>");
  Parser* primary       = Parser::rule("<PRIMARY>");
  Parser* expression    = Parser::rule("<EXPRESSION>");
  Parser* prototype     = Parser::rule<Prototype>("<PROTOTYPE>");
  Parser* definition    = Parser::rule<FnDef>("<DEFINITION>");
  Parser* numberexp     = Parser::rule<kaleidoscope::ast::Number>("<NUMBEREXP>")->num();

  // identifierexpr
  //   ::= identifier
  //   ::= identifier '(' expression* ')'
  identifierexp->oneOf(Parser::rule<Var>()->id(),
                       Parser::rule<FnCall>()->id()->cons("(")->cons(")"),
                       Parser::rule<FnCall>()->id()->cons("(")->rep(expression)->cons(")"));

  // parenexp ::= '(' expression ')'
  parenexp->cons("(")->nt(expression)->cons(")");

  // primary
  //   ::= identifierexp
  //   ::= numberexpr
  //   ::= parenexp
  primary->oneOf(identifierexp, numberexp, parenexp);

  // expression
  //   ::= primary binoprhs
  expression->opL(primary, Parser::rule()->cons("+"), primary);

  // prototype
  //   ::= id '(' id* ')'
  prototype->id()->cons("(")->rep(Parser::rule()->id())->cons(")");

  // definition ::= 'def' prototype expression
  definition->cons("def")->nt(prototype)->nt(expression);

  /// toplevelexpr ::= expression
  Parser* program = Parser::rule<Root>("<PROGRAM>")->rep(expression);

  return program;
}

int main(int argc, char *argv[])
{
  Parser* kaleidoscope = makeKaleidoscopeParser();
  Lexer* lexer = new Lexer();
  kaleidoscope::ast::Root* root = (kaleidoscope::ast::Root*)kaleidoscope->parse(lexer);
  cout << root->str() << endl;
  return 0;
}
