#include "testskywidget.h"
#include "Window.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window window;

   QPalette p( window.palette() );
   p.setColor( QPalette::Background, QColor(0,48,105)/*Qt::black*/ );
   window.setPalette( p );
   //window.setWindowState(/*window.windowState() ^ */Qt::WindowFullScreen);


    window.show();
    window.resize( QSize(600, 600 ) );

//    TestSkyWidget w;
//    w.show();

    return a.exec();
}
