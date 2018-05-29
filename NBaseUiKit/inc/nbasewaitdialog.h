#ifndef NBASEWAITDIALOG_H
#define NBASEWAITDIALOG_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月16日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QDialog>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>
#include "nbaseshadowwidget.h"
#include "nbaseuikit_global.h"

/**
 * @brief The NBaseWaitDialog class 等待框
 */
class NBASEUIKITSHARED_EXPORT NBaseWaitDialog : public NBaseShadowWidget
{
    Q_OBJECT

public:
    enum WaitStyle{
        // box 风格
        BOXSTYLE,
        // android 风格
        ANDROIDSTYLE
    };

public:
    explicit NBaseWaitDialog(QWidget * parent = NULL, WaitStyle paramStyle=BOXSTYLE);
    ~NBaseWaitDialog(){}

public slots:
    /**
     * @brief showWaitDialog 显示等待框
     * @return
     */
    bool showWaitDialog();

    /**
     * @brief closeWaitDialog 关闭等待框
     * @param flag
     */
    void closeWaitDialog();

protected:
    /**
     * @brief closeEvent 关闭事件
     * @param event
     */
    void closeEvent(QCloseEvent *event);

    /**
     * @brief paintEvent 绘制事件
     * @param event
     */
    void paintEvent(QPaintEvent *event);

    /**
     * @brief moveEvent 移动事件
     * @param event
     */
    void moveEvent(QMoveEvent *event);

private:
    /**
     * @brief setBoxStyle 盒子风格的等待框
     */
    void setBoxStyle();

    /**
     * @brief setAndroidStyle android 风格的等待框
     */
    void setAndroidStyle();
private:
    QWidget *parentObj;
    bool isShow;
};

#endif // NBASEWAITDIALOG_H
