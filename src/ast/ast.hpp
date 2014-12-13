#ifndef _AST_H_
#define _AST_H_

#include <string>
#include <vector>

#include <cassert>

#include "../../lib/Sphingid/src/ast/ast.hpp"
#include "../../lib/Sphingid/src/parser/lexer.hpp"

namespace kaleidoscope {
  namespace ast {

    class Exp : public sphingid::ast::Node
    {
    };

    class Number : public Exp
    {
    public:
      Number(int n) : n_(n) {}
      virtual std::string str(void)
      {
        char buff[100];
        sprintf(buff, "%d", n_);
        return std::string(buff);
      }
      static sphingid::ast::Node* make(std::vector<sphingid::ast::Node*> v)
      {
        assert(v.size() == 1);
        assert(dynamic_cast<sphingid::ast::NumLiteralNode*>(v[0]));
        return new Number(atoi(v[0]->str().c_str()));
      }
    private:
      int n_;
    };

    class Var : public Exp
    {
    public:
      Var(std::string name) : name_(name) {}
      ~Var() {}
      virtual std::string str(void)
      {
        return name_;
      }
      static sphingid::ast::Node* make(std::vector<sphingid::ast::Node*> v)
      {
        assert(v.size() == 1);
        return new Var(v[0]->str());
      }
    private:
      std::string name_;
    };

    class BinaryOp : public Exp
    {
    public:
      BinaryOp(std::string op, Exp* right, Exp* left) : op_(op), right_(right), left_(left) {}
      virtual ~BinaryOp()
      {
        delete right_;
        delete left_;
      }
      virtual std::string str(void)
      {
        return "(" + op_ + " " + right_->str() + " " + left_->str() + ")";
      }
      static sphingid::ast::Node* make(std::vector<sphingid::ast::Node*> v)
      {
        if (v.size() != 3) {
          for (int i = 0; i < v.size(); ++i) {
            std::cout << i << ": " << v[i]->str() << std::endl;
          }
          assert(v.size() == 3);
        }

        assert(dynamic_cast<Exp*>(v[0]));
        assert(dynamic_cast<Exp*>(v[2]));
        return new BinaryOp(v[1]->str(), (Exp*)v[0], (Exp*)v[2]);
      }
    private:
      std::string op_;
      Exp* right_;
      Exp* left_;
    };

    class FnCall : public Exp
    {
    public:
      FnCall(std::string fn_name, std::vector<Exp*> args) : fn_name_(fn_name), args_(args) {}
      virtual std::string str(void)
      {
        std::string s;
        for (auto& i : args_) s += " " + i->str();
        return "(" + fn_name_ + s + ")";
      }
      static sphingid::ast::Node* make(std::vector<sphingid::ast::Node*> v)
      {
        assert(1 <= v.size());
        std::vector<Exp*> u;
        for (int i = 1; i < v.size(); ++i) {
          Exp* p = dynamic_cast<Exp*>(v[i]);
          assert(p);
          u.push_back(p);
        }
        return new FnCall(v[0]->str(), u);
      }
    private:
      std::string fn_name_;
      std::vector<Exp*> args_;
    };

    class Prototype : public sphingid::ast::Node
    {
    public:
      Prototype(std::string name, std::vector<std::string> args) : name_(name), args_(args) {}
      virtual std::string str(void)
      {
        std::string s;
        for (auto& i : args_) s += i + " ";
        return name_ + " (" + s + ")";
      }
      static sphingid::ast::Node* make(std::vector<sphingid::ast::Node*> v)
      {
        // 0   1    2 3456 n
        // def name ( args )
        std::vector<std::string> args;
        for (int i = 3; i < v.size() - 1; ++i) {
          args.push_back(v[i]->str());
        }
        return new Prototype(v[1]->str(), args);
      }
    private:
      std::string name_;
      std::vector<std::string> args_;
    };

    class FnDef : public sphingid::ast::Node
    {
    public:
      FnDef(Prototype* prot, Exp* body) : prot_(prot), body_(body) {}
      virtual std::string str(void)
      {
        return "(defn " + prot_->str() + "\n" + body_->str() + ")";
      }
      static sphingid::ast::Node* make(std::vector<sphingid::ast::Node*> v)
      {
        assert(v.size() == 2 && "FnDef Node could not generate");
        Prototype* p = dynamic_cast<Prototype*>(v[0]);
        Exp* q = dynamic_cast<Exp*>(v[1]);
        assert(p && q);
        return new FnDef(p, q);
      }
    private:
      Prototype* prot_;
      Exp* body_;
    };

    class Root : public sphingid::ast::Node
    {
    public:
      Root(std::vector<sphingid::ast::Node*> v) : v_(v) {}
      virtual std::string str(void)
      {
        std::string s;
        for (auto& i : v_) s += i->str() + "\n\n";
        return s;
      }
      static sphingid::ast::Node* make(std::vector<sphingid::ast::Node*> v)
      {
        std::cout << "ROOT: v.size() = " << v.size()  << std::endl;
        return new kaleidoscope::ast::Root(v);
      }
    private:
      std::vector<sphingid::ast::Node*> v_;
    };
  };
};

#endif /* _AST_H_ */
