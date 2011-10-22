#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cassert>

#include "term.hh"

namespace term {
  Term::Term () {}

  Term::~Term () {}

  void Term::print (bool newline) const {
    print_() ;
    if (newline) std::cout << std::endl ;
  }

  Term *Term::get_body () {
    return NULL ;
  }

  Term *jot2term (const bool jot[], unsigned int pos) {
    using namespace std ;
    if (pos == 0) {  // [] = \0
      return parse(".0") ;
    }
    --pos ;
    if (jot[pos]) {  // [F]1 = ..([F])(1)0
      Term *f = jot2term(jot, pos) ;
      return new Abs(new Abs(new App(f, parse("(1)0")))) ;
    } else {  // [F]0 = (([F])...((2)0)(1)0)..1
      Term *f = jot2term(jot, pos) ;
      Term *s = parse("...((2)0)(1)0") ;
      Term *k = parse("..1") ;
      return new App(new App(f, s), k) ;
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

  Term *parse (const char s[]) {
    using namespace std ;
    string str(s) ;
    return parse(str) ;
  }

  Term *parse (const std::string &s) {
    using namespace std ;
    istringstream iss(s) ;
    return parse(iss) ;
  }

  Term *parse (std::istream &cin) {
    char c ;
    cin.get(c) ;
    switch (c) {
    case '\\':
    case '.':
      return new Abs(parse(cin)) ;
    case '(': {
      Term *fun = parse(cin) ;
      cin.get(c) ;
      assert( c == ')' );
      Term *arg = parse(cin) ;
      return new App(fun,arg) ; }
    default:
      unsigned int level = c - '0' ;
      return new Var(level) ;
    }
  }

  bool reduce (Term *&term) {
    return term->reduce(term) ;
  }
}
