#ifndef NBASEREELWIDGET_H
#define NBASEREELWIDGET_H

/**
 * 作者: daodaoliang
 * 时间: 2016年9月06日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QTimeLine>
#include "nbasemoveablewidget.h"
#include "nbaseuikit_global.h"

/**
 * @brief The NBaseReelWidget class 卷轴widget
 */
class NBASEUIKITSHARED_EXPORT NBaseReelWidget : public NBaseMoveableWidget
{
    Q_OBJECT
public:
    explicit NBaseReelWidget(QWidget *parent = 0);
    /**
     * @brief setOriPos 设置起始位置
     * @param p
     */
    void setOriPos(const QPoint& p);

    /**
     * @brief setOriSize 设置尺寸
     * @param s
     */
    void setOriSize(const QSize& s);

    /**
     * @brief showExpan 以卷轴的方式打开
     */
    void showExpan();

protected:
    /**
     * @brief paintEvent 绘制事件
     * @param event
     */
    void paintEvent(QPaintEvent* event);

private slots:
    /**
     * @brief onExpansion 展开的过程槽函数
     */
    void onExpansion();

private:
    /**
     * @brief bFinally 是否 结束显示
     */
    bool bFinally;

    /**
     * @brief oriPos 起始位置
     */
    QPoint oriPos;

    /**
     * @brief oriSize 尺寸
     */
    QSize  oriSize;

    /**
     * @brief animaExpan 卷轴展开的动画时间线
     */
    QTimeLine animaExpan;

    /**
     * @brief bgColorbegin 卷轴背景颜色渐变开始色
     */
    QColor bgColorbegin;

    /**
     * @brief bgColorEnd 卷轴背景颜色渐变结束色
     */
    QColor bgColorEnd;

    /**
     * @brief bgCorner 卷轴角落的阴影色
     */
    QColor bgCorner;
};

#endif // NBASEREELWIDGET_H
