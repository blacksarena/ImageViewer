#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QtGui>
#include <QtWidgets>

class ImageView : public QGraphicsView
{
    Q_OBJECT

public:
    ImageView(QWidget *parent);
    virtual ~ImageView();

    void alignCenter();
    void setImage( const QImage &image );
    void scaleView( qreal factor, const QPointF &center );
    virtual void resizeEvent( QResizeEvent *event ) override;
    virtual void mouseMoveEvent( QMouseEvent *event ) override;
    virtual void mousePressEvent( QMouseEvent *event ) override;
    virtual void wheelEvent( QWheelEvent *event ) override;

protected:
    virtual void paintEvent( QPaintEvent *event );

private:
    QImage _view_image;
    QImage _view_image_transformed;
    QTransform _matrix;
    QTransform _matrix_inv;
    QPointF _downPos;

    void controlImagePosition();

Q_SIGNALS:
    void mousePressed(QPoint p);
};

#endif // IMAGEVIEW_H
