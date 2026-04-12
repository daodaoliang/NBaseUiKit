#include "nbaseuikittest.h"
#include "ui_nbaseuikittest.h"
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QStatusBar>
#include <QTabWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QMap>
#include <QPair>
#include <QMessageBox>
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
#include "nfontawesome.h"

NBaseUiKitTest::NBaseUiKitTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NBaseUiKitTest)
{
    ui->setupUi(this);
    
    // 连接分类按钮信号
    connect(ui->btnLayout, &QPushButton::clicked, this, &NBaseUiKitTest::onCategoryClicked);
    connect(ui->btnAnimation, &QPushButton::clicked, this, &NBaseUiKitTest::onCategoryClicked);
    connect(ui->btnInput, &QPushButton::clicked, this, &NBaseUiKitTest::onCategoryClicked);
    connect(ui->btnDisplay, &QPushButton::clicked, this, &NBaseUiKitTest::onCategoryClicked);
    connect(ui->btnDialog, &QPushButton::clicked, this, &NBaseUiKitTest::onCategoryClicked);
    connect(ui->btnIcon, &QPushButton::clicked, this, &NBaseUiKitTest::onCategoryClicked);
    connect(ui->btnOther, &QPushButton::clicked, this, &NBaseUiKitTest::onCategoryClicked);
    
    // 初始化状态栏
    ui->statusBar->showMessage("欢迎使用 NBaseUiKit 组件库");
}

NBaseUiKitTest::~NBaseUiKitTest()
{
    delete ui;
}

void NBaseUiKitTest::onCategoryClicked()
{
    // 取消所有按钮的选中状态
    ui->btnLayout->setChecked(false);
    ui->btnAnimation->setChecked(false);
    ui->btnInput->setChecked(false);
    ui->btnDisplay->setChecked(false);
    ui->btnDialog->setChecked(false);
    ui->btnIcon->setChecked(false);
    ui->btnOther->setChecked(false);
    
    // 选中当前点击的按钮
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        senderButton->setChecked(true);
        
        // 根据不同的分类显示不同的内容
        if (senderButton == ui->btnLayout) {
            showLayoutComponents();
        } else if (senderButton == ui->btnAnimation) {
            showAnimationComponents();
        } else if (senderButton == ui->btnInput) {
            showInputComponents();
        } else if (senderButton == ui->btnDisplay) {
            showDisplayComponents();
        } else if (senderButton == ui->btnDialog) {
            showDialogComponents();
        } else if (senderButton == ui->btnIcon) {
            showIconComponents();
        } else if (senderButton == ui->btnOther) {
            showOtherComponents();
        }
    }
}

