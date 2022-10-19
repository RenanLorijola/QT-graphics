#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QVector4D>
#include <vector>
#include <QFile>
#include <QApplication>
#include <QKeyEvent>


class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    void drawBlueSquare();
    void drawGraySquare();
    void drawGrayTriangle();
    void drawGreenTriangle();
    void drawSunCircle();
    void drawMoonCircle();
    void drawPinkHeart();
    void drawGrayHeart();
    void drawBrownRectangle();
    void drawGrayRectangle();
    void drawGreenOctagon();
    void drawGrayOctagon();

    bool DayNight{false};

    GLuint vaoSquare{0};
    GLuint eboIndicesSquare{0};
    GLuint vboVerticesSquare{0};

    GLuint vaoCircle{0};
    GLuint vboVerticesCircle{0};
    const unsigned int steps{719};

    GLuint vaoHeart{0};
    GLuint vboVerticesHeart{0};

    GLuint vaoTriangle{0};
    GLuint eboIndicesTriangle{0};
    GLuint vboVerticesTriangle{0};

    GLuint vaoRectangle{0};
    GLuint eboIndicesRectangle{0};
    GLuint vboVerticesRectangle{0};

    GLuint vaoOctagon{0};
    GLuint eboIndicesOctagon{0};
    GLuint vboVerticesOctagon{0};

    GLuint shaderProgram{0};

    void createVBOs();
    void createShaders();

    void destroyVBOs();
    void destroyShaders();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

public slots:
    void toggleDayNight(bool);
    void keyPressEvent(QKeyEvent *event);

};

#endif // OPENGLWIDGET_H
