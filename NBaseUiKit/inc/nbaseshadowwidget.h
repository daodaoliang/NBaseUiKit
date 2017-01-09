#ifndef NBASESHOWDOWWIDGET_H
#define NBASESHOWDOWWIDGET_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月10日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QEvent>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include "nbaseuikit_global.h"
#include "nbasemoveablewidget.h"

/**
 * @brief The NBaseShowdowWidget class 阴影widget基类
 */
class NBASEUIKITSHARED_EXPORT NBaseShadowWidget : public NBaseMoveableWidget
{
    Q_OBJECT
public:
    /**
     * @brief NBaseShowdowWidget 构造函数
     * @param parent
     */
    explicit NBaseShadowWidget(NBaseMoveableWidget *parent = 0);

protected:
    /**
     * @brief changeEvent 改变事件处理函数
     * @param event
     */
    void changeEvent(QEvent *event);

    /**
     * @brief paintEvent 绘制事件处理函数
     * @param e
     */
    void paintEvent(QPaintEvent *e);

private:
    /**
     * @brief drawShadowPlanA 阴影绘制方案A
     */
    void drawShadowPlanA();

    /**
     * @brief drawShadowPlanB 阴影绘制方案B
     */
    void drawShadowPlanB();

private:
    QPixmap m_shadow;
};

#endif // NBASESHOWDOWWIDGET_H
