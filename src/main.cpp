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
  Parser* identifier = Parser::rule("<IDENTIFIEREXPR>");
  Parser* parenexp   = Parser::rule("<PARENEXPR>");
  Parser* primary    = Parser::rule<Exp>("<PRIMARY>");
  Parser* expression = Parser::rule("<EXPRESSION>");
  Parser* prototype  = Parser::rule<Prototype>("<PROTOTYPE>");
  Parser* definition = Parser::rule<FnDef>("<DEFINITION>");
  Parser* numberexp  = Parser::rule<kaleidoscope::ast::Number>("<NUMBEREXP>")->num();
  Parser* variable   = Parser::rule<Var>("<VARIABLE>")->id({"(", ")", "<", ">", "{", "}", "[", "]"});
  Parser* ifexp      = Parser::rule<IfExp>("IF");

  // identifierexpr
  //   ::= identifier
  //   ::= identifier '(' expression* ')'
  identifier->oneOf(Parser::rule<FnCall>("<FUN CALL>")->nt(variable)->cons("(")->cons(")"),
                    Parser::rule<FnCall>("<FUN CALL ARGS>")->nt(variable)->cons("(")->rep(expression)->cons(")"),
                    variable);

  // parenexp ::= '(' expression ')'
  parenexp->cons("(")->nt(expression)->cons(")");

  // ifexp :== if expression then expression else expression
  ifexp->cons("if")->nt(expression)->cons("then")->nt(expression)->cons("else")->nt(expression);

  // primary
  //   ::= identifierexp
  //   ::= numberexpr
  //   ::= parenexp
  primary->oneOf(ifexp, identifier, numberexp, parenexp);

  // expression
  //   ::= primary binoprhs
  expression->oneOf(Parser::rule<BinaryOp>()->nt(primary)->cons("+")->nt(expression),
                    Parser::rule<BinaryOp>()->nt(primary)->cons("-")->nt(expression),
                    primary);

  // prototype
  //   ::= id '(' id* ')'
  prototype->cons("def")->nt(variable)->cons("(")->rep(variable)->cons(")");

  // definition ::= 'def' prototype expression
  definition->nt(prototype)->nt(expression);

  /// toplevelexpr ::= expression
  Parser* program = Parser::rule<Root>("<PROGRAMS>")->rep(Parser::rule("<PROGRAM>")->oneOf(definition, expression));

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
