#include <cassert>

#include "painter.hh"

Painter::Painter (Term *term, qreal rotate, qreal scale, qreal ratio, QWidget *parent)
  : QWidget(parent), term_(term),
    rotate_(rotate), scale_(scale), ratio_(ratio) {}

Painter::~Painter () {
  delete term_ ;
}

bool Painter::reduce () {
  bool b = term::reduce(term_) ;
  update() ;
  return b ;
}

void Painter::setTerm (Term *term) {
  delete term_ ;
  term_ = term ;
  update() ;
}

void Painter::setRotate (qreal rotate) {
  rotate_ = rotate ;
  update() ;
}

void Painter::setScale (qreal scale) {
  scale_ = scale ;
  update() ;
}

void Painter::setRatio (qreal ratio) {
  ratio_ = ratio ;
  update() ;
}

void Painter::paintBelow (QPainter &painter, const Term *term) {
  painter.save() ;
  painter.rotate(rotate_) ;
  painter.scale(scale_, scale_) ;
  paintTerm (painter, term) ;
  painter.restore() ;
}

void Painter::paintAside (QPainter &painter, const Term *term) {
  painter.save() ;
  painter.translate(0, 1 + ratio_) ;
  painter.rotate(180) ;
  painter.scale(ratio_, ratio_) ;
  paintBelow (painter, term) ;
  painter.restore() ;
}

void Painter::paintTerm (QPainter &painter, const Term *term) {
  using namespace term ;
  painter.drawPoint(QPointF(0, 1)) ;
  const Abs *abs ;
  const App *app ;
  if ((app = dynamic_cast<const App*>(term))) {
    paintBelow(painter, app->get_fun()) ;
    paintAside(painter, app->get_arg()) ;
  } else if ((abs = dynamic_cast<const Abs*>(term))) {
    paintBelow(painter, abs->get_body()) ;
  }
}

void Painter::paintEvent (QPaintEvent */*event*/) {
  QPainter painter(this);
  qreal w = this->width() ;
  qreal h = this->height() ;
  painter.fillRect(0, 0, w, h, Qt::black) ;
  qreal s = ((h < w) ? h : w) / 3 ;
  painter.translate(w/2, h/2) ;
  painter.rotate(180) ;
  painter.scale(s, s) ;
  painter.translate(0, -0.9) ;
  painter.setBrush(Qt::white) ;
  painter.setPen(QPen(QBrush(Qt::white), 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)) ;
  paintTerm(painter, term_) ;
}
