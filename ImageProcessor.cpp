#include "ImageProcessor.h"
#include <QImage>

ImageProcessor::ImageProcessor(QObject *parent) : QObject(parent)
{

}

void ImageProcessor::processFrame(const QImage& image)
{
    processImage(image);
}
namespace imgproc {
    void NoProcess::processImage(const QImage& image)
    {
        emit processedFrame(image);
    }
}
