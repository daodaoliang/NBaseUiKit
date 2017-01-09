#include "nbasetoolbutton.h"
#include <QStyle>
#include <QDebug>


NBaseToolButton::NBaseToolButton(QWidget *parent) : QWidget(parent)
{
    minButton = new QToolButton(this);
    closeButton = new QToolButton(this);
    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    minButton->setIcon(minPix);
    closeButton->setIcon(closePix);
    minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");
    connect(minButton,SIGNAL(clicked(bool)),this,SLOT(showMinimized()));
    connect(closeButton,SIGNAL(clicked(bool)),this,SLOT(deleteLater()));
    setHideToolButton();
}

void NBaseToolButton::setShowToolButton()
{
    int width = this->width();
    minButton->setGeometry(width-46,5,20,20);
    closeButton->setGeometry(width-25,5,20,20);
    minButton->setHidden(false);
    closeButton->setHidden(false);
}

void NBaseToolButton::setHideToolButton()
{
    minButton->setHidden(true);
    closeButton->setHidden(true);
}
