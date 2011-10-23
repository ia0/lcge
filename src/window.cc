#include <QSlider>
#include <QGridLayout>
#include <QPushButton>

#include "window.hh"
#include "painter.hh"

Window::Window (QWidget *parent)
  : QWidget(parent),
    rotate_label_(new QLabel()),
    scale_label_(new QLabel()),
    ratio_label_(new QLabel()) {
  painter_ = new Painter(term::fullTerm(10)) ;

  QSlider *rotate_slider = new QSlider(Qt::Horizontal) ;
  QSlider *scale_slider = new QSlider(Qt::Horizontal) ;
  QSlider *ratio_slider = new QSlider(Qt::Horizontal) ;
  rotate_slider->setRange(0, 180) ;
  scale_slider->setRange(0, 100) ;
  ratio_slider->setRange(0, 100) ;

  QPushButton *random = new QPushButton(QString("Random")) ;
  QPushButton *reduce = new QPushButton(QString("Reduce")) ;

  QGridLayout *bottom_layout = new QGridLayout ;
  bottom_layout->addWidget(rotate_slider, 0, 0) ;
  bottom_layout->addWidget(rotate_label_, 0, 1) ;
  bottom_layout->addWidget(random, 0, 2) ;
  bottom_layout->addWidget(scale_slider, 1, 0) ;
  bottom_layout->addWidget(scale_label_, 1, 1) ;
  bottom_layout->addWidget(reduce, 1, 2) ;
  bottom_layout->addWidget(ratio_slider, 2, 0) ;
  bottom_layout->addWidget(ratio_label_, 2, 1) ;

  QGridLayout *main_layout = new QGridLayout ;
  main_layout->addWidget(painter_, 0, 0) ;
  main_layout->addLayout(bottom_layout, 1, 0) ;
  setLayout(main_layout) ;

  connect(random, SIGNAL(clicked()), this, SLOT(randomClicked())) ;
  connect(reduce, SIGNAL(clicked()), this, SLOT(reduceClicked())) ;
  connect(rotate_slider, SIGNAL(valueChanged(int)), this, SLOT(rotateChanged(int))) ;
  connect(scale_slider, SIGNAL(valueChanged(int)), this, SLOT(scaleChanged(int))) ;
  connect(ratio_slider, SIGNAL(valueChanged(int)), this, SLOT(ratioChanged(int))) ;

  rotate_slider->setValue(30) ;
  scale_slider->setValue(70) ;
  ratio_slider->setValue(80) ;
}

Window::~Window () {
  delete painter_ ;
}

void Window::randomClicked () {
  painter_->setTerm(term::randTerm(20)) ;
}

void Window::reduceClicked () {
  painter_->reduce () ;
}

void Window::rotateChanged (int value) {
  painter_->setRotate(value) ;
  rotate_label_->setText(QString::number(value)) ;
}

void Window::scaleChanged (int value) {
  qreal v = value ;
  v /= 100 ;
  painter_->setScale(v) ;
  scale_label_->setText(QString::number(v)) ;
}

void Window::ratioChanged (int value) {
  qreal v = value ;
  v /= 100 ;
  painter_->setRatio(v) ;
  ratio_label_->setText(QString::number(v)) ;
}
