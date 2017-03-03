#include "MainWindow.h"
#include <QApplication>
#include "Camera.h"
#include "ImageProcessor.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Camera* cam = new Camera();
    cam->start();
    if(cam->thread() != cam->thread()->thread()) {
        return 0;
    }
    QObject::connect(cam, &Camera::processedFrame, &w, &MainWindow::displayFrame, Qt::QueuedConnection);

    /*QObject::connect(
      cam,
      &QThread::started,
      cam->thread(),
      [cam]()
      {
        cam->setImageProcessor(new imgproc::NoProcess);
      },
      Qt::QueuedConnection);*/

    a.exec();
    cam->exit(0);
    cam->wait();
    delete cam;
    return 0;
}
