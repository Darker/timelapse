#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>

class ImageProcessor : public QObject
{
        Q_OBJECT
    public:
        explicit ImageProcessor(QObject *parent = 0);

    signals:

    public slots:
};

#endif // IMAGEPROCESSOR_H