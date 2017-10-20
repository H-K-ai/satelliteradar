 #include <QtGui>
 #include "Window.h"

 Window::Window()
 {
   setWindowFlags(Qt::FramelessWindowHint);
   QGridLayout *layout = new QGridLayout;

   QColor fontColor( 0, 48, 100 );

   testskyWidget = new TestSkyWidget;
   testskyWidget->setWindowOpacity(0.5);

   testskyWidget->insert( 0,  0, 10,  QString( "0" ), Qt::red, Qt::blue, fontColor,
      TestSkyWidget::SatelliteState::Visible |
      TestSkyWidget::SatelliteState::Marked   |
      TestSkyWidget::SatelliteState::Flashing
         );
   testskyWidget->insert( 1, 10, 10,  QString( "1" ), Qt::red, Qt::white, fontColor,
      TestSkyWidget::SatelliteState::HalfVisible |
      TestSkyWidget::SatelliteState::Marked   /*|
      TestSkyWidget::SatelliteState::Flashing*/
         );

   testskyWidget->insert( 2,  40, 15,  QString( "2" ), Qt::red, Qt::yellow, fontColor,
      TestSkyWidget::SatelliteState::Visible  |
      TestSkyWidget::SatelliteState::Marked   /*|
      TestSkyWidget::SatelliteState::Flashing1*/

         );
   testskyWidget->insert( 3, 80, 15,  QString( "3" ), Qt::red, Qt::yellow, fontColor,
      TestSkyWidget::SatelliteState::HalfVisible |
      TestSkyWidget::SatelliteState::Marked |
      TestSkyWidget::SatelliteState::Flashing
         );

   testskyWidget->insert( 4,  120, 15,  QString( "4" ), Qt::red, Qt::white, fontColor,
      TestSkyWidget::SatelliteState::Visible  |
      TestSkyWidget::SatelliteState::Marked   |
      TestSkyWidget::SatelliteState::Flashing
         );
   testskyWidget->insert( 5, 150, 15,  QString( "5" ), Qt::red, Qt::white, fontColor,
      TestSkyWidget::SatelliteState::HalfVisible |
      TestSkyWidget::SatelliteState::Marked      /*|
      TestSkyWidget::SatelliteState::Flashing1*/
         );


   testskyWidget->setGridColor( QColor( 255, 255, 255 ) );
   testskyWidget->setGridWidth( 0.0 );
   testskyWidget->setCrosses( 2 );
   testskyWidget->setEllipses( 6 );
   testskyWidget->setSatelliteScale( 0.02 );

   for( int i=50; i <= 70; i ++ ) 
   {
      testskyWidget->insert( i, 0, 0,
            QString(  "0"+QString::number(i) ), 
            Qt::magenta, 
            Qt::white, 
            fontColor, 
            TestSkyWidget::SatelliteState::Visible );
      testskyWidget->setInnerColor  ( i, Qt::white );
      testskyWidget->setOuterColor  ( i, Qt::blue );
      testskyWidget->setFontColor   ( i, Qt::red );
      testskyWidget->setLabel       ( i, QString( "%1" ).arg(i)        );
      testskyWidget->setState( i,
            TestSkyWidget::SatelliteState::Visible |
            TestSkyWidget::SatelliteState::Marked /*|
            TestSkyWidget::SatelliteState::Flashing2*/);

      testskyWidget->setAzimuth     ( i, (i*30)%360  );
      testskyWidget->setElevation   ( i, (i*5)%90  );
   }
   layout->addWidget(testskyWidget, 100, 100 );

   setLayout(layout);

   setWindowTitle(tr("satellite"));
   installEventFilter(this);
 }

void Window::mouseDoubleClickEvent(QMouseEvent *evt)
 {
     static QPoint mousePoint;
//     static bool mousePressed = false;

     if (evt->button() == Qt::LeftButton)
     {
//         mousePressed = true;
         mousePoint = evt->globalPos() - this->pos();
        if(windowState()!= Qt::WindowFullScreen)
        {
           setWindowState(Qt::WindowFullScreen);
        }

        else
        {
           setWindowState(Qt::WindowNoState);
        }

     }

//     else
//     {
//         if (mousePressed && (evt->buttons() && Qt::RightButton))
//         {
//             this->move(evt->globalPos() - mousePoint);
//             return true;

//         }
//     }


}
