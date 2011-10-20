#ifndef __VAR_HH__
#define __VAR_HH__

#include "term.hh"

namespace term {
  class Var : public Term {
  private:
    Var &operator= (const Var &var) ;
  protected:
    unsigned int level_ ;
  public:
    Var (unsigned int level) ;
    Var (const Var &var) ;
    Term *clone () const ;
    void print_ () const ;
  } ;
}

#endif  // __VAR_HH__
