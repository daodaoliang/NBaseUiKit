#include "nbasepopwidget.h"

NBasePopWidget::NBasePopWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool);
    mIsPause = false;
    remainTimer = NULL;
    animation = NULL;
}

void NBasePopWidget::showPopDialog(quint32 paramRemainTime)
{
    mremainTime = paramRemainTime * 500;
    this->move((desktop.availableGeometry().width()-this->width()),desktop.availableGeometry().height());
    if(!this->isVisible()){
        show();
        showAnimation();
    }
}

void NBasePopWidget::closePopDialog()
{
    hide();
    clearAll();
}

void NBasePopWidget::pausePopDialog()
{
    if(animation != NULL){
        this->move((desktop.availableGeometry().width()-this->width()),(desktop.availableGeometry().height()-this->height()));
        animation->setPaused(true);
        mIsPause = true;
    }
}

void NBasePopWidget::startPopDialog()
{
    if(mIsPause){
        if(animation != NULL){
            animation->setPaused(false);
            mIsPause = false;
        }
    }
}

void NBasePopWidget::closeAnimation()
{
    if(!mIsPause){
        remainTimer->stop();
        disconnect(remainTimer,SIGNAL(timeout()),this,SLOT(closeAnimation()));
        delete remainTimer;
        remainTimer=NULL;
        animation->setStartValue(QPoint(this->x(),this->y()));
        animation->setEndValue(QPoint((desktop.availableGeometry().width()-this->width()),desktop.availableGeometry().height()+50));
        animation->start();
        connect(animation,SIGNAL(finished()),this,SLOT(clearAll()));
    }
}

void NBasePopWidget::clearAll()
{
    if(animation != NULL){
        disconnect(animation,SIGNAL(finished()),this,SLOT(clearAll()));
        delete animation;
    }
    animation=NULL;
    hide();
}

void NBasePopWidget::showAnimation()
{
    if(!mIsPause){
        animation=new QPropertyAnimation(this,"pos");
        animation->setDuration(mremainTime);
        animation->setEasingCurve(QEasingCurve::OutElastic);
        animation->setStartValue(QPoint(this->x(),this->y()));
        animation->setEndValue(QPoint((desktop.availableGeometry().width()-this->width()),(desktop.availableGeometry().height()-this->height())));
        connect(animation,SIGNAL(valueChanged(QVariant)),this,SLOT(animationValueChanged(QVariant)));
        animation->start();
        remainTimer=new QTimer();
        connect(remainTimer,SIGNAL(timeout()),this,SLOT(closeAnimation()));
        remainTimer->start(mremainTime*4);
    }
}

void NBasePopWidget::animationValueChanged(QVariant param_value)
{
    QPoint tempValue = param_value.toPoint();
    Q_UNUSED(tempValue)
}
