#ifndef IMAGECROPPER_H
#define IMAGECROPPER_H

#include "imagecropper_p.h"
#include "imagecropper_e.h"
#include <QWidget>

class ImageCropper : public QWidget
{
    Q_OBJECT

public:
    ImageCropper(QWidget *parent = 0);
    ~ImageCropper();

public slots:
    void setImage(const QPixmap& _image);

    void setBackgroundColor(const QColor& _backgroundColor);

    void setCroppingRectBorderColor(const QColor& _borderColor);

    void setProportion(const QSizeF& _proportion);

    void setProportionFixed(const bool _isFixed);

public:

    const QPixmap cropImage();

protected:
    virtual void paintEvent(QPaintEvent* _event);
    virtual void mousePressEvent(QMouseEvent* _event);
    virtual void mouseMoveEvent(QMouseEvent* _event);
    virtual void mouseReleaseEvent(QMouseEvent* _event);

private:

    CursorPosition cursorPosition(const QRectF& _cropRect, const QPointF& _mousePosition);

    void updateCursorIcon(const QPointF& _mousePosition);

    const QRectF calculateGeometry(
            const QRectF& _sourceGeometry,
            const CursorPosition _cursorPosition,
            const QPointF& _mouseDelta
            );

    const QRectF calculateGeometryWithCustomProportions(
            const QRectF& _sourceGeometry,
            const CursorPosition _cursorPosition,
            const QPointF& _mouseDelta
            );

    const QRectF calculateGeometryWithFixedProportions(const QRectF &_sourceGeometry,
                                                       const CursorPosition _cursorPosition,
                                                       const QPointF &_mouseDelta,
                                                       const QSizeF &_deltas
                                                       );

private:

    ImageCropperPrivate* pimpl;
};

#endif // IMAGECROPPER_H
