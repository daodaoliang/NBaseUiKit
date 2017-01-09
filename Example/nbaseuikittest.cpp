#include "nbaseuikittest.h"
#include "ui_nbaseuikittest.h"
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>
#include "QMap"
#include "nbasemoveablewidget.h"
#include "nbasefadewidget.h"
#include "nbaseminiappwidget.h"
#include "nbaseshadowwidget.h"
#include "nbasepopwidget.h"
#include "nbasesnowlabel.h"
#include "nbasecircleanimationwidget.h"
#include "nbaseledwidget.h"
#include "nbasemarqueelabel.h"
#include "nbaseqrencodewidget.h"
#include "nbaseroundprogressbar.h"
#include "nbasetoastr.h"
#include "nbaseshadowlabel.h"
#include "nbasewaitdialog.h"
#include "ntouchlistwidget.h"
#include "nbaserotatingstackedwidget.h"
#include "nbasecaptcha.h"
#include "nbaseimagecropper.h"
#include "nbaseswitchbutton.h"
#include "nbasereelwidget.h"
#include "nbaselogowidget.h"
#include "nbaseclickwave.h"
#include "nbasecountdown.h"


NBaseUiKitTest::NBaseUiKitTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NBaseUiKitTest)
{
    ui->setupUi(this);
}

NBaseUiKitTest::~NBaseUiKitTest()
{
    delete ui;
}

