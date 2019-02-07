# ImageViewer class

---

[参考(丸パクリ)](http://mf-atelier.sakura.ne.jp/mf-atelier/modules/tips/program/Qt/qt_image.html)


行列計算練習用


| Header:  | #include <imageviewer.h> |
|:-------- |:------------------------ |
| Inherits | QGraphicsView            |


##Public Functions


| ------------:|:--------------------------------------- |
|              | ImageViewer(QWidget *parent = nullptr)  |
| virtual      | ~ImageViewer()                          |
| void         | setImage(const QImage &image)           |
| void         | scaleView(qreal factor, QPointF center) |
| virtual void | mousePressEvent(QMouseEvent *event)     |
| virtual void | mouseMoveEvent(QMouseEvent *event)      |
| virtual void | wheelEvent(QWheelEvent *event)          |


##Protected Functions


| ------------:|:------------------------------ |
| virtual void | paintEvent(QPaintEvent *event) |


##Signals


| ----:|:---------------------- |
| void | mousePressed(QPoint p) |


## Member Function Documentation


## ImageViewer::ImageViewer(QWidget *parent = nullptr)
---
Constructer. Do not anything.


## virtual ImageViewer::~ImageViewer()
---
Destructer. Do not anything.


## void ImageViewer::setImage(const QImage &image)
---
Set image. At the same time, redrawing will be done.


## void ImageViewer::scaleView(qreal factor, QPointF center)
---
Scales the set image according to the magnification.


The magnification is 5 times at maximum, it can not be reduced.


## virtual void ImageViewer::mousePressEvent(QMouseEvent *event)
---
Update the place where the mouse was pressed, and backward calculate the position where the image was clicked from the enlargement ratio.


Reverse calculated coordinates can be received via SIGNAL.


## virtual void ImageViewer::mouseMoveEvent(QMouseEvent *event)
---
Using the coordinates stored with mousePressEvent (), calculate the amount of movement of the image and redraw it.


## virtual void ImageViewer::wheelEvent(QWheelEvent *event)
---
Rotate the wheel upward to enlarge it, and rotate downwards to make it smaller.


## virtual void ImageViewer::paintEvent(QPaintEvent *event)
---
Draw the image.


## void ImageViewer::mousePressed(QPoint p)
---
When the mouse is pressed, the position of the clicked image is transmitted.


