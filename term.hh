#ifndef __TERM_HH__
#define __TERM_HH__

#include <iostream>

namespace term {
  class Term {
  private:
    Term (const Term &term) ;  // no copy constructor
    Term &operator= (const Term &term) ;  // no assignment operator
  protected:
    Term () ;
  public:
    virtual ~Term () ;
    virtual Term *clone () const = 0 ;
    virtual void print_ () const = 0 ;
    void print (bool newline = true) const ;
    virtual bool reduce (Term *&me) = 0 ;
    virtual Term *get_body () ;
    virtual bool subst (Term *&me, Term *term, unsigned int target = 0, bool can_use = true) = 0 ;
    virtual void shift (unsigned int shift, unsigned int scope = 0) = 0 ;
  } ;

  Term *jot2term (const bool jot[], unsigned int pos) ;
  Term *randTerm (unsigned int count) ;
  Term *parse (const char s[]) ;
  Term *parse (const std::string &s) ;
  Term *parse (std::istream &cin) ;
  bool reduce (Term *&term) ;
}

#endif  // __TERM_HH__
