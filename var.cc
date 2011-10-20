#include <iostream>

#include "var.hh"

namespace term {
  Var::Var (unsigned int level)
    : level_(level) {}

  Var::Var (const Var &var)
    : Term(), level_(var.level_) {}

  Term *Var::clone() const {
    return new Var(*this) ;
  }

  void Var::print_ () const {
    std::cout << level_ ;
  }
}
