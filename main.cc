#include <iostream>

#include "term.hh"
#include "var.hh"
#include "abs.hh"
#include "app.hh"

int main() {
  using namespace std ;
  using namespace term ;
  // bool jot[] = {true, true, true, true, true, false, false, false} ;
  // Term *term = jot2term(jot, 8) ;
  // bool jot[] = {true, true, true, false, false} ;
  // Term *term = jot2term(jot, 5) ;
  for (unsigned int i = 0 ; i < 50 ; ++i) {
    Term *term = randTerm(i) ;
    cout << "----------------------------------------------------------------------" << endl ;
    cout << i << endl ;
    bool loop = true ;
    while (loop) {
      term->print() ;
      loop = reduce(term) ;
    }
    delete term ;
  }
  return 0 ;
}
