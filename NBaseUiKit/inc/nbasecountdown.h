#ifndef NBASECOUNTDOWN_H
#define NBASECOUNTDOWN_H

/**
 * 作者: daodaoliang
 * 时间: 2016年9月29日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QPropertyAnimation>
#include "nbasemoveablewidget.h"
#include "nbaseuikit_global.h"


/**
 * @brief The NBaseCountDown class 倒计时带有波纹效果的窗体
 */
class NBASEUIKITSHARED_EXPORT NBaseCountDown : public NBaseMoveableWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal waveRadius READ getWaveRadius WRITE setWaveRadius NOTIFY signalWaveRadius)

public:
    /**
     * @brief NBaseCountDown
     * @param parent
     * @param paramCountDown 默认倒数的开始数量
     */
    explicit NBaseCountDown(QWidget *parent = 0, int paramCountDown=10,bool isfill=false);

    /**
     * @brief startCountDown 开始倒计时
     */
    void startCountDown();

    /**
     * @brief getWaveRadius 获取波纹半径
     * @return
     */
    qreal getWaveRadius() const;

    /**
     * @brief setWaveRadius 设置波纹半径
     * @param value
     */
    void setWaveRadius(const qreal &value);

    /**
     * @brief getCountDown 获取倒计数
     * @return
     */
    int getCountDown() const;

    /**
     * @brief setCountDown 设置倒计数
     * @param value
     */
    void setCountDown(int value);

signals:
    /**
     * @brief signalWaveRadius
     * @param paramWaveRadius 状态值
     */
    void signalWaveRadius(qreal paramWaveRadius);

protected:

    /**
     * @brief paintEvent 绘制事件
     * @param event
     */
    void paintEvent(QPaintEvent *event);

    /**
     * @brief timerEvent 定时器事件
     * @param event
     */
    void timerEvent(QTimerEvent *event);

    /**
     * @brief closeEvent 关闭事件
     * @param event
     */
    void closeEvent(QCloseEvent *event);

private:
    /**
     * @brief innerAnimation 开启内部动画片段
     * @param isPositive 是否是正序的
     */
    void innerAnimation(bool isPositive);

private:
    /**
     * @brief pointX 圆心x坐标
     */
    qreal pointX;

    /**
     * @brief pointY 圆心y坐标
     */
    qreal pointY;

    /**
     * @brief waveRadius 圆形波纹半径
     */
    qreal waveRadius;

    /**
     * @brief timerId 倒计时的ID
     */
    int timerId;

    /**
     * @brief countDown 倒计时的开始数量
     */
    int countDown;

    /**
     * @brief innerAnima 内部动画
     */
    QPropertyAnimation *innerAnima;

    /**
     * @brief coreRadius 内核圆半径
     */
    int coreRadius;

    /**
     * @brief isFlag 顺序标记
     */
    bool isFlag;

    /**
     * @brief backColor 背景波纹色
     */
    QColor backColor;

    /**
     * @brief coreColorBegin 核心圆开始颜色
     */
    QColor coreColorBegin;

    /**
     * @brief coreColorMid 核心圆中间色
     */
    QColor coreColorMid;

    /**
     * @brief coreColorEnd 核心圆结束色
     */
    QColor coreColorEnd;

    /**
     * @brief changeStep 步长
     */
    int changeStep;

    /**
     * @brief isFill 是否充满窗体
     */
    bool isFill;
};

#endif // NBASECOUNTDOWN_H
