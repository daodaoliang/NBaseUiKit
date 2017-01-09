#include "imagecropper.h"

#include <QMouseEvent>
#include <QPainter>

namespace {
static const QSize WIDGET_MINIMUM_SIZE(300, 300);
}

ImageCropper::ImageCropper(QWidget* parent) :
    QWidget(parent),
    pimpl(new ImageCropperPrivate)
{
    setMinimumSize(WIDGET_MINIMUM_SIZE);
    setMouseTracking(true);
}

ImageCropper::~ImageCropper()
{
    delete pimpl;
}

void ImageCropper::setImage(const QPixmap& _image)
{
    pimpl->imageForCropping = _image;
    update();
}

void ImageCropper::setBackgroundColor(const QColor& _backgroundColor)
{
    pimpl->backgroundColor = _backgroundColor;
    update();
}

void ImageCropper::setCroppingRectBorderColor(const QColor& _borderColor)
{
    pimpl->croppingRectBorderColor = _borderColor;
    update();
}

void ImageCropper::setProportion(const QSizeF& _proportion)
{
    if (pimpl->proportion != _proportion) {
        pimpl->proportion = _proportion;
        float heightDelta = (float)_proportion.height() / _proportion.width();
        float widthDelta = (float)_proportion.width() / _proportion.height();
        pimpl->deltas.setHeight(heightDelta);
        pimpl->deltas.setWidth(widthDelta);
    }

    if ( pimpl->isProportionFixed ) {
        float croppintRectSideRelation =
                (float)pimpl->croppingRect.width() / pimpl->croppingRect.height();
        float proportionSideRelation =
                (float)pimpl->proportion.width() / pimpl->proportion.height();
        if (croppintRectSideRelation != proportionSideRelation) {
            bool widthShotrerThenHeight =
                    pimpl->croppingRect.width() < pimpl->croppingRect.height();
            if (widthShotrerThenHeight) {
                pimpl->croppingRect.setHeight(
                            pimpl->croppingRect.width() * pimpl->deltas.height());
            } else {
                pimpl->croppingRect.setWidth(
                            pimpl->croppingRect.height() * pimpl->deltas.width());
            }
            update();
        }
    }

}

void ImageCropper::setProportionFixed(const bool _isFixed)
{
    if (pimpl->isProportionFixed != _isFixed) {
        pimpl->isProportionFixed = _isFixed;
        setProportion(pimpl->proportion);
    }
}

const QPixmap ImageCropper::cropImage()
{
    QSize scaledImageSize =
            pimpl->imageForCropping.scaled(
                this->size(), Qt::KeepAspectRatio, Qt::FastTransformation
                ).size();
    float leftDelta = 0;
    float topDelta = 0;
    const float HALF_COUNT = 2;
    if (this->size().height() == scaledImageSize.height()) {
        leftDelta = (this->width() - scaledImageSize.width()) / HALF_COUNT;
    } else {
        topDelta = (this->height() - scaledImageSize.height()) / HALF_COUNT;
    }
    float xScale = (float)pimpl->imageForCropping.width()  / scaledImageSize.width();
    float yScale = (float)pimpl->imageForCropping.height() / scaledImageSize.height();
    QRectF realSizeRect(
                QPointF(pimpl->croppingRect.left() - leftDelta, pimpl->croppingRect.top() - topDelta),
                pimpl->croppingRect.size());
    realSizeRect.setLeft((pimpl->croppingRect.left() - leftDelta) * xScale);
    realSizeRect.setTop ((pimpl->croppingRect.top() - topDelta) * yScale);
    realSizeRect.setWidth(pimpl->croppingRect.width() * xScale);
    realSizeRect.setHeight(pimpl->croppingRect.height() * yScale);
    return pimpl->imageForCropping.copy(realSizeRect.toRect());
}

