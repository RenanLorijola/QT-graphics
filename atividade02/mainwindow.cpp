#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SelectedDraw(int d){
    typeOfDraw=d;
    update();
}

void MainWindow::SelectedWidth(int w){
    width=w;
    update();
}

void MainWindow::SelectedRed(int r){
    red=r;
    update();
}

void MainWindow::SelectedGreen(int g){
    green=g;
    update();
}

void MainWindow::SelectedBlue(int b){
    blue=b;
    update();
}

int centerX(int screenWidth, int width){
    return (screenWidth-width)/2;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);

    int screenWidth = 300;

    QPointF triangle[3] = {
        QPointF(centerX(screenWidth,width), 70),
        QPointF(centerX(screenWidth,width)+width, 70),
        QPointF(centerX(screenWidth,width)+width/2, 30)
    };

    QRectF rectangle(centerX(screenWidth,width),30,width,70);

    QRectF square(centerX(screenWidth,width),30,width,width);

    QRectF losangle(-(sqrt(2)-1)*width,-(sqrt(2)-1)*(width - 30),width,width);

    QColor color(red, green , blue);
    painter.setBrush(color);

    switch(typeOfDraw){
        case 0:
            break;
        case 1:
            painter.drawRect(rectangle);
            break;
        case 2:
            painter.drawEllipse(square);
            break;
        case 3:
            painter.drawRect(square);
            break;
        case 4:
            painter.drawPolygon(triangle, 3);
            break;
        case 5:
            painter.translate(centerX(screenWidth,width), 30);
            painter.rotate(45);
            painter.translate((sqrt(2)-1)*(width+30), 0);
            painter.drawRect(losangle);
            painter.resetTransform();
            break;
    }

}
