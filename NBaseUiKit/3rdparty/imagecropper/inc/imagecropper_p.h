#ifndef IMAGECROPPER_P_H
#define IMAGECROPPER_P_H

#include "imagecropper_e.h"

#include <QtCore/QRect>
#include <QtGui/QPixmap>
#include <QtGui/QColor>

namespace {
const QRect INIT_CROPPING_RECT = QRect();
const QSizeF INIT_PROPORTION = QSizeF(1.0, 1.0);
}

class ImageCropperPrivate {
public:
    ImageCropperPrivate() :
        imageForCropping(QPixmap()),
        croppingRect(INIT_CROPPING_RECT),
        lastStaticCroppingRect(QRect()),
        cursorPosition(CursorPositionUndefined),
        isMousePressed(false),
        isProportionFixed(false),
        startMousePos(QPoint()),
        proportion(INIT_PROPORTION),
        deltas(INIT_PROPORTION),
        backgroundColor(Qt::black),
        croppingRectBorderColor(Qt::white)
    {}

public:

    QPixmap imageForCropping;

    QRectF croppingRect;

    QRectF lastStaticCroppingRect;

    CursorPosition cursorPosition;

    bool isMousePressed;

    bool isProportionFixed;

    QPointF startMousePos;

    QSizeF proportion;

    QSizeF deltas;

    QColor backgroundColor;

    QColor croppingRectBorderColor;
};

#endif // IMAGECROPPER_P_H
