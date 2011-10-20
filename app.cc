#include <iostream>

#include "app.hh"

namespace term {
  App::App (Term *fun, Term *arg)
    : fun_(fun), arg_(arg) {}

  App::App (const App &app)
    : Term(),
      fun_(app.fun_->clone()),
      arg_(app.arg_->clone()) {}

  App::~App () {
    delete fun_ ;
    delete arg_ ;
  }

  Term *App::clone () const {
    return new App(*this) ;
  }

  void App::print_ () const {
    std::cout << "(" ;
    fun_->print_() ;
    std::cout << ")" ;
    arg_->print_() ;
  }

  bool App::reduce (Term *&me) {
    Term *body = fun_->get_body() ;
    if (body) {
      me = body ;
      Term *arg = arg_ ;
      fun_ = NULL ;
      arg_ = NULL ;
      delete this ;
      if (! body->subst(me, arg)) {
        delete arg ;
      }
      return true ;
    } else {
      return fun_->reduce(fun_) || arg_->reduce(arg_) ;
    }
  }

  bool App::subst (Term *&me, Term *term, unsigned int target, bool can_use) {
    bool fun_used = fun_->subst(fun_, term, target, can_use) ;
    can_use = can_use && ! fun_used ;
    bool arg_used = arg_->subst(arg_, term, target, can_use) ;
    return fun_used || arg_used ;
  }

  void App::shift (unsigned int shift, unsigned int scope) {
    fun_->shift(shift, scope) ;
    arg_->shift(shift, scope) ;
  }
}
