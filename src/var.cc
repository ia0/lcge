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

  bool Var::reduce (Term *&/*me*/) {
    return false ;
  }

  bool Var::subst (Term *&me, Term *term, unsigned int target, bool can_use) {
    if (level_ < target) {
      return false ;
    } else if (level_ == target) {
      delete this ;
      if (can_use) {
        me = term ;
      } else {
        me = term->clone() ;
      }
      me->shift(target) ;
      return true ;
    } else {
      --level_ ;
      return false ;
    }
  }

  void Var::shift (unsigned int shift, unsigned int scope) {
    if (level_ >= scope) {
      level_ += shift ;
    }
  }
}
