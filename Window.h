 #ifndef WINDOW_H
 #define WINDOW_H
 #include "testskywidget.h"
 #include <QWidget>
 #include <QGridLayout>

 class Window : public QWidget
 {
     Q_OBJECT
 public:
     Window();
 protected:
     void mouseDoubleClickEvent(QMouseEvent*);


 private:
     TestSkyWidget *testskyWidget;
 };

 #endif
