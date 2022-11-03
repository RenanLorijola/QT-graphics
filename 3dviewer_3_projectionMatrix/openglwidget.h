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

    void initializeGL() ;
    void resizeGL(int, int) ;
    void paintGL() ;
    void keyPressEvent(QKeyEvent *event) ;

    std::shared_ptr<Model> model;

    void createVBOs(std::shared_ptr<Model>);
    void destroyVBOs(std::shared_ptr<Model>);
    void createShaders(std::shared_ptr<Model>);
    void destroyShaders(std::shared_ptr<Model>);
    bool wireframe{false};
    bool orthographic{false};

    Camera camera;

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
