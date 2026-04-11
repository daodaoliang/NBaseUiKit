#include "nfontawesomeanim.h"

/**
 * 作者: daodaoliang
 * 时间: 2026年4月09日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QVariant>

namespace fa {

NFontAwesomeAnim::NFontAwesomeAnim(QWidget* parentWidget, int interval, int step)
    : QObject(parentWidget)
    , mParentWidgetRef(parentWidget)
    , mTimer(new QTimer(this))
    , mInterval(interval)
    , mStep(step)
    , mAngle(0)
{
    connect(mTimer, SIGNAL(timeout()), this, SLOT(update()));
    mTimer->start(mInterval);
}

void NFontAwesomeAnim::update()
{
    mAngle += mStep;
    if (mAngle > 360) {
        mAngle -= 360;
    }
    if (mParentWidgetRef) {
        mParentWidgetRef->update();
    }
}

void NFontAwesomeAnim::setup(QPainter& painter, const QRect& rect)
{
    painter.translate(rect.center());
    painter.rotate(mAngle);
    painter.translate(-rect.center());
}

} // namespace fa
