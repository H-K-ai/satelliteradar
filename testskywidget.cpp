/*!
 *@file    testskywidget.h
 *@brief   模拟卫星运行航迹位置
 *@version 0.1
 *@section LICENSE Copyright (C) 2017-2117 NCHU ImgProcessing Corporation
 *@writer  MHK
*/

#include "testskywidget.h"
#include <QPainter>
#include <QPen>
#include <QTimerEvent>
#include <QConicalGradient>

TestSkyWidget::TestSkyWidget(QWidget *parent) :
    QWidget(parent,Qt::FramelessWindowHint)
    , flash( false )
    , p_marginScale( 0.78 )
    , p_satScale( 0.03 )
    , p_fontScale( 0.02 )
    , p_gridColor( QColor( 0, 48, 105, 255 ) )
    , p_gridTextColor( QColor( 255, 255, 255, 255 ) )
    , p_gridWidth( 1 )
    , p_ellipses( 3 )
    , p_crosses( 3 )
    , p_textMargin( 5 )
    , p_flashIntervall( 500 )
    , p_withGridLabels( true )
    , p_antialiased( true )
{
    flashTimer.setInterval( p_flashIntervall );
    connect( &flashTimer, SIGNAL( timeout() ), this, SLOT( Change_flash() ) );
    flashTimer.start( p_flashIntervall );

    m_pieRotate = 0;
    m_timerId = -1;
    m_nSpeed = 50;
    m_points<<QPoint()<<QPoint()<<QPoint()<<QPoint()<<QPoint();
    m_pointsAlapha<<100<<100<<100<<100<<100;

//    //启动定时器
    m_timerId = startTimer(m_nSpeed);
    m_pointTimerId = startTimer(1200);
}

TestSkyWidget::~TestSkyWidget()
{

}

void TestSkyWidget::Change_flash()
{
    flash = !flash;
    this->update();
}

void TestSkyWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
   // QSize        widgetSize( this->width(), this->height() );
      //QRect        widgetSize;

  //  QPalette       p = QGuiApplication::palette();

     float          topMargin ;
     float          leftMargin;
     float          size;
     float          satelliteSize;
     float          fontSize;

     float          availableWidth    = widgetSize.width ();
     float          availableHeight   = widgetSize.height();

     qreal x = widgetSize.center().x() + (qreal) availableWidth /2 * cos(-m_pieRotate*3.14159/180);
     qreal y = widgetSize.center().y() + (qreal) availableWidth /2 * sin(-m_pieRotate*3.14159/180);
     painter.setPen(QPen(Qt::white));
     painter.drawLine(widgetSize.center(),QPointF(x,y));

      //----//扇形
     QConicalGradient gradient;
     gradient.setCenter(widgetSize.center());
     gradient.setAngle(m_pieRotate + 180); //渐变与旋转方向恰好相反，以扇形相反的边作为渐变角度。
     gradient.setColorAt(0.8,QColor(255,255,255,100)); //从渐变角度开始0.5 - 0.75为扇形区域，由于Int类型计算不精确，将范围扩大到0.4-0.8
     //gradient.setColorAt(0.8,QColor(255,255,255,0));
     gradient.setColorAt(0.4,QColor(255,0,105,100));
     painter.setBrush(QBrush(gradient));
