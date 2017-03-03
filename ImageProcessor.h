#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>

class ImageProcessor : public QObject
{
        Q_OBJECT
    public:
        explicit ImageProcessor(QObject *parent = 0);


    signals:
        void processedFrame(const QImage& img);
    public slots:
        void processFrame(const QImage& image);
    protected:
        //This method is responsible to call processed frame
        // this does not needlesly mean call it for every frame given
        // you can skip frames, generate more frames then given etc...
        virtual void processImage(const QImage& image) = 0;
};
namespace imgproc {
    class NoProcess: public ImageProcessor {
        public:
            NoProcess(QObject *parent = 0): ImageProcessor(parent) {}
        protected:
            void processImage(const QImage &image);
    };
}

#endif // IMAGEPROCESSOR_H
