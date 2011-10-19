#ifndef __TERM_HH__
#define __TERM_HH__

namespace term {
  class Term ;

  class Var {
  private:
  public:
    unsigned int level_ ;
    Var (unsigned int level) ;
  } ;

  class Abs {
  private:
    Abs& operator= (const Abs& abs) ;
  public:
    Term *body_ ;  // I own this pointer
    Abs (Term *body) ;
    Abs (const Abs& abs) ;
    ~Abs () ;
  } ;

  class App {
  private:
    App& operator= (const App& app) ;
  public:
    Term *fun_ ;  // I own this pointer
    Term *arg_ ;  // I own this pointer
    App (Term *fun, Term *arg) ;
    App (const App& app) ;
    ~App () ;
  } ;

  class Term {
  private:
    enum Flag {Var_f, Abs_f, App_f} flag_ ;
    union Content {
      Var *var_c ;  // when (flag_ == Var_f)
      Abs *abs_c ;  // when (flag_ == Abs_f)
      App *app_c ;  // when (flag_ == App_f)
    } content_ ;  // I own these pointers
    Term (const Flag flag, const Content content) ;
    Term& operator= (const Term& term) ;
  public:
    Term (const Term& term) ;
    ~Term () ;
    friend Term *newVar (const unsigned int level) ;
    friend Term *newAbs (Term *body) ;
    friend Term *newApp (Term *fun, Term *arg) ;
    void print (bool newline = true) const ;
    bool reduce () ;
    bool subst (Term *term, unsigned int level = 0, bool can_use = true) ;
    void shift (unsigned int shift, unsigned int scope = 0) ;
    void overwrite_with (Term *source) ;
  } ;

  Term *newVar (unsigned int level) ;
  Term *newAbs (Term *body) ;
  Term *newApp (Term *fun, Term *arg) ;
  Term *jot2term (const bool jot[], unsigned int pos) ;
  Term *randTerm (unsigned int count) ;
  Term *parse () ;
}

#endif  // __TERM_HH__
