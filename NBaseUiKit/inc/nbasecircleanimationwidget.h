#ifndef NBASECIRCLEANIMATIONWIDGET_H
#define NBASECIRCLEANIMATIONWIDGET_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月10日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPropertyAnimation>
#include <qmath.h>
#include "nbaseuikit_global.h"
#include "nbasemoveablewidget.h"
#define PI  3.1415

class QPropertyAnimation;

/**
 * @brief The NBaseCircleAnimationWidget class 圆周运动的组件类
 */
class NBASEUIKITSHARED_EXPORT NBaseCircleAnimationWidget : public NBaseMoveableWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal percent READ percent WRITE setPercent)

public:
    explicit NBaseCircleAnimationWidget(NBaseMoveableWidget *parent = 0);

    /**
     * @brief NBaseCircleAnimationWidget 构造函数
     * @param icon 背景图片
     * @param radius 圆角度
     * @param parent 父控件
     */
    explicit NBaseCircleAnimationWidget(const QString &icon,const qreal &radius, NBaseMoveableWidget *parent = 0);

public:
    /**
     * @brief setCircleInfo 设置窗体的的信息
     * @param icon
     * @param radius
     */
    void setCircleInfo(const QString &icon, const qreal &radius);

    /**
     * @brief startAnimation 开启动画效果
     */
    void startAnimation();

    /**
     * @brief stopAnimation 结束动画效果
     */
    void stopAnimation();

    /**
     * @brief setPercent 设置位置
     * @param per 位置
     */
    void setPercent(const qreal &per);

    /**
     * @brief percent 位置
     * @return
     */
    const qreal &percent();

protected:
    /**
     * @brief paintEvent 绘制事件
     */
    void paintEvent(QPaintEvent *);

private slots:
    /**
     * @brief updatePos 更新位置
     */
    void updatePos();

private:
    QPoint mathPoint();
    QPoint mathPoint(const QPoint &centerPos, const qreal &percent, const qreal &radius);
    void initAnimation();

private:
    qreal m_percent;
    qreal m_radius;
    QPoint m_centerPos;
    QPropertyAnimation *m_percentAnimation;
    QPixmap m_pix;
    QPoint m_point;
    QPoint m_originPoint;
};

#endif // NBASECIRCLEANIMATIONWIDGET_H
