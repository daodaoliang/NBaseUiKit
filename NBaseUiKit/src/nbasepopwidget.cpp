#include "nbasepopwidget.h"
#include <QApplication>

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
    QScreen *screen = QApplication::primaryScreen();
    QRect desktopGeometry = screen->availableGeometry();
    this->move((desktopGeometry.width()-this->width()),desktopGeometry.height());
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
        QScreen *screen = QApplication::primaryScreen();
        QRect desktopGeometry = screen->availableGeometry();
        this->move((desktopGeometry.width()-this->width()),(desktopGeometry.height()-this->height()));
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
        disconnect(remainTimer,&QTimer::timeout,this,&NBasePopWidget::closeAnimation);
        delete remainTimer;
        remainTimer=NULL;
        animation->setStartValue(QPoint(this->x(),this->y()));
        QScreen *screen = QApplication::primaryScreen();
        QRect desktopGeometry = screen->availableGeometry();
        animation->setEndValue(QPoint((desktopGeometry.width()-this->width()),desktopGeometry.height()+50));
        animation->start();
        connect(animation,&QPropertyAnimation::finished,this,&NBasePopWidget::clearAll);
    }
}

void NBasePopWidget::clearAll()
{
    if(animation != NULL){
        disconnect(animation,&QPropertyAnimation::finished,this,&NBasePopWidget::clearAll);
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
        QScreen *screen = QApplication::primaryScreen();
        QRect desktopGeometry = screen->availableGeometry();
        animation->setEndValue(QPoint((desktopGeometry.width()-this->width()),(desktopGeometry.height()-this->height())));
        connect(animation,&QPropertyAnimation::valueChanged,this,&NBasePopWidget::animationValueChanged);
        animation->start();
        remainTimer=new QTimer();
        connect(remainTimer,&QTimer::timeout,this,&NBasePopWidget::closeAnimation);
        remainTimer->start(mremainTime*4);
    }
}

void NBasePopWidget::animationValueChanged(const QVariant &param_value)
{
    QPoint tempValue = param_value.toPoint();
    Q_UNUSED(tempValue)
}
