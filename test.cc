#include <iostream>

#include "term.hh"

int main() {
  using namespace std ;
  using namespace term ;
  Term *term = randTerm(14) ;
// \\(((\\(((\\(\\(((((\\(\\(\\(\\(((\\(\0)(1)0)\\\((2)0)(1)0)\\1)(1)0)(1)0)(1)0)(1)0)\\\((2)0)(1)0)\\1)\\\((2)0)(1)0)\\1)(1)0)(1)0)\\\((2)0)(1)0)\\1)(1)0)\\\((2)0)(1)0)\\1)(1)0
  // bool jot[] = {true, true, true, true, true, false, false, false} ;
  // Term *term = jot2term(jot, 8) ;
  // Term *term = parse() ;
  bool loop = true ;
  while (loop) {
    term->print() ;
    loop = term->reduce() ;
  }
  delete term ;
  return 0 ;
}
