#include <iostream>

#include "abs.hh"

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
}
