#ifndef NBASETOOLBUTTON_H
#define NBASETOOLBUTTON_H

/**
 * 作者: daodaoliang
 * 时间: 2016年9月06日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QToolButton>
#include "nbaseuikit_global.h"

class NBASEUIKITSHARED_EXPORT NBaseToolButton : public QWidget
{
    Q_OBJECT
public:
    explicit NBaseToolButton(QWidget *parent = 0);

    void setShowToolButton();
    void setHideToolButton();

public:
    QToolButton *minButton;
    QToolButton *closeButton;
};

#endif // NBASETOOLBUTTON_H
