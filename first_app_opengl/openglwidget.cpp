#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1,1,1,1);
}

void OpenGLWidget::resizeGL(int w, int h)
{}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

float fromRGBtoGLFloat (int value) {
    return value/255;
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