void ImageCropper::paintEvent(QPaintEvent* _event)
{
    QWidget::paintEvent( _event );
    QPainter widgetPainter(this);
    {
        QPixmap scaledImage =
                pimpl->imageForCropping.scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
        widgetPainter.fillRect( this->rect(), pimpl->backgroundColor );
        if ( this->size().height() == scaledImage.height() ) {
            widgetPainter.drawPixmap( ( this->width() - scaledImage.width() ) / 2, 0, scaledImage );
        } else {
            widgetPainter.drawPixmap( 0, ( this->height() - scaledImage.height() ) / 2, scaledImage );
        }
    }
    {
        if (pimpl->croppingRect.isNull()) {
            const int width = WIDGET_MINIMUM_SIZE.width()/2;
            const int height = WIDGET_MINIMUM_SIZE.height()/2;
            pimpl->croppingRect.setSize(QSize(width, height));
            float x = (this->width() - pimpl->croppingRect.width())/2;
            float y = (this->height() - pimpl->croppingRect.height())/2;
            pimpl->croppingRect.moveTo(x, y);
        }

        QPainterPath p;
        p.addRect(pimpl->croppingRect);
        p.addRect(this->rect());
        widgetPainter.setBrush(QBrush(QColor(0,0,0,120)));
        widgetPainter.setPen(Qt::transparent);
        widgetPainter.drawPath(p);
        widgetPainter.setPen(pimpl->croppingRectBorderColor);
        {
            widgetPainter.setBrush(QBrush(Qt::transparent));
            widgetPainter.drawRect(pimpl->croppingRect);
        }
        {
            widgetPainter.setBrush(QBrush(pimpl->croppingRectBorderColor));
            int leftXCoord   = pimpl->croppingRect.left() - 2;
            int centerXCoord = pimpl->croppingRect.center().x() - 3;
            int rightXCoord  = pimpl->croppingRect.right() - 2;
            int topYCoord    = pimpl->croppingRect.top() - 2;
            int middleYCoord = pimpl->croppingRect.center().y() - 3;
            int bottomYCoord = pimpl->croppingRect.bottom() - 2;
            const QSize pointSize(6, 6);
            QVector<QRect> points;
            points
                    << QRect( QPoint(leftXCoord, topYCoord), pointSize )
                    << QRect( QPoint(leftXCoord, middleYCoord), pointSize )
                    << QRect( QPoint(leftXCoord, bottomYCoord), pointSize )
                    << QRect( QPoint(centerXCoord, topYCoord), pointSize )
                    << QRect( QPoint(centerXCoord, middleYCoord), pointSize )
                    << QRect( QPoint(centerXCoord, bottomYCoord), pointSize )
                    << QRect( QPoint(rightXCoord, topYCoord), pointSize )
                    << QRect( QPoint(rightXCoord, middleYCoord), pointSize )
                    << QRect( QPoint(rightXCoord, bottomYCoord), pointSize );
            widgetPainter.drawRects( points );
        }
        {
            QPen dashPen(pimpl->croppingRectBorderColor);
            dashPen.setStyle(Qt::DashLine);
            widgetPainter.setPen(dashPen);
            widgetPainter.drawLine(
                        QPoint(pimpl->croppingRect.center().x(), pimpl->croppingRect.top()),
                        QPoint(pimpl->croppingRect.center().x(), pimpl->croppingRect.bottom()) );
            widgetPainter.drawLine(
                        QPoint(pimpl->croppingRect.left(), pimpl->croppingRect.center().y()),
                        QPoint(pimpl->croppingRect.right(), pimpl->croppingRect.center().y()) );
        }
    }
    widgetPainter.end();
}

void ImageCropper::mousePressEvent(QMouseEvent* _event)
{
    if (_event->button() == Qt::LeftButton) {
        pimpl->isMousePressed = true;
        pimpl->startMousePos = _event->pos();
        pimpl->lastStaticCroppingRect = pimpl->croppingRect;
    }
    updateCursorIcon(_event->pos());
}

void ImageCropper::mouseMoveEvent(QMouseEvent* _event)
{
    QPointF mousePos = _event->pos();
    if (!pimpl->isMousePressed) {
        pimpl->cursorPosition = cursorPosition(pimpl->croppingRect, mousePos);
        updateCursorIcon(mousePos);
    } else if (pimpl->cursorPosition != CursorPositionUndefined) {
        QPointF mouseDelta;
        mouseDelta.setX( mousePos.x() - pimpl->startMousePos.x() );
        mouseDelta.setY( mousePos.y() - pimpl->startMousePos.y() );
        if (pimpl->cursorPosition != CursorPositionMiddle) {
            QRectF newGeometry =
                    calculateGeometry(
                        pimpl->lastStaticCroppingRect,
                        pimpl->cursorPosition,
                        mouseDelta);
            if (!newGeometry.isNull()) {
                pimpl->croppingRect = newGeometry;
            }
        } else {
            pimpl->croppingRect.moveTo( pimpl->lastStaticCroppingRect.topLeft() + mouseDelta );
        }
        update();
    }
}

void ImageCropper::mouseReleaseEvent(QMouseEvent* _event)
{
    pimpl->isMousePressed = false;
    updateCursorIcon(_event->pos());
}

namespace {
static bool isPointNearSide (const int _sideCoordinate, const int _pointCoordinate)
{
    static const int indent = 10;
    return (_sideCoordinate - indent) < _pointCoordinate && _pointCoordinate < (_sideCoordinate + indent);
}
}

