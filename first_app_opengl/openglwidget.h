#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
//#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_4_0_Core>
#include <QTimer>


class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

private:
    QTimer timer;
    bool blinkFlag{false};

public slots:
    void toggleDarkMode(bool);

signals:
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // OPENGLWIDGET_H
