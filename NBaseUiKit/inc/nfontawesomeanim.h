#ifndef NFONTAWESOMEANIM_H
#define NFONTAWESOMEANIM_H

/**
 * 作者: daodaoliang
 * 时间: 2026年4月09日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include "nbaseuikit_global.h"

class QPainter;
class QRect;
class QTimer;
class QWidget;

namespace fa {

/**
 * @brief The NFontAwesomeAnim class 图标动画类
 */
class NBASEUIKITSHARED_EXPORT NFontAwesomeAnim : public QObject
{
    Q_OBJECT

public:
    explicit NFontAwesomeAnim(QWidget* parentWidget, int interval = 10, int step = 1);
    void setup(QPainter& painter, const QRect& rect);

public slots:
    void update();

private:
    QWidget* mParentWidgetRef;
    QTimer* mTimer;
    int mInterval;
    int mStep;
    float mAngle;
};

} // namespace fa

#endif // NFONTAWESOMEANIM_H