//   painter.setBrush(QBrush(QColor(255,0,0,100)));
     painter.setPen(Qt::NoPen);
     painter.drawPie(widgetSize,m_pieRotate*16,90*16);//添加扫描功能


     //装饰-随机点
     for(int i = 0; i < m_points.count(); ++i)
     {
         int colorAlaph = m_pointsAlapha.at(i);
         painter.setPen(QPen(QColor(255,255,255,colorAlaph),3));
         painter.drawPoint(m_points.at(i));
     }


     if( availableHeight/*height()*/ > availableWidth/*width()*/ )
     {
        size = widgetSize.width() * p_marginScale;
        topMargin   = ( widgetSize.width() - widgetSize.width() * p_marginScale +
              widgetSize.height() - widgetSize.width() ) / 2.0;
        leftMargin  = ( widgetSize.width() - widgetSize.width() * p_marginScale ) / 2.0;

//          widgetSize = QRect(0,(height() - width())/2 ,width(),width());
     }

     else
     {
        size = widgetSize.height() * p_marginScale;
        leftMargin = ( widgetSize.height() - widgetSize.height() * p_marginScale +
              widgetSize.width() - widgetSize.height()) / 2.0;
        topMargin  = ( widgetSize.height() - widgetSize.height() * p_marginScale ) / 2.0;


         //widgetSize = QRect((width() - height())/2 ,0,height(),height());

     }

      satelliteSize = size * p_satScale;
     //satelliteSize = widgetSize/*size*/ * p_satScale;

     painter.setRenderHint(QPainter::Antialiasing, p_antialiased);
     painter.translate( leftMargin, topMargin );
     fontSize = size * p_fontScale;


     painter.setFont(
           QFont( "Arial",
           static_cast< int >( fontSize ) ) );

     // paint the circles
     for( int i=0; i < p_ellipses; i++ )
     {
        float radius = size / 2.0 - i * ( size / ( 2.0  * p_ellipses )  );
        painter.setPen( QPen( p_gridColor, p_gridWidth ) );
        painter.drawEllipse(
              QPoint( size/2.0, size/2.0 ),
              static_cast< int >( radius ),
              static_cast< int >( radius ) );
        if( p_withGridLabels )
        {
           painter.setPen( QPen( p_gridTextColor, p_gridWidth ) );
           painter.drawText( QPoint( size/2.0 + p_textMargin, size/2.0 - ( radius + p_textMargin ) ),
                              QString("%1").arg( i * (90 / p_ellipses ) ) );
        }
     }

     // paint the crosses
     for( int i=0; i < p_crosses; i ++ )
     {
        QLineF line1;
        QLineF line2;
        float angle = static_cast<float>(i) * 90.0 / static_cast<float>(p_crosses);
        line1.setP1( QPoint( size/2.0, size/2.0 ) );
        line1.setLength( size/2.0 );

        QRectF textRect( 0, 0, 4.0 * fontSize, fontSize + 2.0 );

        for( int c = 0; c < 4; c++ )
        {
           line1.setAngle( angle + c*90.0 + 90.0 );
           painter.setPen( QPen( p_gridColor, p_gridWidth ) );
           painter.drawLine( line1 );
           if( p_withGridLabels  )
           {
              painter.setPen( QPen( p_gridTextColor, p_gridWidth ) );
              line2 = QLineF( line1 );
              line2.setLength( size/2.0 + 2.0 * fontSize );
              textRect.moveCenter( line2.p2() );
              if( i > 0 )
                 painter.drawText( textRect, Qt::AlignCenter, QString( "%1").arg( 360.0 - (c*90.0 ) - angle ) );
              else
                 painter.drawText( textRect, Qt::AlignCenter, QString( "N") );
           }
        }
     }

     QBrush innerBrush = QBrush( Qt::SolidPattern );
     //QBrush outerBrush = QBrush( );

     foreach( auto s, satellites )
     {

        // skip invisible satellites
        if(     s.state & SatelliteState::Invisible       ||  // the invisible flag is set

           ( !( s.state & SatelliteState::Visible ) &         // neither visible nor half-visible
             !( s.state & SatelliteState::HalfVisible ) ) ||

           (  s.state & (SatelliteState::Flashing/*|SatelliteState::Flashing1|SatelliteState::Flashing2*/) && flash )    // flashing flag is set and flash is active
           )
           continue;


        float el_s = ( 90 - s.el ) * size / ( 2 * 90.0 );
        QRectF labelRect( 0, 0, s.label.length() * satelliteSize, satelliteSize+2 );

        QPoint satPos( size/2   + sin( s.az * 2 * MY_PI / 360.0 ) * el_s,
                       size/2   - cos( s.az * 2 * MY_PI / 360.0 ) * el_s );

        // define the color's alpha value (0.3 or 1.0)
        QColor innerColor = s.innerColor;
        QColor outerColor = s.outerColor;
        QColor fontColor  = s.fontColor;
        if( s.state & SatelliteState::Visible )
        {
           innerColor.setAlphaF( 1.0 );
           outerColor.setAlphaF( 1.0 );
           fontColor.setAlphaF( 1.0 );
        }
        else
        {
           innerColor.setAlphaF( 0.3 );
           outerColor.setAlphaF( 0.3 );
           fontColor.setAlphaF( 0.3 );
        }

        // paint the inner circle
        innerBrush.setColor( innerColor );
        painter.setBrush( innerBrush );
        if( s.state & SatelliteState::Marked )
           painter.setPen( QPen( outerColor, satelliteSize/4 ) );
        else
           painter.setPen( QPen( p_gridColor, 0 ) );
        painter.drawEllipse(
              satPos,
              static_cast< int >( satelliteSize ),
              static_cast< int >( satelliteSize ) );


        // write the text
        painter.setPen( QPen( fontColor, 1 ) );
        painter.setFont(
              QFont( "Arial",
              static_cast< int >( satelliteSize ),
              QFont::Bold ) );
        labelRect.moveCenter( satPos );
        painter.drawText( labelRect, Qt::AlignCenter, s.label );

     }

}

