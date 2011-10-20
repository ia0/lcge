#include <iostream>

#include "term.hh"
#include "var.hh"
#include "abs.hh"
#include "app.hh"

int main() {
  using namespace std ;
  using namespace term ;

  // Term *term = randTerm(14) ;
// \\(((\\(((\\(\\(((((\\(\\(\\(\\(((\\(\0)(1)0)\\\((2)0)(1)0)\\1)(1)0)(1)0)(1)0)(1)0)\\\((2)0)(1)0)\\1)\\\((2)0)(1)0)\\1)(1)0)(1)0)\\\((2)0)(1)0)\\1)(1)0)\\\((2)0)(1)0)\\1)(1)0
  // bool jot[] = {true, true, true, true, true, false, false, false} ;
  // Term *term = jot2term(jot, 8) ;
  // Term *term = parse() ;
  // bool loop = true ;
  // while (loop) {
  //   term->print() ;
  //   loop = term->reduce() ;
  // }

  Term *term = new Abs(new App(new Var(0), new Var(0))) ;
  term->print() ;
  delete term ;
  return 0 ;
}
