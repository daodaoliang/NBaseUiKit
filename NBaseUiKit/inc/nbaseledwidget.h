#ifndef NBASELEDWIDGET_H
#define NBASELEDWIDGET_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月11日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QPainter>
#include "nbaseuikit_global.h"

/**
 * @brief The NBaseLEDWidget class 仿LED效果的widget
 */
class NBASEUIKITSHARED_EXPORT NBaseLEDWidget : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Effect)
    Q_PROPERTY(Effect effect READ effect WRITE setEffect)
    Q_PROPERTY(QColor colorText READ colorText WRITE setTextColor)
    Q_PROPERTY(QColor colorBackground READ colorBackground WRITE setBackgroundColor)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(int timer READ timerInterval WRITE setTimer)
    Q_PROPERTY(bool start READ isStart WRITE startEffect)

public:
    explicit NBaseLEDWidget(QWidget *parent = 0);
    /**
     * @brief The Effect enum 特效枚举
     * sliding 为跑马灯效果
     * intermittent 为闪烁效果
     */
    enum Effect
    {
        sliding=1,
        intermittent=2
    };

public slots:
    /**
     * @brief setTextColor 设置文本颜色
     * @param colorTx 颜色
     */
    void setTextColor(QColor colorText);

    /**
     * @brief setBackgroundColor 设置背景颜色
     * @param colorBg 颜色
     */
    void setBackgroundColor(QColor colorBackground);

    /**
     * @brief setEffect 设置特效类型
     * @param effect sliding-为跑马灯效果 intermittent-为闪烁效果
     */
    void setEffect(Effect effect);

    /**
     * @brief setText 设置文本内容
     * @param text 文本
     */
    void setText(QString text);

    /**
     * @brief setTimer 设置定时频率(毫秒)
     * @param timer 频率
     */
    void setTimer(int timer);

    /**
     * @brief startEffect 开始/关闭 特效
     * @param start true-开启 false-关闭
     */
    void startEffect(bool start);

public:
    /**
     * @brief minimumSizeHint 获取最小显示尺寸
     * @return
     */
    QSize minimumSizeHint() const;

    /**
     * @brief sizeHint 获取尺寸
     * @return
     */
    QSize sizeHint() const;

    /**
     * @brief effect 获取特效类型
     * @return
     */
    Effect effect() const;

    /**
     * @brief colorText 获取文字颜色
     * @return
     */
    QColor colorText() const;

    /**
     * @brief colorBackground 获取背景颜色
     * @return
     */
    QColor colorBackground() const;

    /**
     * @brief text 获取文本内容
     * @return
     */
    QString text() const;

    /**
     * @brief timerInterval 获取刷新频率
     * @return
     */
    int timerInterval() const;

    /**
     * @brief isStart 获取特效是否开启中
     * @return
     */
    bool isStart() const;

signals:
    void timeOut();

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
    * @brief paintBorder 绘制边框
    */
   void paintBorder();

   /**
    * @brief paintText 绘制文本
    */
   void	paintText();

   /**
    * @brief paintGrid 绘制网格
    */
   void	paintGrid();

private:
    int timerVal;
    int idTimer;
    double numChar;
    double length;
    bool on;
    bool timerState;
    QString textMsg;
    QString textOff;
    QString textOn;
    QColor textCol;
    QColor backCol;
    Effect typeEff;
};

#endif // NBASELEDWIDGET_H
