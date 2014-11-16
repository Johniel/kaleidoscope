#ifndef _AST_H_
#define _AST_H_

#include <string>
#include <vector>

namespace kaleidoscope {

  namespace ast {

    class Node {
    public:
      virtual ~Node() {}
      virtual Node* parse() = 0;
    };

    class Exp : public Node {
    };

    class Num : public Exp {
      double num_;
    public:
      Num(double num) : num_(num) {}
    };

    class Var : public Exp {
      std::string Name;
    public:
      Var(const std::string &name) : Name(name) {}
    };

    class BinaryOp : public Exp {
      char op_;
      Node *left_, *right_;
    public:
      BinaryOp(char op, Node *left, Node *right)
        : op_(op), left_(left), right_(right) {}
    };

    class FnCall : public Exp {
      std::string fn_name_;
      std::vector<Node*> args_;
    public:
      FnCall(const std::string &fn_name, std::vector<Node*> &args)
        : fn_name_(fn_name), args_(args) {}
    };

    class Prototype : public kaleidoscope::ast::Node {
      std::string fn_name_;
      std::vector<std::string> args_;
    public:
      Prototype(const std::string &fn_name, const std::vector<std::string> &args)
        : fn_name_(fn_name), args_(args) {}
    };

    class Function : public kaleidoscope::ast::Node {
      Prototype *proto_;
      kaleidoscope::ast::Node *body_;
    public:
      Function(Prototype *proto, kaleidoscope::ast::Node *body)
        : proto_(proto), body_(body) {}
    };
  };
};

#endif /* _AST_H_ */
