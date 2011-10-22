#ifndef __PAINTER_HH__
#define __PAINTER_HH__

#include <QWidget>

#include "term.hh"

using term::Term ;

class Painter : public QWidget {
  Q_OBJECT
private:
  Term *term_ ;
  Painter (const Painter &painter) ;
  Painter &operator= (const Painter &painter) ;
protected:
  void paintEvent(QPaintEvent *event);
public:
  Painter (Term *term, QWidget *parent = 0) ;
  ~Painter () ;
} ;

#endif  // __PAINTER_HH__
