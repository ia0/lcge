#ifndef __WINDOW_HH__
#define __WINDOW_HH__

#include <QWidget>

#include "painter.hh"
#include "term.hh"

using term::Term ;

class Window : public QWidget {
  Q_OBJECT
private:
  Painter *painter_ ;
  Window (const Window &window) ;
  Window &operator= (const Window &window) ;
private slots:
  void randomClicked () ;
  void reduceClicked () ;
protected:
  // void paintEvent (QPaintEvent *event) ;
public:
  Window (QWidget *parent = 0) ;
  ~Window () ;
} ;

#endif  // __WINDOW_HH__
