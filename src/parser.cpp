#include "parser.hpp"

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'


/// primary
///   ::= identifierexpr
///   ::= numberexpr
///   ::= parenexpr


/// binoprhs
///   ::= ('+' primary)*


/// expression
///   ::= primary binoprhs
///

/// prototype
///   ::= id '(' id* ')'

/// definition ::= 'def' prototype expression

/// toplevelexpr ::= expression

/// external ::= 'extern' prototype
