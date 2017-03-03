#ifndef CAMERA_H
#define CAMERA_H

#include <QThread>
class ImageProcessor;
class QCamera;
class QMediaRecorder;
class QCameraImageCapture;
class CameraFrameGrabber;
class QTimer;
/**
 * @brief Thread responsible for all camera signals
 * Lives in it's own thread, do not fuck with it.
 */
class Camera : public QThread
{
        Q_OBJECT
    public:
        explicit Camera(QObject *parent = 0);

    signals:
        void frame(const QImage& img);
        void processedFrame(const QImage& img);
    public slots:
        void setImageProcessor(ImageProcessor* proc);
    protected:
        virtual void run() override;
        ImageProcessor* processor;
        QCamera* camera;
        CameraFrameGrabber* frameGrabber;
        // calls methods in this thread if they are called from another one
        QTimer* methodDelegator;
        //QMediaRecorder* mediaRecorder;
        //QCameraImageCapture* imageCapture;

};

#endif // CAMERA_H