CursorPosition ImageCropper::cursorPosition(const QRectF& _cropRect, const QPointF& _mousePosition)
{
    CursorPosition cursorPosition = CursorPositionUndefined;
    if ( _cropRect.contains( _mousePosition ) ) {
        if (isPointNearSide(_cropRect.top(), _mousePosition.y()) &&
                isPointNearSide(_cropRect.left(), _mousePosition.x())) {
            cursorPosition = CursorPositionTopLeft;
        } else if (isPointNearSide(_cropRect.bottom(), _mousePosition.y()) &&
                   isPointNearSide(_cropRect.left(), _mousePosition.x())) {
            cursorPosition = CursorPositionBottomLeft;
        } else if (isPointNearSide(_cropRect.top(), _mousePosition.y()) &&
                   isPointNearSide(_cropRect.right(), _mousePosition.x())) {
            cursorPosition = CursorPositionTopRight;
        } else if (isPointNearSide(_cropRect.bottom(), _mousePosition.y()) &&
                   isPointNearSide(_cropRect.right(), _mousePosition.x())) {
            cursorPosition = CursorPositionBottomRight;
        } else if (isPointNearSide(_cropRect.left(), _mousePosition.x())) {
            cursorPosition = CursorPositionLeft;
        } else if (isPointNearSide(_cropRect.right(), _mousePosition.x())) {
            cursorPosition = CursorPositionRight;
        } else if (isPointNearSide(_cropRect.top(), _mousePosition.y())) {
            cursorPosition = CursorPositionTop;
        } else if (isPointNearSide(_cropRect.bottom(), _mousePosition.y())) {
            cursorPosition = CursorPositionBottom;
        } else {
            cursorPosition = CursorPositionMiddle;
        }
    }
    return cursorPosition;
}

void ImageCropper::updateCursorIcon(const QPointF& _mousePosition)
{
    QCursor cursorIcon;
    switch (cursorPosition(pimpl->croppingRect, _mousePosition))
    {
    case CursorPositionTopRight:
    case CursorPositionBottomLeft:
        cursorIcon = QCursor(Qt::SizeBDiagCursor);
        break;
    case CursorPositionTopLeft:
    case CursorPositionBottomRight:
        cursorIcon = QCursor(Qt::SizeFDiagCursor);
        break;
    case CursorPositionTop:
    case CursorPositionBottom:
        cursorIcon = QCursor(Qt::SizeVerCursor);
        break;
    case CursorPositionLeft:
    case CursorPositionRight:
        cursorIcon = QCursor(Qt::SizeHorCursor);
        break;
    case CursorPositionMiddle:
        cursorIcon = pimpl->isMousePressed ?
                    QCursor(Qt::ClosedHandCursor) :
                    QCursor(Qt::OpenHandCursor);
        break;
    case CursorPositionUndefined:
    default:
        cursorIcon = QCursor(Qt::ArrowCursor);
        break;
    }
    this->setCursor(cursorIcon);
}

const QRectF ImageCropper::calculateGeometry(
        const QRectF& _sourceGeometry,
        const CursorPosition _cursorPosition,
        const QPointF& _mouseDelta
        )
{
    QRectF resultGeometry;
    if ( pimpl->isProportionFixed ) {
        resultGeometry =
                calculateGeometryWithFixedProportions(
                    _sourceGeometry, _cursorPosition, _mouseDelta, pimpl->deltas);
    } else {
        resultGeometry =
                calculateGeometryWithCustomProportions(
                    _sourceGeometry, _cursorPosition, _mouseDelta);
    }
    if ((resultGeometry.left() >= resultGeometry.right()) ||
            (resultGeometry.top() >= resultGeometry.bottom())) {
        resultGeometry = QRect();
    }
    return resultGeometry;
}

