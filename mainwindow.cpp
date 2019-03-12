#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // centralwidgetにimageViewerを設定する
    this->setCentralWidget(ui->ImageViewer);

    // 画像のロード、貼り付け
    ui->ImageViewer->setImage(QImage("your image path"));

    connect(ui->ImageViewer, SIGNAL(mousePressed(QPoint)), this, SLOT(imagePressEvent(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->ImageViewer->alignCenter();
}

void MainWindow::imagePressEvent(QPoint p)
{
    //qDebug() << "press point: " << p;
}
