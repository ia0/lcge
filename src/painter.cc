#include "painter.hh"

Painter::Painter (Term *term, QWidget *parent)
  : QWidget(parent), term_(term) {}

Painter::~Painter () {
  delete term_ ;
}

void Painter::paintEvent (QPaintEvent */*event*/) {
  QPainter painter(this);
  qreal w = this->width() ;
  qreal h = this->height() ;
  qreal s = ((h < w) ? h : w) / 3 ;
  painter.translate(w/2, h/2) ;
  painter.rotate(180) ;
  painter.scale(s, s) ;
  painter.translate(0, -0.9) ;
  painter.setBrush(Qt::black) ;
  painter.setPen(QPen(QBrush(Qt::black), 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)) ;
  // painter.drawPoint(0, 0) ;
  term_->paint(painter) ;
}
