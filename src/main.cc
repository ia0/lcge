#include <iostream>

#include "term.hh"

int main() {
  using namespace std ;
  using namespace term ;
  for (unsigned int i = 0 ; i < 50 ; ++i) {
    Term *term = randTerm(i) ;
    bool loop = true ;
    while (loop) {
      term->print() ;
      loop = reduce(term) ;
    }
    delete term ;
    cout << endl ;
  }
  return 0 ;
}
