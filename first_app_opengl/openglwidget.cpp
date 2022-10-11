#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);
    QObject::connect(&timer, &QTimer::timeout,[&](){this->update();});
    timer.start (200);
}

void OpenGLWidget::resizeGL(int w, int h)
{}

void OpenGLWidget::paintGL()
{
    blinkFlag =! blinkFlag;
    if (blinkFlag)
        glClearColor (1, 1, 1, 1);
    else
        glClearColor (0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

float fromRGBtoGLFloat (int value) {
    return value/255.0;
}

void OpenGLWidget::toggleDarkMode(bool changeToDarkMode)
{
    int red = 66;
    int green = 135;
    int blue = 245;
    makeCurrent();
    if(changeToDarkMode)
        glClearColor(0,0,0,1);
    else
        glClearColor(fromRGBtoGLFloat(red),fromRGBtoGLFloat(green),fromRGBtoGLFloat(blue),1);
    update();
}
