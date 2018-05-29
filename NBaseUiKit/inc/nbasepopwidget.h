#ifndef NBASEPOPWIDGET_H
#define NBASEPOPWIDGET_H


/**
 * 作者: daodaoliang
 * 时间: 2016年8月10日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QPoint>
#include <QTimer>
#include <QDebug>
#include "nbaseuikit_global.h"

/**
 * @brief The NBasePopWidget class 弹出窗体界面
 */
class NBASEUIKITSHARED_EXPORT NBasePopWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief NBasePopWidget 构造函数
     * @param parent
     */
    explicit NBasePopWidget(QWidget *parent = 0);

public slots:
    /**
     * @brief showPopDialog 显示弹出窗口
     * @param paramRemainTime
     */
    void showPopDialog(quint32 paramRemainTime = 6);

    /**
     * @brief closePopDialog 关闭弹出窗口
     */
    void closePopDialog();

    /**
     * @brief pausePopDialog 暂停动画效果
     */
    void pausePopDialog();

    /**
     * @brief startPopDialog 开启动画效果
     */
    void startPopDialog();

private slots:

    /**
     * @brief closeAnimation 弹出窗消失时的动画效果
     */
    void closeAnimation();

    /**
     * @brief clearAll 清除弹出框消失时的动画并关闭窗体
     */
    void clearAll();

    /**
     * @brief showAnimation 弹出框显示时的动画效果
     */
    void showAnimation();

    /**
     * @brief animationValueChanged 属性值发生改变时的槽函数
     * @param param_value
     */
    void animationValueChanged(QVariant param_value);

private:

    /**
     * @brief desktop 窗体桌面信息
     */
    QDesktopWidget desktop;


    /**
     * @brief animation 当前动画指针
     */
    QPropertyAnimation* animation;

    /**
     * @brief remainTimer 出场动画和落场动画之间的时间间隔定时器(窗体停留时间)
     */
    QTimer *remainTimer;


    /**
     * @brief mremainTime 动画效果持续的时间
     */
    quint32 mremainTime;

    /**
     * @brief mIsPause 动画效果是否处于暂停
     */
    bool mIsPause;
};

#endif // NBASEPOPWIDGET_H
