
#include <QApplication>
#include <QSurfaceFormat>
#include "mainwindow.h"

int main (int argc , char * argv [])
{
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    QSurfaceFormat format ;
    #ifdef Q_OS_MAC
        format . setVersion (4, 1);
        format . setProfile ( QSurfaceFormat :: CoreProfile );
    #endif
    format . setDepthBufferSize (24) ; // Definining depth buffer precision
    format . setSamples (4) ; // Defining anti - aliasing
    QSurfaceFormat :: setDefaultFormat ( format );
    QApplication a(argc , argv );
    MainWindow w;
    w. show ();
    return a. exec ();
}
