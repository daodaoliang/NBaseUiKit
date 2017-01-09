#ifndef NBASETOASTR_H
#define NBASETOASTR_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月16日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QLabel>
#include "nbaseuikit_global.h"

#define DEFULT_TOAST_STYLE "\
QLabel{\
    color:#FFFFFF;\
    font:18px;\
    font-weight:500;\
    background-color:rgb(98,92,82,90);\
    padding:3px;\
    border-radius:2;\
}\
"

/**
 * @brief The NBaseToastr class 自动消失的提示框
 */
class NBASEUIKITSHARED_EXPORT NBaseToastr : public QLabel
{
    Q_OBJECT
public:
    explicit NBaseToastr(QWidget *parent,
                   const QString &message = QString(),
                   int w = 200,
                   int h = 50,
                   const QString &style = DEFULT_TOAST_STYLE);
    void toastr();

private:
    /**
     * @brief setShadow 设置窗体阴影效果
     * @param w 窗体指针
     * @param blurRadius 阴影清晰度，越小越清晰
     * @param dx x方向阴影位置和偏移量，正值在右方，值越大偏移越大
     * @param dy y方向阴影位置和偏移量，正值在下方，值越大偏移越大
     * @return
     */
    void setShadow(QWidget *w, qreal blurRadius=10, qreal dx=5, qreal dy=5);

private slots:
    void animationFinished();
    void delSelf();

private:
    int startx;
    int starty;
    int endy;
};

#endif // NBASETOASTR_H
