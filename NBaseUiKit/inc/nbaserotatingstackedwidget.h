#ifndef NBASEROTATINGSTACKEDWIDGET_H
#define NBASEROTATINGSTACKEDWIDGET_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月10日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QVariant>
#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include <QPainter>
#include <QTransform>
#include <QParallelAnimationGroup>
#include "nbaseuikit_global.h"

/**
 * @brief The NBaseRotatingStackedWidget class 反转的stacked
 */
class NBASEUIKITSHARED_EXPORT NBaseRotatingStackedWidget : public QStackedWidget
{
    Q_OBJECT
    Q_PROPERTY( float rotateVal READ rotateVal WRITE setRotateVal)
public:
    /**
     * @brief NBaseRotatingStackedWidget 构造函数
     * @param parent
     */
    explicit NBaseRotatingStackedWidget(QWidget *parent = 0);

    /**
     * @brief paintEvent 绘制事件
     */
    void paintEvent(QPaintEvent *event);

public slots:
    /**
     * @brief nextPage 下一页
     */
    void nextPage();

public:

    /**
     * @brief rotate index 跳转到索引页
     */
    void rotate(int index);

    /**
     * @brief rotateVal 旋转值
     * @return
     */
    float rotateVal();

    /**
     * @brief setRotateVal 设置旋转值
     * @param fl 值
     */
    void setRotateVal(float fl);

private slots:
    /**
     * @brief valChanged 旋转值改变了
     */
    void valChanged(QVariant);

    /**
     * @brief animDone 动画结束
     */
    void animDone();

private:
    /**
     * @brief iRotateVal 旋转值
     */
    float iRotateVal;

    /**
     * @brief isAnimating 旋转动画中
     */
    bool isAnimating;

    /**
     * @brief nextIndex 下一个索引页
     */
    int nextIndex;
};

#endif // NBASEROTATINGSTACKEDWIDGET_H
