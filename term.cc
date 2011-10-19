#include <iostream>
#include <cstdlib>
#include <cassert>

#include "term.hh"

/* We simulate the following Haskell data declaration:
 * > data Term
 * >   = Var {level :: Int}
 * >   | Abs {body :: Term}
 * >   | App {fun :: Term, arg :: Term}
 */

namespace term {

  Var::Var (unsigned int level) : level_(level) {}

  Abs::Abs (Term *body) : body_(body) {}

  Abs::Abs (const Abs& abs)
    : body_(new Term(*abs.body_)) {}

  Abs::~Abs () {
    delete body_ ;
  }

  App::App (Term *fun, Term *arg)
    : fun_(fun), arg_(arg) {}

  App::App (const App& app)
    : fun_(new Term(*app.fun_)),
      arg_(new Term(*app.arg_)) {}

  App::~App () {
    delete fun_ ;
    delete arg_ ;
  }

  Term::Term (const Flag flag, const Content content)
    : flag_(flag), content_(content) {}

  Term::Term (const Term& term)
    : flag_(term.flag_) {
    switch (flag_) {
    case Var_f:
      content_.var_c = new Var(*term.content_.var_c) ;
      break ;
    case Abs_f:
      content_.abs_c = new Abs(*term.content_.abs_c) ;
      break ;
    case App_f:
      content_.app_c = new App(*term.content_.app_c) ;
      break ;
    }
  }

  Term::~Term () {
    switch (flag_) {
    case Var_f:
      delete content_.var_c ;
      break ;
    case Abs_f:
      delete content_.abs_c ;
      break ;
    case App_f:
      delete content_.app_c ;
      break ;
    }
  }

  void Term::print (bool newline) const {
    using namespace std ;
    switch (flag_) {
    case Var_f:
      cout << content_.var_c->level_ ;
      break ;
    case Abs_f:
      cout << "\\" ;
      content_.abs_c->body_->print(false) ;
      break ;
    case App_f:
      cout << "(" ;
      content_.app_c->fun_->print(false) ;
      cout << ")" ;
      content_.app_c->arg_->print(false) ;
      break ;
    }
    if (newline) cout << endl ;
  }

  bool Term::reduce () {
#ifdef DEBUG
    { using namespace std ;
      cout << "BEGIN reduce " ;
      print(false) ;
      cout << endl ; }
#endif
    bool result = true ;  // will be overwritten
    switch (flag_) {
    case Var_f:
      result = false ;
      break ;
    case Abs_f:
      result = content_.abs_c->body_->reduce() ;
      break ;
    case App_f:
      App *app = content_.app_c ;
      Term *fun = app->fun_ ;
      Term *arg = app->arg_ ;
      if (fun->flag_ == Abs_f) {
        Term *body = fun->content_.abs_c->body_ ;
        if (! body->subst(arg)) {
          delete arg ;
        }
        overwrite_with(body) ;
        app->arg_ = NULL ;
        fun->content_.abs_c->body_ = NULL ;
        delete app ;
        result = true ;
      } else {
        result = fun->reduce() || arg->reduce() ;
      }
      break ;
    }
#ifdef DEBUG
    { using namespace std ;
      cout << "END reduce = " << result << endl ; }
#endif
    return result ;
  }

