#ifndef __TERM_HH__
#define __TERM_HH__

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
    // bool reduce () ;
    // bool subst (Term *term, unsigned int level = 0, bool can_use = true) ;
    // void shift (unsigned int shift, unsigned int scope = 0) ;
    // void overwrite_with (Term *source) ;
  } ;

  // Term *jot2term (const bool jot[], unsigned int pos) ;
  // Term *randTerm (unsigned int count) ;
  // Term *parse () ;
}

#endif  // __TERM_HH__
