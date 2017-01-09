#ifndef NBASEFADEWIDGET_H
#define NBASEFADEWIDGET_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月10日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "nbasemoveablewidget.h"
#include "nbaseuikit_global.h"

/**
 * @brief The NBaseFadeWidget class 淡入淡出widget
 */
class NBASEUIKITSHARED_EXPORT NBaseFadeWidget : public NBaseMoveableWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ getopacity WRITE setopacity NOTIFY opacityChanged)

public:
    /**
     * @brief NBaseFadeWidget 构造函数
     * @param parent
     */
    explicit NBaseFadeWidget(NBaseMoveableWidget *parent = 0);

signals:
    /**
     * @brief opacityChanged 透明度改变的信号
     * @param param_opacity 当前透明度
     */
    void opacityChanged(qreal param_opacity);

public:
    /**
     * @brief beginFadeShow 开启淡入淡出的效果
     * @param param_seconds param_seconds秒内完成效果动画
     */
    void beginFadeShow(quint32 param_seconds);

    /**
     * @brief setopacity 设置透明度
     * @param param_opacity 透明度
     */
    void setopacity(qreal param_opacity);

    /**
     * @brief getopacity 获取当前透明度
     * @return
     */
    qreal getopacity();

private:
    /**
     * @brief opacity_ 当前透明度
     */
    qreal opacity_;

    /**
     * @brief show_animation_ 显示动画
     */
    QPropertyAnimation *show_animation_;
};

#endif // NBASEFADEWIDGET_H
