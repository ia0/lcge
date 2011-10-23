#include <iostream>

#include "term.hh"

namespace term {
  Abs::Abs (Term *body)
    : body_(body) {}

  Abs::Abs (const Abs &abs)
    : Term(), body_(abs.body_->clone()) {}

  Abs::~Abs () {
    delete body_ ;
  }

  Term *Abs::clone () const {
    return new Abs(*this) ;
  }

  void Abs::print_ () const {
    std::cout << "\\" ;
    body_->print_() ;
  }

  bool Abs::reduce (Term *&/*me*/) {
    return body_->reduce(body_) ;
  }

  const Term *Abs::get_body () const {
    return body_ ;
  }

  void Abs::extract (Term *&body) {
    body = body_ ;
    body_ = NULL ;
    delete this ;
  }

  bool Abs::subst (Term *&/*me*/, Term *term, unsigned int target, bool can_use) {
    ++target ;
    return body_->subst(body_, term, target, can_use) ;
  }

  void Abs::shift (unsigned int shift, unsigned int scope) {
    ++scope ;
    body_->shift(shift, scope) ;
  }
}
