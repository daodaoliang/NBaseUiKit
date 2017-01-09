#ifndef NBASEMINIAPPWIDGET_H
#define NBASEMINIAPPWIDGET_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月10日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include "nbasemoveablewidget.h"

/**
 * @brief The NBaseMiniAppWidget class mini窗体基类
 */
class NBASEUIKITSHARED_EXPORT NBaseMiniAppWidget : public NBaseMoveableWidget
{
    Q_OBJECT
public:
    explicit NBaseMiniAppWidget(NBaseMoveableWidget *parent = 0);

signals:
    /**
     * @brief signalMiniIconClicked 窗体点击事件
     */
    void signalMiniIconClicked();

public:
    /**
     * @brief setPixmap 设置窗体背景图片
     * @param pixmap
     */
    void setPixmap(QPixmap pixmap);

protected:
    /**
     * @brief enterEvent 时间处理函数
     * @param event
     */
    void enterEvent(QEvent *event);

    /**
     * @brief leaveEvent 鼠标离开事件
     * @param event
     */
    void leaveEvent(QEvent *event);

    /**
     * @brief paintEvent 绘画事件
     * @param event
     */
    void paintEvent(QPaintEvent *event);

    /**
     * @brief mouseDoubleClickEvent 鼠标双击事件
     * @param event
     */
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    /**
     * @brief m_Pixmap 背景图片
     */
    QPixmap m_Pixmap;
};

#endif // NBASEMINIAPPWIDGET_H
