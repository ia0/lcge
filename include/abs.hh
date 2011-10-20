#ifndef __ABS_HH__
#define __ABS_HH__

#include "term.hh"

namespace term {
  class Abs : public Term {
  private:
    Abs &operator= (const Abs &abs) ;
  protected:
    Term *body_ ;  // I own this pointer
  public:
    Abs (Term *body) ;
    Abs (const Abs &abs) ;
    ~Abs () ;
    Term *clone () const ;
    void print_ () const ;
    bool reduce (Term *&me) ;
    Term *get_body () ;
    bool subst (Term *&me, Term *term, unsigned int target, bool can_use) ;
    void shift (unsigned int shift, unsigned int scope) ;
  } ;
}

#endif  // __ABS_HH__
