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
    qDebug() << d;
    typeOfDraw=d;
    update();
}

int centerX(int screenWidth, int width){
    return (screenWidth-width)/2;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);

    int screenWidth = 250;
    int width = 30;
    switch(typeOfDraw){
        case 0:
            break;
        case 1:
            width = 30;
            painter.drawRect(centerX(screenWidth,width),30,width,60);
            break;
        case 2:
            width = 40;
            painter.drawEllipse(centerX(screenWidth,width),30,width,width);
            break;
        case 3:
            width = 45;
            painter.drawRect(centerX(screenWidth,width),30,width,width);
            break;
        case 4:
            width = 45;
            painter.drawRect(centerX(screenWidth,width),30,width,width);
            break;
        case 5:
            width = 45;
            painter.rotate(45);
            painter.drawRect(centerX(screenWidth,width),30,width,width);
            break;
    }

}
