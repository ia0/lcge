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
}
