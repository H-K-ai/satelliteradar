/*!
 *@file    testskywidget.h
 *@brief   模拟卫星运行航迹位置
 *@version 0.1
 *@section LICENSE Copyright (C) 2017-2117 NCHU ImgProcessing Corporation
 *@writer  MHK
*/

#ifndef TESTSKYWIDGET_H
#define TESTSKYWIDGET_H

#include <QWidget>
#include <QTimer>


const double MY_PI = 3.141592;
class TestSkyWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY( float  marginScale       READ marginScale     WRITE setMarginScale    )
    Q_PROPERTY( float  satelliteScale    READ satelliteScale  WRITE setSatelliteScale )
    Q_PROPERTY( float  fontScale         READ fontScale       WRITE setFontScale      )
    Q_PROPERTY( QColor gridColor         READ gridColor       WRITE setGridColor      )
    Q_PROPERTY( QColor gridTextColor     READ gridTextColor   WRITE setGridTextColor  )
    Q_PROPERTY( int    gridWidth         READ gridWidth       WRITE setGridWidth      )
    Q_PROPERTY( int    ellipses          READ ellipses        WRITE setEllipses       )
    Q_PROPERTY( int    crosses           READ crosses         WRITE setCrosses        )
    Q_PROPERTY( int    textMargin        READ textMargin      WRITE setTextMargin     )
    Q_PROPERTY( int    flashIntervall    READ flashIntervall  WRITE setFlashIntervall )
    Q_PROPERTY( bool   withGridLabels    READ withGridLabels  WRITE setWithGridLabels )
    Q_PROPERTY( bool   antialiased       READ antialiased     WRITE setAntialiased    )


public:
    explicit TestSkyWidget(QWidget *parent = 0);
    ~TestSkyWidget();
public:
    enum SatelliteState : quint8
    {
       Invisible   = 0x00,
       Visible     = 0x01,
       HalfVisible = 0x02,
       Marked      = 0x04,
       Flashing    = 0x06,
       Flashing1    =0x60,
       Flashing2   = 0x80,
    };
    Q_ENUMS( SatelliteState )

    void  setMarginScale    ( float          scale ){ p_marginScale    = scale;       this->update(); }
    void  setSatelliteScale ( float          scale ){ p_satScale       = scale;       this->update(); }
    void  setFontScale      ( float          scale ){ p_fontScale      = scale;       this->update(); }
    void  setGridColor      ( const QColor & color ){ p_gridColor      = color;       this->update(); }
    void  setGridTextColor  ( const QColor & color ){ p_gridTextColor  = color;       this->update(); }
    void  setGridWidth      ( int            width ){ p_gridWidth      = width;       this->update(); }
    void  setEllipses       ( int               no ){ p_ellipses       = no;          this->update(); }
    void  setCrosses        ( int               no ){ p_crosses        = no;          this->update(); }
    void  setTextMargin     ( int           margin ){ p_textMargin     = margin;      this->update(); }
    void  setFlashIntervall ( int        intervall ){ p_flashIntervall = intervall;   this->update(); }
    void  setWithGridLabels ( int       withLabels ){ p_withGridLabels = withLabels;  this->update(); }
    void  setAntialiased    ( int      antialiased ){ p_antialiased    = antialiased; this->update(); }

    float          marginScale       ( void ) const { return p_marginScale;    }
    float          satelliteScale    ( void ) const { return p_satScale;       }
    float          fontScale         ( void ) const { return p_fontScale;      }
    const QColor & gridColor         ( void ) const { return p_gridColor;      }
    const QColor & gridTextColor     ( void ) const { return p_gridTextColor;  }
    int            gridWidth         ( void ) const { return p_gridWidth;      }
    int            ellipses          ( void ) const { return p_ellipses;       }
    int            crosses           ( void ) const { return p_crosses;        }
    int            textMargin        ( void ) const { return p_textMargin;     }
    int            flashIntervall    ( void ) const { return p_flashIntervall; }
    int            withGridLabels    ( void ) const { return p_withGridLabels; }
    int            antialiased       ( void ) const { return p_antialiased;    }

    QColor         innerColor     ( int id ) const;
    QColor         outerColor     ( int id ) const;
    QColor         fontColor      ( int id ) const;
    SatelliteState state          ( int id ) const;
    QString        label          ( int id ) const;
    float          azimuth        ( int id ) const;
    float          elevation      ( int id ) const;

    QList<int> ids(void) const;

public slots:
    void insert(
                 int   id,
                 float az = 0,
                 float el = 90.0,
                 const QString & label      = QString(""),
                 const QColor  & outerColor = Qt::red,
                 const QColor  & innerColor = Qt::lightGray,
                 const QColor  & fontColor  = Qt::black,
                 SatelliteState  state      = SatelliteState::Visible
                );

    void remove( int id );
    void setInnerColor  ( int id, const QColor & c       );
    void setOuterColor  ( int id, const QColor & c       );
    void setFontColor   ( int id, const QColor & c       );
    void setState       ( int id, SatelliteState state   );
    void setLabel       ( int id, const QString & label  );
    void setAzimuth     ( int id, float az               );
    void setElevation   ( int id, float el               );
    bool contains( int id ) const;

 private:
    bool      flash;
    QTimer    flashTimer;

    float     p_marginScale;
    float     p_satScale;
    float     p_fontScale;
    QColor    p_gridColor;
    QColor    p_gridTextColor;
    int       p_gridWidth;
    int       p_ellipses;
    int       p_crosses;
    int       p_textMargin;
    int       p_flashIntervall;
    bool      p_withGridLabels;
    bool      p_antialiased;

    typedef struct _Satellite
    {
       QString  label;
       QColor   innerColor;
       QColor   outerColor;
       QColor   fontColor;
       float    az;
       float    el;
       SatelliteState  state;
    } Satellite;

    QHash< int, Satellite > satellites;
protected:
    virtual void paintEvent(QPaintEvent* )Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event);    //定时器事件
    void resizeEvent(QResizeEvent *);

private slots:
    void Change_flash(void);

private:
    QRect         m_drawArea;      //绘制区域
    QRect         widgetSize;
    int           m_pieRotate;     //扇形旋转区域
    int           m_timerId;       //定时器ID
    int           m_pointTimerId;  //变更点定时器
    int           m_nSpeed;        //速度
    QList<QPoint> m_points;        //绘制点
    QList<int>    m_pointsAlapha;  //绘制点颜色alapha值


};

TestSkyWidget::SatelliteState operator|
(
      TestSkyWidget::SatelliteState lhs,
      TestSkyWidget::SatelliteState rhs
 );
#endif // TESTSKYWIDGET_H
