#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

public slots:
    void SelectedDraw(int);
    void SelectedWidth(int);
    void SelectedRed(int);
    void SelectedGreen(int);
    void SelectedBlue(int);

private:
    Ui::MainWindow *ui;
    int typeOfDraw{0};
    int width{15};
    int red{0};
    int green{0};
    int blue{0};
};
#endif // MAINWINDOW_H
