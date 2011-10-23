#include <iostream>

#include <QApplication>
#include <QProcessEnvironment>

#include "term.hh"
#include "window.hh"

int main (int argc, char *argv[]) {
  using namespace std ;
  QProcessEnvironment env = QProcessEnvironment::systemEnvironment() ;
  if (env.contains(QString("TEST_MODE"))) {
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
  QApplication app(argc, argv) ;
  Window window ;
  window.show() ;
  return app.exec() ;
}