void NBaseUiKitTest::clearContentLayout()
{
    // 清空内容布局
    QLayoutItem *item;
    while ((item = ui->contentLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void NBaseUiKitTest::showLayoutComponents()
{
    clearContentLayout();
    
    // 添加标题和描述
    QLabel *title = new QLabel("布局组件");
    title->setObjectName("componentTitle");
    ui->contentLayout->addWidget(title);
    
    QLabel *desc = new QLabel("提供各种布局方式和容器组件，用于构建复杂的界面布局。");
    desc->setObjectName("componentDesc");
    desc->setWordWrap(true);
    ui->contentLayout->addWidget(desc);
    
    // 可移动窗体
    addComponent("NBaseMoveableWidget", "可移动的窗体组件，支持拖拽和工具栏", 
                 "NBaseMoveableWidget *widget = new NBaseMoveableWidget();\n" 
                 "widget->setFixedSize(400, 400);\n" 
                 "widget->setShowToolButton();\n" 
                 "widget->show();",
                 []() {
                     NBaseMoveableWidget *test = new NBaseMoveableWidget();
                     QLabel label(test);
                     label.setText("可移动窗体测试");
                     test->setStyleSheet("background-color: rgba(0, 255, 0, 120);");
                     test->setFixedSize(400, 400);
                     test->setShowToolButton();
                     test->show();
                     QTimer::singleShot(5000, test, &QObject::deleteLater);
                 });
    
    // 弹出窗体
    addComponent("NBasePopWidget", "弹出式窗体，从屏幕边缘滑入", 
                 "NBasePopWidget *widget = new NBasePopWidget();\n" 
                 "widget->setFixedSize(400, 400);\n" 
                 "widget->showPopDialog();",
                 []() {
                     NBasePopWidget *test = new NBasePopWidget();
                     test->setFixedHeight(400);
                     test->setFixedWidth(400);
                     test->setStyleSheet("background-color: rgb(170, 255, 255);");
                     test->showPopDialog();
                     QTimer::singleShot(5000, test, &QObject::deleteLater);
                 });
    
    // 翻转页面
    addComponent("NBaseRotatingStackedWidget", "支持3D翻转效果的页面切换组件", 
                 "NBaseRotatingStackedWidget *widget = new NBaseRotatingStackedWidget();\n" 
                 "widget->setFixedSize(400, 500);\n" 
                 "widget->addWidget(page1);\n" 
                 "widget->addWidget(page2);\n" 
                 "widget->show();",
                 []() {
                     NBaseRotatingStackedWidget *test = new NBaseRotatingStackedWidget();
                     test->setFixedSize(400, 500);
                     test->show();
                     
                     QMap<QString, QString> colorMap;
                     colorMap.insert("红色", "background-color:rgb(255, 0, 0);color:white;");
                     colorMap.insert("绿色", "background-color:rgb(0, 255, 0);color:white;");
                     colorMap.insert("蓝色", "background-color:rgb(0, 0, 255);color:white;");
                     
                     for (const QString &item : colorMap.keys()) {
                         QLabel *page = new QLabel(test);
                         page->setStyleSheet(colorMap[item]);
                         page->setText(item);
                         page->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                         page->setFont(QFont("微软雅黑", 18, QFont::Bold));
                         QPushButton *btn = new QPushButton(QString("下一个"), page);
                         btn->setFont(QFont("微软雅黑", 12, QFont::Bold));
                         btn->setFixedWidth(80);
                         btn->setStyleSheet("background-color:rgb(41,176,204);color:white;border:none;border-radius:1px;");
                         connect(btn, &QPushButton::clicked, test, &NBaseRotatingStackedWidget::nextPage);
                         test->addWidget(page);
                     }
                 });
    
    // 触屏列表
    addComponent("NTouchListWidget", "支持触摸滑动的列表组件", 
                 "NTouchListWidget *widget = new NTouchListWidget();\n" 
                 "widget->setFixedSize(200, 500);\n" 
                 "widget->addItem(\"测试项目1\");\n" 
                 "widget->show();",
                 []() {
                     NTouchListWidget *test = new NTouchListWidget();
                     test->setFixedSize(200, 500);
                     test->show();
                     
                     for(int index = 0; index != 20; index++) {
                         test->addItem(QString("测试项目:%1").arg(index));
                     }
                     
                     QTimer::singleShot(10000, test, &QObject::deleteLater);
                 });
}

void NBaseUiKitTest::showAnimationComponents()
{
    clearContentLayout();
    
    QLabel *title = new QLabel("动画效果");
    title->setObjectName("componentTitle");
    ui->contentLayout->addWidget(title);
    
    QLabel *desc = new QLabel("提供各种动画和过渡效果，增强用户界面的视觉体验。");
    desc->setObjectName("componentDesc");
    desc->setWordWrap(true);
    ui->contentLayout->addWidget(desc);
    
    // 渐入渐出窗体
    addComponent("NBaseFadeWidget", "支持渐入渐出动画效果的窗体", 
                 "NBaseFadeWidget *widget = new NBaseFadeWidget();\n" 
                 "widget->setFixedSize(400, 400);\n" 
                 "widget->beginFadeShow(5);",
                 []() {
                     NBaseFadeWidget *test = new NBaseFadeWidget();
                     QLabel label(test);
                     label.setText("渐入渐出窗体测试");
                     test->setFixedSize(400, 400);
                     test->setStyleSheet("background-color: rgba(255, 0, 0, 120);");
                     test->beginFadeShow(5);
                     QTimer::singleShot(5000, test, &QObject::deleteLater);
                 });
    
    // 圆周运动
    addComponent("NBaseCircleAnimationWidget", "实现圆周运动动画效果", 
                 "NBaseCircleAnimationWidget *widget = new NBaseCircleAnimationWidget();\n" 
                 "widget->setCircleInfo(\":miniImage\", 10);\n" 
                 "widget->startAnimation();",
                 []() {
                     NBaseCircleAnimationWidget *test = new NBaseCircleAnimationWidget();
                     test->setCircleInfo(":miniImage", 10);
                     test->move(750, 200);
                     test->show();
                     test->startAnimation();
                     QTimer::singleShot(5000, test, &QObject::deleteLater);
                 });
    
    // LED效果
    addComponent("NBaseLEDWidget", "LED灯效果，支持跑马灯和闪光灯", 
                 "NBaseLEDWidget *widget = new NBaseLEDWidget();\n" 
                 "widget->setText(\"跑马灯效果\");\n" 
                 "widget->setTimer(500);\n" 
                 "widget->startEffect(true);",
                 []() {
                     NBaseLEDWidget *test = new NBaseLEDWidget();
                     test->setFixedSize(300, 40);
                     test->setText("我是跑马灯LED效果");
                     test->setTimer(500);
                     test->startEffect(true);
                     test->show();
                     QTimer::singleShot(5000, test, &QObject::deleteLater);
                 });
    
    // 跑马灯
    addComponent("NBaseMarqueeLabel", "文字跑马灯效果", 
                 "NBaseMarqueeLabel *label = new NBaseMarqueeLabel();\n" 
                 "label->setText(\"跑马灯测试数据\");\n" 
                 "label->setDirection(NBaseMarqueeLabel::RightToLeft);\n" 
                 "label->start();",
                 []() {
                     NBaseMarqueeLabel *test = new NBaseMarqueeLabel();
                     test->setText("我是跑马灯测试数据");
                     test->setFont(QFont("Fixed", 20, QFont::Bold));
                     test->setDirection(NBaseMarqueeLabel::RightToLeft);
                     test->setInterval(50);
                     test->start();
                     test->show();
                     QTimer::singleShot(5000, test, &QObject::deleteLater);
                 });
    
    // 点击波按钮
    addComponent("NBaseClickWave", "点击时产生波纹效果的按钮", 
                 "NBaseClickWave *button = new NBaseClickWave();\n" 
                 "button->setClickColor(QColor(225, 189, 162));\n" 
                 "button->setFixedSize(200, 80);\n" 
                 "button->show();",
                 []() {
                     NBaseClickWave *test = new NBaseClickWave();
                     test->setClickColor(QColor(225, 189, 162));
                     test->setFixedSize(200, 80);
                     test->show();
                     QTimer::singleShot(10000, test, &QObject::deleteLater);
                 });
}

void NBaseUiKitTest::showInputComponents()
{
    clearContentLayout();
    
    QLabel *title = new QLabel("输入控件");
    title->setObjectName("componentTitle");
    ui->contentLayout->addWidget(title);
    
    QLabel *desc = new QLabel("用于用户输入的各种控件组件。");
    desc->setObjectName("componentDesc");
    desc->setWordWrap(true);
    ui->contentLayout->addWidget(desc);
    
    // 验证码
    addComponent("NBaseCaptcha", "生成验证码图片", 
                 "NBaseCaptcha captcha(0, 200, 50, 6);\n" 
                 "QPixmap pixmap = captcha.generateOneCaptcha();\n" 
                 "QString code = captcha.getCurrentCaptcha();",
                 []() {
                     NBaseCaptcha test(0, 200, 50, 6);
                     QLabel *label = new QLabel;
                     label->setPixmap(test.generateOneCaptcha());
                     label->show();
                     QTimer::singleShot(10000, label, &QObject::deleteLater);
                 });
    
    // 图片截取
    addComponent("NBaseImageCropper", "图片截取和编辑组件", 
                 "NBaseImageCropper *cropper = new NBaseImageCropper(nullptr, true, true);\n" 
                 "cropper->setImage(\":testImage\");\n" 
                 "cropper->setSize(400, 600);\n" 
                 "cropper->show();",
                 []() {
                     NBaseImageCropper *test = new NBaseImageCropper(nullptr, true, true);
                     test->setImage(":testImage");
                     test->setSize(400, 600);
                     test->show();
                     QTimer::singleShot(30000, test, &QObject::deleteLater);
                 });
    
    // 开关按钮
    addComponent("NBaseSwitchButton", "开关按钮组件", 
                 "NBaseSwitchButton *button = new NBaseSwitchButton();\n" 
                 "button->show();",
                 []() {
                     NBaseSwitchButton *test = new NBaseSwitchButton();
                     test->show();
                     QTimer::singleShot(10000, test, &QObject::deleteLater);
                 });
}

void NBaseUiKitTest::showDisplayComponents()
{
    clearContentLayout();
    
    QLabel *title = new QLabel("显示控件");
    title->setObjectName("componentTitle");
    ui->contentLayout->addWidget(title);
    
    QLabel *desc = new QLabel("用于展示信息的各种控件组件。");
    desc->setObjectName("componentDesc");
    desc->setWordWrap(true);
    ui->contentLayout->addWidget(desc);
    
    // 迷你窗体
    addComponent("NBaseMiniAppWidget", "迷你应用窗体", 
                 "NBaseMiniAppWidget *widget = new NBaseMiniAppWidget();\n" 
                 "widget->setPixmap(QPixmap(\":miniImage\"));\n" 
                 "widget->show();",
                 []() {
                     NBaseMiniAppWidget *test = new NBaseMiniAppWidget();
                     test->setPixmap(QPixmap(":miniImage"));
                     test->show();
                     QTimer::singleShot(5000, test, &QObject::deleteLater);
                 });
    
    // 阴影窗体
    addComponent("NBaseShadowWidget", "带阴影效果的窗体", 
                 "NBaseShadowWidget *widget = new NBaseShadowWidget();\n" 
                 "widget->setFixedSize(400, 400);\n" 
                 "widget->show();",
                 []() {
                     NBaseShadowWidget *test = new NBaseShadowWidget();
                     test->setFixedSize(400, 400);
                     test->show();
                     QTimer::singleShot(5000, test, &QObject::deleteLater);
                 });
    
    // 雪花标签
    addComponent("NBaseSnowLabel", "雪花效果标签", 
                 "NBaseSnowLabel *label = new NBaseSnowLabel();\n" 
                 "label->setText(\"测试数据\");\n" 
                 "label->show();",
                 []() {
                     NBaseSnowLabel *test = new NBaseSnowLabel();
                     test->setText("我是测试数据");
                     test->setFont(QFont("微软雅黑", 12, QFont::Bold));
                     test->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                     test->setFixedSize(200, 50);
                     test->show();
                     QTimer::singleShot(5000, test, &QObject::deleteLater);
                 });
    
    // 圆形进度条
    addComponent("NBaseRoundProgressBar", "圆形进度条组件", 
                 "NBaseRoundProgressBar *progress = new NBaseRoundProgressBar();\n" 
                 "progress->setOutlinePenWidth(8);\n" 
                 "progress->setDataPenWidth(10);\n" 
                 "progress->setValue(30);\n" 
                 "progress->show();",
                 []() {
                     NBaseRoundProgressBar *test = new NBaseRoundProgressBar();
                     test->setOutlinePenWidth(8);
                     test->setDataPenWidth(10);
                     test->setBarStyle(NBaseRoundProgressBar::StyleLine);
                     test->setDecimals(0);
                     test->setFixedSize(200, 200);
                     test->show();
                     test->setValue(30);
                     QTimer::singleShot(5000, test, &QObject::deleteLater);
                 });
    
    // 阴影标签
    addComponent("NBaseShadowLabel", "带阴影效果的标签", 
                 "NBaseShadowLabel *label = new NBaseShadowLabel(\"测试数据\");\n" 
                 "label->setFont(QFont(\"Fixed\", 25, QFont::Bold));\n" 
                 "label->show();",
                 []() {
                     NBaseShadowLabel *test = new NBaseShadowLabel(" 我是刀刀亮测试数据 ");
                     test->setFont(QFont("Fixed", 25, QFont::Bold));
                     test->setFixedSize(400, 50);
                     test->show();
                     QTimer::singleShot(5000, test, &QObject::deleteLater);
                 });
    
    // 二维码
    addComponent("NBaseQREncodeWidget", "二维码生成组件", 
                 "NBaseQREncodeWidget *qr = new NBaseQREncodeWidget();\n" 
                 "qr->setQrData(\"二维码内容\");\n" 
                 "qr->setQrLogo(\":miniImage\");\n" 
                 "qr->show();",
                 []() {
                     NBaseQREncodeWidget *test = new NBaseQREncodeWidget();
                     test->resize(300, 300);
                     test->setQrData("别扫了，没啥东西");
                     test->setQrLogo(":miniImage");
                     test->show();
                     QTimer::singleShot(5000, test, &QObject::deleteLater);
                 });
}

void NBaseUiKitTest::showDialogComponents()
{
    clearContentLayout();
    
    QLabel *title = new QLabel("对话框");
    title->setObjectName("componentTitle");
    ui->contentLayout->addWidget(title);
    
    QLabel *desc = new QLabel("各种弹窗和对话框组件。");
    desc->setObjectName("componentDesc");
    desc->setWordWrap(true);
    ui->contentLayout->addWidget(desc);
    
    // 等待框
    addComponent("NBaseWaitDialog", "等待对话框组件", 
                 "NBaseWaitDialog *dialog = new NBaseWaitDialog(parent);\n" 
                 "dialog->showWaitDialog();",
                 []() {
                     NBaseWaitDialog *test = new NBaseWaitDialog(nullptr, NBaseWaitDialog::ANDROIDSTYLE);
                     test->showWaitDialog();
                     QTimer::singleShot(15000, test, &QObject::deleteLater);
                 });
    
    // 提示框
    addComponent("NBaseToastr", "消息提示组件", 
                 "NBaseToastr *toastr = new NBaseToastr(parent, \"提示消息\");\n" 
                 "toastr->toastr();",
                 [this]() {
                     NBaseToastr *test = new NBaseToastr(this, "我是刀刀亮测试数据");
                     test->toastr();
                 });
}

void NBaseUiKitTest::showIconComponents()
{
    clearContentLayout();
    
    QLabel *title = new QLabel("图标库");
    title->setObjectName("componentTitle");
    ui->contentLayout->addWidget(title);
    
    QLabel *desc = new QLabel("集成了 QtAwesome 图标库，提供 2000+ 精美图标。");
    desc->setObjectName("componentDesc");
    desc->setWordWrap(true);
    ui->contentLayout->addWidget(desc);
    
    // 图标测试
    addComponent("NFontAwesome", "集成了 QtAwesome 图标库，提供 2000+ 精美图标",
                 "// 初始化\n" 
                 "fa::NFontAwesome *awesome = fa::NFontAwesome::instance();\n" 
                 "awesome->initFontAwesome();\n\n" 
                 "// 通过名称获取图标\n" 
                 "QIcon icon = awesome->icon(\"home\");\n\n" 
                 "// 通过编码获取图标\n" 
                 "QIcon icon2 = awesome->icon(0xf015);",
                 []() {
                     // 完整的图标测试代码
                     QMainWindow *test = new QMainWindow();
                     test->setMinimumSize(1200, 800);
                     test->setWindowTitle("QtAwesome 图标库测试");
                      
                     QWidget *centralWidget = new QWidget(test);
                     test->setCentralWidget(centralWidget);
                      
                     QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
                      
                     fa::NFontAwesome *awesome = fa::NFontAwesome::instance();
                     awesome->initFontAwesome();
                      
                     QStatusBar *statusBar = new QStatusBar(test);
                     test->setStatusBar(statusBar);
                     statusBar->showMessage("点击图标查看名称");
                      
                     QTabWidget *tabWidget = new QTabWidget(centralWidget);
                     mainLayout->addWidget(tabWidget);
                      
                     // Solid 图标
                     QWidget *solidTab = new QWidget();
                     QVBoxLayout *solidLayout = new QVBoxLayout(solidTab);
                     QScrollArea *solidScroll = new QScrollArea();
                     solidScroll->setWidgetResizable(true);
                     
                     QTableWidget *solidTable = new QTableWidget();
                     solidTable->setColumnCount(6);
                     solidTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                     solidTable->verticalHeader()->setDefaultSectionSize(80);
                     solidTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
                     solidTable->setSelectionMode(QAbstractItemView::SingleSelection);
                     solidTable->setSelectionBehavior(QAbstractItemView::SelectItems);
                     solidTable->setFocusPolicy(Qt::NoFocus);
                     solidTable->setStyleSheet("QTableWidget::item:focus { outline: none; }");
                     
                     // 填充 Solid 图标
                     int solidRow = 0;
                     int solidCol = 0;
                     for (const QString &name : awesome->iconNames()) {
                         QIcon icon = awesome->icon(name);
                         QLabel *label = new QLabel();
                         label->setAlignment(Qt::AlignCenter);
                         label->setPixmap(icon.pixmap(48, 48));
                         label->setToolTip(name);
                         
                         if (solidRow >= solidTable->rowCount()) {
                             solidTable->insertRow(solidRow);
                         }
                         
                         solidTable->setCellWidget(solidRow, solidCol, label);
                         
                         QTableWidgetItem *item = new QTableWidgetItem();
                         item->setData(Qt::UserRole, name);
                         solidTable->setItem(solidRow, solidCol, item);
                         
                         solidCol++;
                         if (solidCol >= 6) {
                             solidCol = 0;
                             solidRow++;
                         }
                     }
                     
                     solidScroll->setWidget(solidTable);
                     solidLayout->addWidget(solidScroll);
                     tabWidget->addTab(solidTab, QString("Solid (%1 图标)").arg(awesome->iconNames().size()));
                     
                     // 连接点击信号
                     QObject::connect(solidTable, &QTableWidget::cellClicked, [statusBar, solidTable](int row, int column) {
                         QTableWidgetItem *item = solidTable->item(row, column);
                         if (item) {
                             QString iconName = item->data(Qt::UserRole).toString();
                             statusBar->showMessage(QString("图标名称: %1").arg(iconName));
                         }
                     });
                     
                     test->show();
                 });
}

void NBaseUiKitTest::showOtherComponents()
{
    clearContentLayout();
    
    QLabel *title = new QLabel("其他组件");
    title->setObjectName("componentTitle");
    ui->contentLayout->addWidget(title);
    
    QLabel *desc = new QLabel("未分类的实用组件。");
    desc->setObjectName("componentDesc");
    desc->setWordWrap(true);
    ui->contentLayout->addWidget(desc);
    
    // 卷轴widget
    addComponent("NBaseReelWidget", "卷轴效果的窗体", 
                 "NBaseReelWidget *widget = new NBaseReelWidget();\n" 
                 "widget->setOriPos(QPoint(100, 100));\n" 
                 "widget->setOriSize(QSize(500, 300));\n" 
                 "widget->showExpan();",
                 []() {
                     NBaseReelWidget *test = new NBaseReelWidget;
                     test->setOriPos(QPoint(100, 100));
                     test->setOriSize(QSize(500, 300));
                     test->setShowToolButton();
                     test->showExpan();
                     QTimer::singleShot(10000, test, &QObject::deleteLater);
                 });
    
    // 头像编辑
    addComponent("NBaseLogoWidget", "头像编辑组件", 
                 "NBaseLogoWidget *widget = new NBaseLogoWidget();\n" 
                 "widget->show();",
                 []() {
                     NBaseLogoWidget *test = new NBaseLogoWidget;
                     test->show();
                 });
    
    // 倒计数
    addComponent("NBaseCountDown", "倒计时组件", 
                 "NBaseCountDown *widget = new NBaseCountDown(nullptr, 30);\n" 
                 "widget->setFixedSize(400, 400);\n" 
                 "widget->startCountDown();",
                 []() {
                     NBaseCountDown *test = new NBaseCountDown(nullptr, 30);
                     test->setFixedSize(400, 400);
                     test->startCountDown();
                 });
}

void NBaseUiKitTest::addComponent(const QString &name, const QString &description, const QString &code, std::function<void()> demoFunction)
{
    QGroupBox *groupBox = new QGroupBox(name);
    QVBoxLayout *layout = new QVBoxLayout(groupBox);
    
    // 组件描述
    QLabel *descLabel = new QLabel(description);
    descLabel->setWordWrap(true);
    descLabel->setStyleSheet("font-size: 14px; color: #666; margin-bottom: 10px;");
    layout->addWidget(descLabel);
    
    // 代码示例
    QTextEdit *codeEdit = new QTextEdit();
    codeEdit->setPlainText(code);
    codeEdit->setReadOnly(true);
    codeEdit->setFixedHeight(100);
    layout->addWidget(codeEdit);
    
    // 演示按钮
    QPushButton *demoButton = new QPushButton("运行演示");
    demoButton->setObjectName("demoButton");
    connect(demoButton, &QPushButton::clicked, this, [=]() {
        demoFunction();
        ui->statusBar->showMessage(QString("运行 %1 演示").arg(name));
    });
    
    // 添加垂直弹簧 - 撑满下半部分空间
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addItem(verticalSpacer);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(demoButton);
    layout->addLayout(buttonLayout);
    
    // 限制组件大小，避免占满整个屏幕
    groupBox->setMaximumWidth(800);
    groupBox->setMaximumHeight(280);
    
    ui->contentLayout->addWidget(groupBox);
}
