#ifndef __PAINTER_HH__
#define __PAINTER_HH__

#include <QWidget>

#include "term.hh"

using term::Term ;

class Painter : public QWidget {
  Q_OBJECT
private:
  const Term *term_ ;
  qreal rotate_ ;  // one step rotation
  qreal scale_ ;  // after one rotation
  qreal ratio_ ;  // right/left child for app
  Painter (const Painter &painter) ;
  Painter &operator= (const Painter &painter) ;
  void paintBelow (QPainter &painter, const Term *term) ;
  void paintAside (QPainter &painter, const Term *term) ;
  void paintTerm (QPainter &painter, const Term *term) ;
protected:
  void paintEvent (QPaintEvent *event) ;
public:
  Painter (const Term *term, qreal rotate = 30, qreal scale = 0.7, qreal ratio = 0.8, QWidget *parent = 0) ;
  ~Painter () ;
  void setTerm (const Term *term) ;
  void setRotate (qreal rotate) ;
  void setScale (qreal scale) ;
  void setRatio (qreal ratio) ;
} ;

#endif  // __PAINTER_HH__
