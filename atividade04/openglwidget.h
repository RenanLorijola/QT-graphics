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

    GLuint vboVertices{0};
    GLuint vboColors{0};
    GLuint eboIndices{0};
    GLuint vao{0};

    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;

    GLuint shaderProgram{0};

    void createVBOs();
    void createShaders();

    void destroyVBOs();
    void destroyShaders();

    float playerPosYOffset{0};
    float playerPosY{0};

    float targetPosYOffset{2.0f};
    float targetPosY{0};

    QTimer timer;
    QElapsedTimer elapsedTime;

    bool shooting{false};
    std::array<float,2> projectilePos;
    int numHits{0};

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
