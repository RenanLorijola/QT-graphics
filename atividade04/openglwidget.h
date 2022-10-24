#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QElapsedTimer>
#include <QTimer>
#include <QVector4D>
#include <QFile>
#include <QKeyEvent>
#include <QApplication>
#include <array>
#include <cmath>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    GLuint vboSquareVertices{0};
    GLuint vboSquareColors{0};
    GLuint eboSquareIndices{0};
    GLuint vaoSquare{0};

    GLuint vboTriangleVertices{0};
    GLuint vboTriangleColors{0};
    GLuint eboTriangleIndices{0};
    GLuint vaoTriangle{0};

    GLuint vboRectangleVertices{0};
    GLuint vboRectangleColors{0};
    GLuint eboRectangleIndices{0};
    GLuint vaoRectangle{0};

    std::vector<QVector4D> verticesSquare;
    std::vector<QVector4D> colorsSquare;
    std::vector<GLuint> indicesSquare;

    std::vector<QVector4D> verticesTriangle;
    std::vector<QVector4D> colorsTriangle;
    std::vector<GLuint> indicesTriangle;

    std::vector<QVector4D> verticesRectangle;
    std::vector<QVector4D> colorsRectangle;
    std::vector<GLuint> indicesRectangle;

    GLuint shaderProgram{0};

    void createVBOs();
    void createShaders();

    void destroyVBOs();
    void destroyShaders();

    float playerPosYOffset{0};
    float playerPosY{0};

    float targetPosYOffset{2.0f};
    float targetPosY{0};

    float blinkScreenTime{0};

    float yBulletSpeed{0};
    float gravityAcc{2.0f};

    QTimer timer;
    QElapsedTimer elapsedTime;

    bool shooting{false};
    int shootingCounter{1};
    int projectileTraceSize{50};
    std::array<float,2> projectilePos;
    int allyHits{0};
    int enemyHits{0};

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
public slots:
    void animate();

signals:
    void updateHitsLabel(QString);
};

#endif // OPENGLWIDGET_H
