#ifndef NBASESNOWLABEL_H
#define NBASESNOWLABEL_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月10日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include "nbaseuikit_global.h"

/**
 * @brief The NBaseSnowLabel class Label前面加红色星号
 */
class NBASEUIKITSHARED_EXPORT NBaseSnowLabel : public QLabel
{
    Q_OBJECT
public:
    explicit NBaseSnowLabel(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // NBASESNOWLABEL_H
