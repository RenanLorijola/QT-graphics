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

    void drawSolidSquare();
    void drawColorSquare();
    void drawCircle();
    void drawHeart();

    bool DayNight{false};

    GLuint vboVerticesSquare{0};
    GLuint vboColorsSquare{0};
    GLuint eboIndicesSquare{0};
    GLuint vaoSquare{0};

    GLuint vaoCircle{0};
    GLuint vboVerticesCircle{0};
    const unsigned int steps{719};

    GLuint vaoHeart{0};
    GLuint vboVerticesHeart{0};

    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;

    GLuint shaderProgram{0};

    void createVBOs();
    void createShaders();

    void destroyVBOs();
    void destroyShaders();

    void changeDiagonal();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

public slots:
    void toggleDayNight(bool);
    void keyPressEvent(QKeyEvent *event);

};

#endif // OPENGLWIDGET_H