  bool Term::subst (Term *term, unsigned int target, bool can_use) {
#ifdef DEBUG
    { using namespace std ;
      cout << "BEGIN subst " << target << " for " ;
      term->print(false) ;
      cout << " in " ;
      print(false) ;
      cout << " (can_use=" << can_use << ")" << endl ; }
#endif
    bool result = true ;  // will be overwritten
    switch (flag_) {
    case Var_f: {
      Var *var = content_.var_c ;
      unsigned int level = var->level_ ;
      if (level < target) {
        result = false ;
      } else if (level == target) {
        delete var ;
        if (can_use) {
          overwrite_with(term) ;
        } else {
          overwrite_with(new Term(*term)) ;
        }
        shift(level) ;
        result = true ;
      } else {
        --var->level_ ;
        result = false ;
      }
      break ; }
    case Abs_f:
      ++target ;
      result = content_.abs_c->body_->subst(term, target, can_use) ;
      break ;
    case App_f:
      bool fun_used = content_.app_c->fun_->subst(term, target, can_use) ;
      bool arg_used = content_.app_c->arg_->subst(term, target, can_use && !fun_used) ;
      result = fun_used || arg_used ;
      break ;
    }
#ifdef DEBUG
    { using namespace std ;
      cout << "END subst = " << result << endl ; }
#endif
    return result ;
  }

  void Term::shift (unsigned int shift, unsigned int scope) {
    switch (flag_) {
    case Var_f: {
      Var *var = content_.var_c ;
      unsigned int level = var->level_ ;
      if (level >= scope) {
        var->level_ += shift ;
      }
      break ; }
    case Abs_f:
      ++scope ;
      content_.abs_c->body_->shift(shift, scope) ;
      break ;
    case App_f:
      content_.app_c->fun_->shift(shift, scope) ;
      content_.app_c->arg_->shift(shift, scope) ;
      break ;
    }
  }

  void Term::overwrite_with (Term *source) {
#ifdef DEBUG
    { using namespace std ;
      cout << "BEGIN overwrite_with " ;
      source->print(false) ;
      cout << endl ; }
#endif
    flag_ = source->flag_ ;
    content_ = source->content_ ;
    source->content_.var_c = NULL ;  // var_c is kind of a hack
    delete source ;
#ifdef DEBUG
    { using namespace std ;
      cout << "END overwrite" << endl ; }
#endif
  }

  Term *newVar (const unsigned int level) {
    Term::Content content ;
    content.var_c = new Var(level) ;
    Term *term = new Term(Term::Var_f, content) ;
    return term ;
  }

  Term *newAbs (Term *body) {
    Term::Content content ;
    content.abs_c = new Abs(body) ;
    Term *term = new Term(Term::Abs_f, content) ;
    return term ;
  }

  Term *newApp (Term *fun, Term *arg) {
    Term::Content content ;
    content.app_c = new App(fun, arg) ;
    Term *term = new Term(Term::App_f, content) ;
    return term ;
  }

  Term *jot2term (const bool jot[], unsigned int pos) {
    if (pos == 0) {  // [] = \0
      return newAbs(newVar(0)) ;
    }
    --pos ;
    if (jot[pos]) {  // [F]1 = \\[F]10
      Term *f = jot2term (jot, pos) ;
      return newAbs(newAbs(newApp(f,newApp(newVar(1),newVar(0))))) ;
    } else {  // [F]0 = ([F](\\\(20)10))(\\1)
      Term *f = jot2term (jot, pos) ;
      Term *s = newAbs(newAbs(newAbs(newApp(newApp(newVar(2),newVar(0)),newApp(newVar(1),newVar(0)))))) ;
      Term *k = newAbs(newAbs(newVar(1))) ;
      return newApp(newApp(f,s),k) ;
    }
  }

  Term *randTerm (unsigned int count) {
    bool jot[count] ;
    for (unsigned int i = 0; i < count; ++i) {
      if (rand() % 2) {
        jot[i] = true ;
      } else {
        jot[i] = false ;
      }
    }
    return jot2term (jot, count) ;
  }

  Term *parse () {
    using namespace std ;
    char c ;
    cin.get(c) ;
    switch (c) {
    case '\\':
      return newAbs(parse()) ;
    case '(': {
      Term *fun = parse() ;
      cin.get(c) ;
      assert( c == ')' );
      Term *arg = parse() ;
      return newApp(fun,arg) ; }
    default:
      unsigned int level = c - '0' ;
      return newVar(level) ;
    }
  }
}