void NBaseUiKitTest::on_pushButton_clicked()
{
    // 可以移动窗体的测试用例
    NBaseMoveableWidget *test_case_001 = new NBaseMoveableWidget();
    QLabel test_case_001_label(test_case_001);
    test_case_001_label.setText("可以移动窗体的测试用例");
    test_case_001->setStyleSheet("background-color: rgba(0, 255, 0, 120);");
    test_case_001->setFixedSize(400,400);
    test_case_001->setShowToolButton();
    test_case_001->show();

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_001, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("可以移动窗体的测试用例,执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_2_clicked()
{
    // 渐入渐出窗体测试用例
    NBaseFadeWidget *test_case_002 = new NBaseFadeWidget();
    QLabel test_case_002_label(test_case_002);
    test_case_002_label.setText("渐入渐出窗体测试用例");
    test_case_002->setFixedSize(400, 400);
    test_case_002->setStyleSheet("background-color: rgba(255, 0, 0, 120);");
    test_case_002->beginFadeShow(5);

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_002, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("渐入渐出窗体测试用例,执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_3_clicked()
{
    // 迷你窗体测试用例
    NBaseMiniAppWidget *test_case_003 = new NBaseMiniAppWidget();
    test_case_003->setPixmap(QPixmap(":miniImage"));
    test_case_003->show();

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_003, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("迷你窗体测试用例,执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_4_clicked()
{
    // 阴影窗体测试用例
    NBaseShadowWidget *test_case_004 = new NBaseShadowWidget();
    test_case_004->setFixedSize(400,400);
    test_case_004->show();

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_004, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("阴影窗体测试用例,执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_5_clicked()
{
    // 弹出窗体测试用例
    NBasePopWidget *test_case_005 = new NBasePopWidget();
    test_case_005->setFixedHeight(400);
    test_case_005->setFixedWidth(400);
    test_case_005->setStyleSheet("background-color: rgb(170, 255, 255);");
    test_case_005->showPopDialog();

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_005, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("弹出窗体测试用例,执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_6_clicked()
{
    // snowLabel测试用例
    NBaseSnowLabel *test_case_006 = new NBaseSnowLabel();
    test_case_006->setText("我是测试数据");
    test_case_006->setFont(QFont("微软雅黑", 12, QFont::Bold));
    test_case_006->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    test_case_006->setFixedSize(200,50);
    test_case_006->show();

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_006, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("snowLabel测试用例,执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_8_clicked()
{
    // 圆周运动窗体测试用例
    NBaseCircleAnimationWidget *test_case_007 = new NBaseCircleAnimationWidget();
    test_case_007->setCircleInfo(":miniImage",10);
    test_case_007->move(750,200);
    test_case_007->show();
    test_case_007->startAnimation();

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_007, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("圆周运动窗体测试用例,执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_7_clicked()
{
    // LED窗体测试用例(跑马灯效果)
    NBaseLEDWidget *test_case_008 = new NBaseLEDWidget();
    test_case_008->setFixedSize(300,40);
    test_case_008->setText("我是跑马灯LED效果。");
    test_case_008->setTimer(500);
    test_case_008->startEffect(true);
    test_case_008->show();

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_008, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("LED窗体测试用例,执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_9_clicked()
{
    // LED窗体测试用例(闪光灯效果)
    NBaseLEDWidget *test_case_009 = new NBaseLEDWidget();
    test_case_009->setFixedSize(300,40);
    test_case_009->setText("我是闪光灯LED效果。");
    test_case_009->setTimer(500);
    test_case_009->setEffect(NBaseLEDWidget::intermittent);
    test_case_009->startEffect(true);
    test_case_009->show();

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_009, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("LED窗体测试用例(闪光灯效果),执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_10_clicked()
{
    // 跑马灯label测试用例
    NBaseMarqueeLabel *test_case_010 = new NBaseMarqueeLabel();
    test_case_010->setText("我是跑马灯测试数据");
    test_case_010->setFont(QFont("Fixed", 20, QFont::Bold));
    test_case_010->setDirection(NBaseMarqueeLabel::RightToLeft);
    test_case_010->setInterval(50);
    test_case_010->start();
    test_case_010->show();

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_010, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("跑马灯label测试用例,执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_11_clicked()
{
    // QR测试用例
    NBaseQREncodeWidget *test_case_011 = new NBaseQREncodeWidget();
    test_case_011->resize(300,300);
    test_case_011->setQrData("别扫了，没啥东西");
    test_case_011->setQrLogo(":miniImage");
    test_case_011->show();

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_011, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("QR测试用例,执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_12_clicked()
{
    // 圆形进度条测试用例(甜甜圈样式)
    QPalette p1;
    p1.setBrush(QPalette::AlternateBase, Qt::darkCyan);
    p1.setColor(QPalette::Text, Qt::yellow);
    NBaseRoundProgressBar *test_case_012 = new NBaseRoundProgressBar();
    test_case_012->setOutlinePenWidth(2);
    test_case_012->setPalette(p1);
    test_case_012->setNullPosition(NBaseRoundProgressBar::PositionLeft);
    test_case_012->setDecimals(0);
    test_case_012->setFixedSize(200,200);
    test_case_012->show();

    // 设置进度
    test_case_012->setValue(30);

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_012, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("圆形进度条测试用例(甜甜圈样式),执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_13_clicked()
{
    // 圆形进度条测试用例(线性样式)
    NBaseRoundProgressBar *test_case_013 = new NBaseRoundProgressBar();
    test_case_013->setOutlinePenWidth(8);
    test_case_013->setDataPenWidth(10);
    test_case_013->setBarStyle(NBaseRoundProgressBar::StyleLine);
    test_case_013->setDecimals(0);
    test_case_013->setFixedSize(200,200);
    test_case_013->show();

    // 设置进度
    test_case_013->setValue(30);

    // 5秒后关闭
    QTimer::singleShot(5000, test_case_013, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("圆形进度条测试用例(线性样式),执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_14_clicked()
{
    // toastr 测试用例
    NBaseToastr * test_case_014 = new NBaseToastr(this, "我是刀刀亮测试数据");
    test_case_014->toastr();

    // 日志
    ui->textBrowser->insertPlainText("toastr, 执行成功,三秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_15_clicked()
{
    // 阴影label 测试用例
    NBaseShadowLabel * test_case_015 = new NBaseShadowLabel(" 我是刀刀亮测试数据 ");
    test_case_015->setFont(QFont("Fixed", 25, QFont::Bold));
    test_case_015->setFixedSize(400, 50);
    test_case_015->show();

    // 5 秒后关闭
    QTimer::singleShot(5000, test_case_015, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("阴影label 测试用例,执行成功,五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_16_clicked()
{
    // 等待框(box) 测试用例
    NBaseWaitDialog * test_case_016 = new NBaseWaitDialog(this);
    test_case_016->showWaitDialog();

    // 十秒后关闭
    QTimer::singleShot(15000, test_case_016, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("等待框(box风格) 测试用例,执行成功,十五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_17_clicked()
{
    // 等待框(android) 测试用例
    NBaseWaitDialog * test_case_017 = new NBaseWaitDialog(this, NBaseWaitDialog::ANDROIDSTYLE);
    test_case_017->showWaitDialog();

    // 十秒后关闭
    QTimer::singleShot(15000, test_case_017, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("等待框(android) 测试用例,执行成功,十五秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_18_clicked()
{
    // 触屏列表 测试用例
    NTouchListWidget *test_case_18 = new NTouchListWidget();
    test_case_18->setFixedSize(200,500);
    test_case_18->show();

    // 插入测试数据
    for(int index = 0;index != 200;index++) test_case_18->addItem(QString("测试项目:%1").arg(index));

    // 十秒后关闭
    QTimer::singleShot(30000, test_case_18, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("触屏列表 测试用例,执行成功,三十秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_19_clicked()
{
    // 翻转页面 测试用例
    NBaseRotatingStackedWidget *test_case_19 = new NBaseRotatingStackedWidget();
    test_case_19->setFixedSize(400,500);
    test_case_19->show();

    // 插入测试数据
    QMap<QString, QString> colorMap;
    colorMap.insert("相思灰","background-color:rgb(98,92,82);color:white;");
    colorMap.insert("卡其黄","background-color:rgb(213,184,132);color:white;");
    colorMap.insert("番茄红","background-color:rgb(196,71,61);color:white;");
    colorMap.insert("艳红","background-color:rgb(204,53,54);color:white;");
    colorMap.insert("绛紫","background-color:rgb(112,77,78);color:white;");
    colorMap.insert("浅血牙","background-color:rgb(234,205,209);color:white;");
    colorMap.insert("紫藤灰","background-color:rgb(133,126,149);color:white;");
    colorMap.insert("沙绿","background-color:rgb(0,91,90);color:white;");
    colorMap.insert("鸭蛋青","background-color:rgb(209,227,219);color:white;");
    colorMap.insert("柠檬黄","background-color:rgb(233,219,57);color:white;");
    colorMap.insert("芦灰","background-color:rgb(169,176,143);color:white;");
    colorMap.insert("油烟墨","background-color:rgb(63,63,60);color:white;");
    colorMap.insert("米红","background-color:rgb(225,189,162);color:white;");
    colorMap.insert("十样锦","background-color:rgb(252,177,170);color:white;");
    foreach (QString item, colorMap.keys()) {
        QLabel *page = new QLabel(test_case_19);
        page->setStyleSheet(colorMap[item]);
        page->setText(item);
        page->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        page->setFont(QFont("微软雅黑", 18, QFont::Bold));
        QPushButton *btn = new QPushButton(QString("下一个"),page);
        btn->setFont(QFont("微软雅黑", 12, QFont::Bold));
        btn->setFixedWidth(80);
        btn->setStyleSheet("background-color:rgb(41,176,204);color:white;border:none;border-radius:1px;");
        connect(btn,SIGNAL(clicked(bool)),test_case_19,SLOT(nextPage()));
        test_case_19->addWidget(page);
    }

    // 日志
    ui->textBrowser->insertPlainText("翻转页面 测试用例,执行成功,三十秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_20_clicked()
{
    // 触屏列表 测试用例
    NTouchListWidget *test_case_20 = new NTouchListWidget();
    test_case_20->setFixedSize(500,200);
    test_case_20->setFlow(QListWidget::LeftToRight);
    test_case_20->show();

    // 插入测试数据
    for(int index = 0;index != 200;index++) test_case_20->addItem(QString("测试项目:%1").arg(index));

    // 十秒后关闭
    QTimer::singleShot(30000, test_case_20, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText("触屏列表 测试用例,执行成功,三十秒后将会关闭……\r\n");
}

void NBaseUiKitTest::on_pushButton_21_clicked()
{
    // 验证码 测试用例
    NBaseCaptcha test_case_21(0,200,50,6);
    QLabel *test_case_21_w = new QLabel;
    test_case_21_w->setPixmap(test_case_21.generateOneCaptcha());
    test_case_21_w->move(x()+width()/2, y()+height()/2);
    test_case_21_w->show();

    // 十秒后关闭
    QTimer::singleShot(10000, test_case_21_w, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText(tr("验证码 测试用例,执行成功,当前验证码为:(%1)十秒后将会关闭……\r\n").arg(test_case_21.getCurrentCaptcha()));
}

void NBaseUiKitTest::on_pushButton_22_clicked()
{
    // 图片截取的测试用例
    NBaseImageCropper *test_case_22 = new NBaseImageCropper(nullptr,true,true);
    test_case_22->setImage(":testImage");
    test_case_22->setSize(400,600);
    test_case_22->show();

    // 十秒后关闭
    QTimer::singleShot(30000, test_case_22, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText(tr("图片截取 测试用例,执行成功,三十秒后将会关闭……\r\n"));
}

void NBaseUiKitTest::on_pushButton_23_clicked()
{
    // switch按钮 测试用例
    NBaseSwitchButton *test_case_23 = new NBaseSwitchButton;
    test_case_23->show();

    // 十秒后关闭
    QTimer::singleShot(10000, test_case_23, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText(tr("switch按钮 测试用例,执行成功,十秒后将会关闭……\r\n"));
}

void NBaseUiKitTest::on_pushButton_24_clicked()
{
    // 卷轴widget 测试用例
    NBaseReelWidget *test_case_24 = new NBaseReelWidget;
    test_case_24->setOriPos(QPoint(x()+width()/2-250, y()+height()/2-150));
    test_case_24->setOriSize(QSize(500,300));
    test_case_24->setShowToolButton();
    test_case_24->showExpan();

    // 十秒后关闭
    QTimer::singleShot(10000, test_case_24, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText(tr("卷轴widget 测试用例,执行成功,十秒后将会关闭……\r\n"));
}

void NBaseUiKitTest::on_pushButton_25_clicked()
{
    // 头像编辑 测试用例
    NBaseLogoWidget *test_case_25 = new NBaseLogoWidget;
    test_case_25->show();

    // 日志
    ui->textBrowser->insertPlainText(tr("头像widget 测试用例,执行成功\r\n"));
}

void NBaseUiKitTest::on_pushButton_26_clicked()
{
    // 点击波按钮 测试用例
    NBaseClickWave *test_case_26 = new NBaseClickWave;
    test_case_26->setClickColor(QColor(225,189,162));
    test_case_26->setFixedSize(200,80);
    test_case_26->show();

    // 十秒后关闭
    QTimer::singleShot(10000, test_case_26, SLOT(deleteLater()));

    // 日志
    ui->textBrowser->insertPlainText(tr("点击波按钮 测试用例,执行成功,十秒后将会关闭……\r\n"));
}

void NBaseUiKitTest::on_pushButton_27_clicked()
{
    // 倒计数窗体
    NBaseCountDown *test_case_27 = new NBaseCountDown(nullptr, 30);
    test_case_27->setFixedSize(400,400);
    test_case_27->startCountDown();
    // 日志
    ui->textBrowser->insertPlainText(tr("倒计数窗体 测试用例,执行成功,十秒后将会关闭……\r\n"));
}
