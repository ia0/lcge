#ifndef __APP_HH__
#define __APP_HH__

#include "term.hh"

namespace term {
  class App : public Term {
  private:
    App &operator= (const App &app) ;
  protected:
    Term *fun_ ;  // I own this pointer
    Term *arg_ ;  // I own this pointer
  public:
    App (Term *fun, Term *arg) ;
    App (const App &app) ;
    ~App () ;
    Term *clone () const ;
    void print_ () const ;
    bool reduce (Term *&me) ;
    bool subst (Term *&me, Term *term, unsigned int target, bool can_use) ;
    void shift (unsigned int shift, unsigned int scope) ;
    void paint (QPainter &painter) const ;
  } ;
}

#endif  // __APP_HH__
