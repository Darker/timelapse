#include "Camera.h"
#include "ImageProcessor.h"
#include "CameraFrameGrabber.h"

#include "stdexcept"

#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>

#include <QMessageBox>
#include <QPalette>

#include <QtWidgets>
#include <QTimer>
Q_DECLARE_METATYPE(QCameraInfo)
Camera::Camera(QObject *parent)
    : QThread(parent)
    , methodDelegator(new QTimer)
    , processor(nullptr)
    , frameGrabber(nullptr)
{
    this->moveToThread(this);
}

void Camera::setImageProcessor(ImageProcessor* proc)
{
    if(proc->parent()!=this)
        proc->setParent(nullptr);
    proc->moveToThread(this);
    proc->setParent(this);
    if(this->processor)
        delete this->processor;
    this->processor = proc;
    connect(processor, &ImageProcessor::processedFrame, this, &Camera::processedFrame);
    //connect(this, &Camera::frame, processor, &ImageProcessor::processFrame);
    if(frameGrabber)
        connect(frameGrabber, &CameraFrameGrabber::frameAvailable, processor, &ImageProcessor::processFrame);
}

void Camera::run()
{
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    const QCameraInfo info = cameras[0];
    camera = new QCamera(QCameraInfo::defaultCamera(), this);
    camera->setViewfinder(frameGrabber = new CameraFrameGrabber(this));
    if(processor) {
        connect(frameGrabber, &CameraFrameGrabber::frameAvailable, processor, &ImageProcessor::processFrame);
    }
    else {
        setImageProcessor(new imgproc::NoProcess(this));
    }
    //connect(camera, SIGNAL(stateChanged(QCamera::State)), this, SLOT(updateCameraState(QCamera::State)));
    //connect(camera, SIGNAL(error(QCamera::Error)), this, SLOT(displayCameraError()));

    //mediaRecorder = new QMediaRecorder(camera);
    //connect(mediaRecorder, SIGNAL(stateChanged(QMediaRecorder::State)), this, SLOT(updateRecorderState(QMediaRecorder::State)));

    //imageCapture = new QCameraImageCapture(camera);

    //connect(mediaRecorder, SIGNAL(durationChanged(qint64)), this, SLOT(updateRecordTime()));
    //connect(mediaRecorder, SIGNAL(error(QMediaRecorder::Error)), this, SLOT(displayRecorderError()));

    //mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));

    //connect(ui->exposureCompensation, SIGNAL(valueChanged(int)), SLOT(setExposureCompensation(int)));

    //camera->setViewfinder(ui->viewfinder);

    //updateCameraState(camera->state());
    //updateLockStatus(camera->lockStatus(), QCamera::UserRequest);
    //updateRecorderState(mediaRecorder->state());

    /*connect(imageCapture, SIGNAL(readyForCaptureChanged(bool)), this, SLOT(readyForCapture(bool)));
    connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(processCapturedImage(int,QImage)));
    connect(imageCapture, SIGNAL(imageSaved(int,QString)), this, SLOT(imageSaved(int,QString)));
    connect(imageCapture, SIGNAL(error(int,QCameraImageCapture::Error,QString)), this,
            SLOT(displayCaptureError(int,QCameraImageCapture::Error,QString)));

    connect(camera, SIGNAL(lockStatusChanged(QCamera::LockStatus,QCamera::LockChangeReason)),
            this, SLOT(updateLockStatus(QCamera::LockStatus,QCamera::LockChangeReason)));
*/
    //ui->captureWidget->setTabEnabled(0, (camera->isCaptureModeSupported(QCamera::CaptureStillImage)));
    //ui->captureWidget->setTabEnabled(1, (camera->isCaptureModeSupported(QCamera::CaptureVideo)));

    //updateCaptureMode();
    camera->start();
    this->exec();
}
