#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>

#ifdef Q_OS_MAC
    #include <QOpenGLFunctions_4_1_Core>
#else
    #include <QOpenGLFunctions_4_0_Core>
#endif

#include <QTimer>
#include <QVector4D>
#include <QFile>
#include <QKeyEvent>
#include <QApplication>
#include <QFileDialog>
#include <memory>
#include <model.h>
#include <camera.h>
#include <trackball.h>


class OpenGLWidget : public QOpenGLWidget, protected
        #ifdef Q_OS_MAC
          QOpenGLFunctions_4_1_Core
        #else
          QOpenGLFunctions_4_0_Core
        #endif
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    void initializeGL() override;
    void resizeGL(int, int) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;

    std::shared_ptr<Model> model;

    void createVBOs(std::shared_ptr<Model>);
    void destroyVBOs(std::shared_ptr<Model>);
    void createShaders(std::shared_ptr<Model>);
    void destroyShaders(std::shared_ptr<Model>);
    bool wireframe{false};
    bool orthographic{false};

    Camera camera;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    QTimer timer;
    float zoom{0};
    TrackBall trackBall;


signals:
    void statusBarMessage(QString);


public slots:
    void toggleDarkMode(bool);
    void toggleWireframe(bool);
    void toggleOrthographic(bool);
    void showFileOpenDialog();

}
;

#endif // OPENGLWIDGET_H