const QRectF ImageCropper::calculateGeometryWithCustomProportions(
        const QRectF& _sourceGeometry,
        const CursorPosition _cursorPosition,
        const QPointF& _mouseDelta
        )
{
    QRectF resultGeometry = _sourceGeometry;
    switch ( _cursorPosition )
    {
    case CursorPositionTopLeft:
        resultGeometry.setLeft( _sourceGeometry.left() + _mouseDelta.x() );
        resultGeometry.setTop ( _sourceGeometry.top()  + _mouseDelta.y() );
        break;
    case CursorPositionTopRight:
        resultGeometry.setTop  ( _sourceGeometry.top()   + _mouseDelta.y() );
        resultGeometry.setRight( _sourceGeometry.right() + _mouseDelta.x() );
        break;
    case CursorPositionBottomLeft:
        resultGeometry.setBottom( _sourceGeometry.bottom() + _mouseDelta.y() );
        resultGeometry.setLeft  ( _sourceGeometry.left()   + _mouseDelta.x() );
        break;
    case CursorPositionBottomRight:
        resultGeometry.setBottom( _sourceGeometry.bottom() + _mouseDelta.y() );
        resultGeometry.setRight ( _sourceGeometry.right()  + _mouseDelta.x() );
        break;
    case CursorPositionTop:
        resultGeometry.setTop( _sourceGeometry.top() + _mouseDelta.y() );
        break;
    case CursorPositionBottom:
        resultGeometry.setBottom( _sourceGeometry.bottom() + _mouseDelta.y() );
        break;
    case CursorPositionLeft:
        resultGeometry.setLeft( _sourceGeometry.left() + _mouseDelta.x() );
        break;
    case CursorPositionRight:
        resultGeometry.setRight( _sourceGeometry.right() + _mouseDelta.x() );
        break;
    default:
        break;
    }
    return resultGeometry;
}

const QRectF ImageCropper::calculateGeometryWithFixedProportions(
        const QRectF& _sourceGeometry,
        const CursorPosition _cursorPosition,
        const QPointF& _mouseDelta,
        const QSizeF& _deltas
        )
{
    QRectF resultGeometry = _sourceGeometry;
    switch (_cursorPosition)
    {
    case CursorPositionLeft:
        resultGeometry.setTop(_sourceGeometry.top() + _mouseDelta.x() * _deltas.height());
        resultGeometry.setLeft(_sourceGeometry.left() + _mouseDelta.x());
        break;
    case CursorPositionRight:
        resultGeometry.setTop(_sourceGeometry.top() - _mouseDelta.x() * _deltas.height());
        resultGeometry.setRight(_sourceGeometry.right() + _mouseDelta.x());
        break;
    case CursorPositionTop:
        resultGeometry.setTop(_sourceGeometry.top() + _mouseDelta.y());
        resultGeometry.setRight(_sourceGeometry.right() - _mouseDelta.y() * _deltas.width());
        break;
    case CursorPositionBottom:
        resultGeometry.setBottom(_sourceGeometry.bottom() + _mouseDelta.y());
        resultGeometry.setRight(_sourceGeometry.right() + _mouseDelta.y() * _deltas.width());
        break;
    case CursorPositionTopLeft:
        if ((_mouseDelta.x() * _deltas.height()) < (_mouseDelta.y())) {
            resultGeometry.setTop(_sourceGeometry.top() + _mouseDelta.x() * _deltas.height());
            resultGeometry.setLeft(_sourceGeometry.left() + _mouseDelta.x());
        } else {
            resultGeometry.setTop(_sourceGeometry.top() + _mouseDelta.y());
            resultGeometry.setLeft(_sourceGeometry.left() + _mouseDelta.y() * _deltas.width());
        }
        break;
    case CursorPositionTopRight:
        if ((_mouseDelta.x() * _deltas.height() * -1) < (_mouseDelta.y())) {
            resultGeometry.setTop(_sourceGeometry.top() - _mouseDelta.x() * _deltas.height());
            resultGeometry.setRight(_sourceGeometry.right() + _mouseDelta.x() );
        } else {
            resultGeometry.setTop(_sourceGeometry.top() + _mouseDelta.y());
            resultGeometry.setRight(_sourceGeometry.right() - _mouseDelta.y() * _deltas.width());
        }
        break;
    case CursorPositionBottomLeft:
        if ((_mouseDelta.x() * _deltas.height()) < (_mouseDelta.y() * -1)) {
            resultGeometry.setBottom(_sourceGeometry.bottom() - _mouseDelta.x() * _deltas.height());
            resultGeometry.setLeft(_sourceGeometry.left() + _mouseDelta.x());
        } else {
            resultGeometry.setBottom(_sourceGeometry.bottom() + _mouseDelta.y());
            resultGeometry.setLeft(_sourceGeometry.left() - _mouseDelta.y() * _deltas.width());
        }
        break;
    case CursorPositionBottomRight:
        if ((_mouseDelta.x() * _deltas.height()) > (_mouseDelta.y())) {
            resultGeometry.setBottom(_sourceGeometry.bottom() + _mouseDelta.x() * _deltas.height());
            resultGeometry.setRight(_sourceGeometry.right() + _mouseDelta.x());
        } else {
            resultGeometry.setBottom(_sourceGeometry.bottom() + _mouseDelta.y());
            resultGeometry.setRight(_sourceGeometry.right() + _mouseDelta.y() * _deltas.width());
        }
        break;
    default:
        break;
    }
    return resultGeometry;
}

