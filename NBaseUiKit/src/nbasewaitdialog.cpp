#include "nbasewaitdialog.h"
#include <QKeyEvent>
#include <QEventLoop>
#include <QTimer>
#include <QCoreApplication>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include "waitingspinnerwidget.h"

WaitingSpinnerWidget * innerSpin;

NBaseWaitDialog::NBaseWaitDialog(QWidget *parent, WaitStyle paramStyle)
    :parentObj(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    setWindowOpacity(0.9);
    isShow = false;
    switch (paramStyle) {
    case BOXSTYLE:
        setBoxStyle();
        break;
    case ANDROIDSTYLE:
        setAndroidStyle();
        break;
    default:
        setBoxStyle();
        break;
    }
}

bool NBaseWaitDialog::showWaitDialog()
{
    QWidget *parentObj = (QWidget *)(parent());
    if(parentObj != NULL) setGeometry(parentObj->width()/2-width()/2,parentObj->height()/2-height()/2,width(),height());
    // 增加spinbox
    innerSpin->start();
    // 显示
    show();
    isShow = true;
    return true;
}

void NBaseWaitDialog::closeWaitDialog()
{
    qDebug()<<"daodaoliang";
    innerSpin->stop();
    hide();
    isShow = false;
}

void NBaseWaitDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
}

void NBaseWaitDialog::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    NBaseShadowWidget::paintEvent(event);
}

void NBaseWaitDialog::moveEvent(QMoveEvent *event)
{
    if(isShow && parentObj){
        QPoint newPos = event->pos();
        QPoint fatherPos = parentObj->pos();
        if(newPos.x()<fatherPos.x()){
            if(newPos.y()<fatherPos.y()) move(fatherPos.x(),fatherPos.y());
            else if (newPos.y()>=fatherPos.y()&&newPos.y()<=fatherPos.y()+parentObj->height()-height()) move(fatherPos.x(), newPos.y());
            else move(fatherPos.x(), fatherPos.y()+parentObj->height()-height());
        } else if (fatherPos.x() <= newPos.x() && newPos.x() <= fatherPos.x() + parentObj->width() - width()) {
            if(newPos.y()<fatherPos.y()) move(newPos.x(),fatherPos.y());
            else if (newPos.y()>=fatherPos.y()&&newPos.y()<=fatherPos.y()+parentObj->height()-height()) event->accept();
            else move(newPos.x(), fatherPos.y()+parentObj->height()-height());
        } else {
            if(newPos.y()<fatherPos.y()) move(fatherPos.x()+parentObj->width()-width(),fatherPos.y());
            else if (newPos.y()>=fatherPos.y()&&newPos.y()<=fatherPos.y()+parentObj->height()-height()) move(fatherPos.x()+parentObj->width()-width(),newPos.y());
            else move(fatherPos.x()+parentObj->width()-width(), fatherPos.y()+parentObj->height()-height());
        }
        event->ignore();
    }
    event->ignore();
}

void NBaseWaitDialog::setBoxStyle()
{
    setFixedSize(300, 250);
    // 增加辅助控件(标题)
    QLabel *innerTitleLabel = new QLabel("我是测试标题", this);
    innerTitleLabel->setFont(QFont("微软雅黑", 13, QFont::Bold));
    innerTitleLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    innerTitleLabel->setStyleSheet("background-color:rgb(41,146,204);"
                                   "color:white;");
    innerTitleLabel->setGeometry(this->x() + 18 , this->y() + 18, this->width() - 36, 40);

    // 增加辅助控件(按钮)
    QPushButton *innerCancleBtn = new QPushButton("关闭", this);
    innerCancleBtn->setFont(QFont("微软雅黑", 13, QFont::Bold));
    innerCancleBtn->setEnabled(true);
    innerCancleBtn->setStyleSheet("background-color:rgb(41,146,204);"
                                  "border:1px solid;"
                                  "border-color:rgb(41,146,204);"
                                  "color:white;");
    innerCancleBtn->setGeometry(this->x() + this->width()/2 - 50, this->y() + this->height() - 50, 100, 30);
    connect(innerCancleBtn, SIGNAL(clicked(bool)), this, SLOT(closeWaitDialog()));

    // 增加辅助控件(中间面板)
    QWidget *innerCenter = new QWidget(this);
    innerCenter->setStyleSheet("border-top:0.5px solid;"
                               "border-top-color: rgb(50,55,51);"
                               "border-bottom:0.5px solid;"
                               "border-bottom-color: rgb(50,55,51);");
    innerCenter->setGeometry(this->x() + 18 , this->y() + 58, this->width() - 36, this->height() - 110);

    // 设置spinbox
    innerSpin = new WaitingSpinnerWidget(innerCenter);
    innerSpin->setRoundness(70.0);
    innerSpin->setMinimumTrailOpacity(15.0);
    innerSpin->setTrailFadePercentage(70.0);
    innerSpin->setNumberOfLines(17);
    innerSpin->setLineLength(13);
    innerSpin->setLineWidth(4);
    innerSpin->setInnerRadius(13);
    innerSpin->setRevolutionsPerSecond(1);
    innerSpin->setColor(QColor(41,146,204));
}

void NBaseWaitDialog::setAndroidStyle()
{
    setFixedSize(300, 100);
    // 增加左边辅助面板
    QWidget *left = new QWidget(this);
    left->setGeometry(0,18,90,this->height()-36);
    // 增加右边文字面板
    QLabel *right = new QLabel(QString("请耐心等候……"),this);
    right->setFont(QFont("微软雅黑", 14, QFont::Bold));
    right->setAlignment(Qt::AlignCenter);
    right->setGeometry(90,18,200,this->height()-36);
    right->setStyleSheet("color:rgb(50,55,50);");
    // 设置spinbox
    innerSpin = new WaitingSpinnerWidget(left);
    innerSpin->setRoundness(70.0);
    innerSpin->setMinimumTrailOpacity(15.0);
    innerSpin->setTrailFadePercentage(70.0);
    innerSpin->setNumberOfLines(17);
    innerSpin->setLineLength(13);
    innerSpin->setLineWidth(4);
    innerSpin->setInnerRadius(13);
    innerSpin->setRevolutionsPerSecond(1);
    innerSpin->setColor(QColor(41,146,204));
}