void TestSkyWidget::insert(
                        int id,
                        float az,
                        float el,
                        const QString & label,
                        const QColor & outerColor,
                        const QColor & innerColor,
                        const QColor & fontColor,
                        SatelliteState  state )
{
   Satellite   sat;
   sat.label      = label;
   sat.az         = az;
   sat.el         = el;
   sat.state      = state;
   sat.innerColor = innerColor;
   sat.outerColor = outerColor;
   sat.fontColor  = fontColor;

   this->update();

   satellites.insert( id, sat );
}


void TestSkyWidget::remove( int id )
{
   satellites.remove( id );
}


bool TestSkyWidget::contains( int id ) const
{
    return satellites.contains( id );
}


QColor TestSkyWidget::innerColor( int id ) const
{
   return satellites[ id ].innerColor;
}

QColor TestSkyWidget::outerColor( int id ) const
{
   return satellites[ id ].outerColor;
}

QColor TestSkyWidget::fontColor( int id ) const
{
   return satellites[ id ].fontColor;
}

void  TestSkyWidget::setInnerColor( int id, const QColor & c )
{
   satellites[ id ].innerColor = c;
   this->update();
}

void TestSkyWidget::setOuterColor( int id, const QColor & c )
{
   satellites[ id ].outerColor = c;
}

void TestSkyWidget::setFontColor( int id, const QColor & c )
{
   satellites[ id ].fontColor = c;
}


TestSkyWidget::SatelliteState TestSkyWidget::state( int id ) const
{
   return satellites[ id ].state;
}

void  TestSkyWidget::setState( int id, SatelliteState state )
{
   satellites[ id ].state = state;
   this->update();
}


QString TestSkyWidget::label( int id ) const
{
   return satellites[ id ].label;
}

void TestSkyWidget::setLabel( int id, const QString & label )
{
   satellites[ id ].label = label;
   this->update();
}


float TestSkyWidget::azimuth( int id ) const
{
   return satellites[ id ].az;
}

float TestSkyWidget::elevation( int id ) const
{
   return satellites[ id ].el;
}

void TestSkyWidget::setAzimuth( int id, float az )
{
   satellites[ id ].az = az;
   this->update();
}

void TestSkyWidget::setElevation( int id, float el )
{
   satellites[ id ].el = el;
   this->update();
}

QList<int> TestSkyWidget::ids( void ) const
{
   return satellites.keys();
}


TestSkyWidget::SatelliteState operator|
(
      TestSkyWidget::SatelliteState lhs,
      TestSkyWidget::SatelliteState rhs
)
{
   return static_cast< TestSkyWidget::SatelliteState >
           (
               static_cast< quint8 >( lhs ) | static_cast< quint8 >( rhs )
           );
}

void TestSkyWidget::timerEvent(QTimerEvent *event)
{
    if(m_timerId == event->timerId())
    {
        m_pieRotate -= 10;
        update();
    }
    else if(m_pointTimerId == event->timerId())
    {
        //随机更换装饰的点
        for(int i = 0; i < m_points.count(); ++i)
        {
            int offsetX = rand()%widgetSize.width();
            int offsetY = rand()%widgetSize.width();
            int alapha = rand()%255;
            m_points.replace(i,QPoint(offsetX,offsetY) + widgetSize.topLeft());
            m_pointsAlapha.replace(i,alapha);
        }

        update();
    }
}



void TestSkyWidget::resizeEvent(QResizeEvent *)
{
    if(width() > height())
    {
        widgetSize = QRect((width() - height())/1000 ,0,height(),height());
    }
    else
    {
        widgetSize = QRect(0,(height() - width())/1000 ,width(),width());
    }

    //widgetSize.adjust(10,10,-10,-10);
    //widgetSize.adjust(5,5,-10,-10);

}



