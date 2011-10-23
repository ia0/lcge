#ifndef __WINDOW_HH__
#define __WINDOW_HH__

#include <QWidget>
#include <QLabel>

#include "painter.hh"
#include "term.hh"

using term::Term ;

class Window : public QWidget {
  Q_OBJECT
private:
  Painter *painter_ ;
  QLabel *rotate_label_ ;
  QLabel *scale_label_ ;
  QLabel *ratio_label_ ;
  Window (const Window &window) ;
  Window &operator= (const Window &window) ;
private slots:
  void randomClicked () ;
  void reduceClicked () ;
  void rotateChanged (int value) ;
  void scaleChanged (int value) ;
  void ratioChanged (int value) ;
public:
  Window (QWidget *parent = 0) ;
  ~Window () ;
} ;

#endif  // __WINDOW_HH__
