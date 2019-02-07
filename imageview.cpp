#include "imageview.h"

ImageView::ImageView(QWidget *parent)
:QGraphicsView(parent)
{
}


ImageView::~ImageView()
{
}

void ImageView::paintEvent( QPaintEvent *event )
{
    QPainter widgetpainter( viewport() );
    widgetpainter.setWorldTransform( _matrix );

    widgetpainter.drawImage( 0, 0, _view_image );
}


void ImageView::setImage( const QImage &image )
{
    _view_image = QImage( image );
    _view_image_transformed = _view_image;
    viewport()->update();
}

void ImageView::scaleView( qreal factor, const QPointF &center )
{
    factor/=5;//-0.1 <-> 0.1
    factor+=1;//0.9 <-> 1.1

    //limit zoom out ---
    if (_matrix.m11()==1 && factor < 1)
    {
        return;
    }

    if (_matrix.m11()*factor<1)
    {
        factor = 1/_matrix.m11();
    }

    //limit zoom in ---
    if (_matrix.m11()>100 && factor > 1)
    {
        return;
    }

    //inverse the transform
    int a, b;
    _matrix_inv.map(center.x(),center.y(),&a,&b);

    _matrix.translate(a-factor*a,b-factor*b);
    _matrix.scale(factor,factor);

    // ここで表示用画像を作成
    if ( viewport()->width() < _view_image.width() )
    {
        _view_image_transformed = _view_image.scaled(
                    viewport()->width()*_matrix.m11(),
                    viewport()->height()*_matrix.m11(),
                    Qt::KeepAspectRatio,Qt::FastTransformation);
    }
    controlImagePosition();
}

void ImageView::controlImagePosition()
{
    qreal left, top, right, bottom;
    qreal limRight, limBottom;

    //after check top-left, bottom right corner to avoid getting "out" during zoom/panning
    _matrix.map(0,0,&left,&top);

    if (left > 0)
    {
        _matrix.translate(-left,0);
        left = 0;
    }
    if (top > 0)
    {
        _matrix.translate(0,-top);
        top = 0;
    }

    //-------
    QSize sizeImage = size() * (qreal)_matrix.m11();
    _matrix.map( sizeImage.width(), sizeImage.height(), &right, &bottom );

    limRight = sizeImage.width()/_matrix.m11();
    limBottom = sizeImage.height()/_matrix.m11();

    if ( right < limRight )
    {
        _matrix.translate( limRight-right, 0 );
        right = limRight;
    }
    if ( bottom < limBottom )
    {
        _matrix.translate( 0, limBottom-bottom );
        bottom = limBottom;
    }

    _matrix_inv = _matrix.inverted();

    viewport()->update();
}

void ImageView::mouseMoveEvent( QMouseEvent *event )
{
    QPointF pnt = event->pos();

    if ( _matrix.m11() > 1 && event->buttons() == Qt::LeftButton )
    {
        QPointF pntf = ( pnt - _downPos ) / _matrix.m11();
        _downPos = event->pos();
        _matrix.translate( pntf.x(), pntf.y() );
        controlImagePosition();
        viewport()->update();
    }
}

void ImageView::mousePressEvent( QMouseEvent *event )
{
    _downPos = event->pos();


    // ウィンドウサイズ・画像サイズの比を計算
    double dScale = (double)viewport()->width() / (double)_view_image.width();
    if ( dScale > ( (double)viewport()->height() / (double)_view_image.height() ) )
    {
        dScale = (double)viewport()->height() / (double)_view_image.height();
    }
    dScale *= _matrix.m11();

    // 画像座標を計算してシグナルを発行
    QPoint pnt = _matrix_inv.map( event->pos() );
    emit mousePressed( pnt );
}

void ImageView::wheelEvent( QWheelEvent *event )
{
    this->scaleView(event->delta()/100.0, event->pos());
}
