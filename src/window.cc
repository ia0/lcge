#include <QSlider>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include "window.hh"
#include "painter.hh"

Window::Window (QWidget *parent)
  : QWidget(parent) {
  painter_ = new Painter(term::fullTerm(10)) ;
  QSlider *rotate_slider = new QSlider(Qt::Horizontal) ;
  QLabel *rotate_label = new QLabel() ;
  // QSlider *scale = new QSlider(Qt::Horizontal) ;
  // QSlider *ratio = new QSlider(Qt::Horizontal) ;
  QPushButton *random = new QPushButton(QString("Random")) ;
  QPushButton *reduce = new QPushButton(QString("Reduce")) ;
  // QPushButton *reduce = new QPushButton(QString("Reduce")) ;
  QGridLayout *bottom_layout = new QGridLayout ;
  bottom_layout->addWidget(rotate_slider, 0, 0) ;
  bottom_layout->addWidget(rotate_label, 0, 1) ;
  bottom_layout->addWidget(random, 0, 2) ;
  // bottom_layout->addWidget(scale, 0, 1) ;
  bottom_layout->addWidget(reduce, 1, 2) ;
  // bottom_layout->addWidget(ratio, 0, 2) ;
  QGridLayout *main_layout = new QGridLayout ;
  main_layout->addWidget(painter_, 0, 0) ;
  main_layout->addLayout(bottom_layout, 1, 0) ;
  setLayout(main_layout) ;
  connect(random, SIGNAL(clicked()),
          this, SLOT(randomClicked())) ;
  connect(reduce, SIGNAL(clicked()),
          this, SLOT(reduceClicked())) ;
}

Window::~Window () {
  delete painter_ ;
}

void Window::randomClicked() {
  painter_->setTerm(term::randTerm(20)) ;
}

void Window::reduceClicked() {
  painter_->reduce () ;
}
