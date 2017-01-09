# 基础UI组件使用说明

[TOC]

## 0.如何添加项目

* 首先拷贝源码到你的工程文件目录;
* 在你的项目 pro文件中添加:

```c
# import dll
win32: LIBS += -L$$PWD/../bin/ -lNBaseUiKit
DEPENDPATH += $$PWD/../bin

# import dll file
include($$PWD/../NBaseUiKit/NBaseUiKit_inc.pri)
```

**具体的路径请按照你的项目情况进行修改**

## 1. 如何运行测试例子

打开工程文件`NBaseUiKit.pro`,然后在QtCreator中勾掉show build选项,编译运行即可,生成的文件在`bin`文件中;

## 2. 测试用例

* 可移动窗体测试用例

```c
    // 可以移动窗体的测试用例
    NBaseMoveableWidget test_case_001;
    QLabel test_case_001_label(&test_case_001);
    test_case_001_label.setText("可以移动窗体的测试用例");
    test_case_001.setGeometry(0,0,400,400);
    test_case_001.show();
```

* 渐入渐出窗体测试用例

```c
	// 渐入渐出窗体测试用例
    NBaseFadeWidget test_case_002;
    QLabel test_case_002_label(&test_case_002);
    test_case_002_label.setText("渐入渐出窗体测试用例");
    test_case_002.setGeometry(400,0,400,400);
    test_case_002.beginFadeShow(5);
```

* // 迷你窗体测试用例

```c
    // 迷你窗体测试用例
    NBaseMiniAppWidget test_case_003;
    test_case_003.setPixmap(QPixmap(":miniImage"));
    test_case_003.show();
```

* 阴影窗体测试用例

```c
    // 阴影窗体测试用例
    NBaseShadowWidget test_case_004;
    test_case_004.setGeometry(0,400,400,400);
    test_case_004.show();
```

* 弹出窗体测试用例

```c
    // 弹出窗体测试用例
    NBasePopWidget test_case_005;
    QLabel test_case_005_label(&test_case_005);
    test_case_005_label.setText("弹出窗体测试用例");
    test_case_005.setFixedHeight(400);
    test_case_005.setFixedWidth(400);
    test_case_005.showPopDialog();
```

* snowLabel测试用例

```c
	// snowLabel测试用例
    NBaseSnowLabel test_case_006;
    test_case_006.setText("我是测试数据");
    test_case_006.setFont(QFont("微软雅黑", 12, QFont::Bold));
    test_case_006.setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    test_case_006.show();
```

* 圆周运动窗体测试用例

```c
	// 圆周运动窗体测试用例
    NBaseCircleAnimationWidget test_case_007;
    test_case_007.setCircleInfo(":miniImage",10);
    test_case_007.show();
    test_case_007.startAnimation();
```

* LED窗体测试用例(跑马灯效果)

```c
    NBaseLEDWidget test_case_008;
    test_case_008.setGeometry(0,230,300,40);
    test_case_008.setText("我是跑马灯LED效果。");
    test_case_008.setTimer(500);
    test_case_008.startEffect(true);
    test_case_008.show();
```

* LED窗体测试用例(闪光灯效果)

```c
    NBaseLEDWidget test_case_009;
    test_case_009.setGeometry(330,230,300,40);
    test_case_009.setText("我是闪光灯LED效果。");
    test_case_009.setTimer(500);
    test_case_009.setEffect(NBaseLEDWidget::intermittent);
    test_case_009.startEffect(true);
    test_case_009.show();
```

* 跑马灯label测试用例(像素级别)

```c
    NBaseMarqueeLabel test_case_010;
    test_case_010.setText("我是跑马灯测试数据");
    test_case_010.setFont(QFont("Fixed", 20, QFont::Bold));
    test_case_010.setDirection(NBaseMarqueeLabel::RightToLeft);
    test_case_010.setInterval(50);
    test_case_010.start();
    test_case_010.show();
```

* QR测试用例

```c
	NBaseQREncodeWidget test_case_011;
    test_case_011.resize(300,300);
    test_case_011.setQrLogo(":miniImage");
    test_case_011.show();
```

* 圆形进度条测试

```
    // 圆形进度条测试用例(甜甜圈样式)
    QPalette p1;
    p1.setBrush(QPalette::AlternateBase, Qt::darkCyan);
    p1.setColor(QPalette::Text, Qt::yellow);
    NBaseRoundProgressBar test_case_012;
    test_case_012.setOutlinePenWidth(2);
    test_case_012.setPalette(p1);
    test_case_012.setNullPosition(NBaseRoundProgressBar::PositionLeft);
    test_case_012.setDecimals(0);
    test_case_012.setFixedSize(200,200);
    test_case_012.show();

    // 圆形进度条测试用例(线性样式)
    NBaseRoundProgressBar test_case_013;
    test_case_013.setOutlinePenWidth(8);
    test_case_013.setDataPenWidth(10);
    test_case_013.setBarStyle(NBaseRoundProgressBar::StyleLine);
    test_case_013.setDecimals(0);
    test_case_013.setFixedSize(200,200);
    test_case_013.show();
```

* toastr 提示测试

```
	NBaseToastr * test_case_014 = new NBaseToastr(this, "我是刀刀亮测试数据");
    test_case_014->toastr();
```

* 阴影文字label 测试

```
    NBaseShadowLabel * test_case_015 = new NBaseShadowLabel(" 我是刀刀亮测试数据 ");
    test_case_015->setFont(QFont("Fixed", 25, QFont::Bold));
    test_case_015->setFixedSize(400, 50);
    test_case_015->show();
```

* 等待框 测试

```
    // 等待框 测试用例
    NBaseWaitDialog * test_case_016 = new NBaseWaitDialog(this);
    test_case_016->showWaitDialog();
	//test_case_016->closeWaitDialog();
```

* 纵向触屏列表 测试用例

```
    // 触屏列表 测试用例
    NTouchListWidget *test_case_18 = new NTouchListWidget();
    test_case_18->setFixedSize(200,500);
    test_case_18->show();

    // 插入测试数据
    for(int index = 0;index != 200;index++) test_case_18->addItem(QString("测试项目:%1").arg(index));
```

* 翻转页面 测试用例

```
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
```

* 横向触屏 测试用例

```
    // 触屏列表 测试用例
    NTouchListWidget *test_case_20 = new NTouchListWidget();
    test_case_20->setFixedSize(500,200);
    test_case_20->setFlow(QListWidget::LeftToRight);
    test_case_20->show();

    // 插入测试数据
    for(int index = 0;index != 200;index++) test_case_20->addItem(QString("测试项目:%1").arg(index));
```

* 验证码 测试用例

```
    // 验证码 测试用例
    NBaseCaptcha test_case_21(0,200,50,6);
    QLabel *test_case_21_w = new QLabel;
    test_case_21_w->setPixmap(test_case_21.generateOneCaptcha());
    test_case_21_w->move(x()+width()/2, y()+height()/2);
    test_case_21_w->show();
```

* 图片截取 测试用例

```
    // 图片截取的测试用例
    NBaseImageCropper *test_case_22 = new NBaseImageCropper(nullptr,true,true);
    test_case_22->setImage(":testImage");
    test_case_22->setSize(400,600);
    test_case_22->show();
```

* switch按钮 测试用例

```
    // switch按钮 测试用例
    NBaseSwitchButton *test_case_23 = new NBaseSwitchButton;
    test_case_23->show();
```

* 卷轴 测试用例

```
    // 卷轴widget 测试用例
    NBaseReelWidget *test_case_24 = new NBaseReelWidget;
    test_case_24->setOriPos(QPoint(x()+width()/2-250, y()+height()/2-150));
    test_case_24->setOriSize(QSize(500,300));
    test_case_24->showExpan();
```

* 头像 测试用例

```
    // 头像编辑 测试用例
    NBaseLogoWidget *test_case_25 = new NBaseLogoWidget;
    test_case_25->show();
```

* 点击波按钮 测试用例

```
    // 点击波按钮 测试用例
    NBaseClickWave *test_case_26 = new NBaseClickWave;
    test_case_26->setClickColor(QColor(225,189,162));
    test_case_26->setFixedSize(200,80);
    test_case_26->show();
```

## 3. 组件路线图

* ~~可移动widget;~~
* ~~渐入渐出widget;~~
* ~~迷你工具widget;~~
* ~~阴影widget;~~
* ~~弹出式widget;~~
* ~~圆周抖动式widget~~
* ~~LED效果widget;~~
* ~~反转效果stackwidget~~
* ~~二维码生成widget~~
* ~~圆形进度条;~~
* ~~toastr提示组件;~~
* ~~阴影文字label组件;~~
* ~~等待框组件;~~
* ~~翻转效果的widget;~~
* ~~触屏效果的list;~~
* ~~验证码widget;~~
* ~~图片截取widget;~~
* ~~switch按钮;~~
* ~~卷轴效果widget;~~
* ~~双态按钮;~~
* ~~头像生成按钮;~~
* ~~点击波按钮~~

## 4. changelog

* V 1.0.1.0 完成常用的加解密的封装;
* V 1.0.2.0 增加LED效果的组件;
* V 1.0.3.0 增加跑马灯效果的组件;
* V 1.0.4.0 增加二维码效果组件;
* V 1.0.5.0 增加圆形进度条组件;
* V 1.0.6.0 增加toastr提示组件;
* V 1.0.7.0 增加阴影文字label组件;
* V 1.0.8.0 增加等待框组件;
* V 1.0.9.0 增加触屏效果的list;
* V 1.0.10.0 增加翻转效果的组件;
* V 1.0.11.0 增加触屏效果的listview 和 Listwidget;
* V 1.0.12.0 增加验证码widget和图片截取widget;
* V 1.0.13.0 增加switch按钮;
* V 1.0.14.0 增加卷轴widget;
* V 1.0.15.0 增加头像编辑控件，同时增加了图片截取的控件的比例按钮;
* V 1.0.16.0 增加了点击波按钮;
* V 1.0.17.0 增加了倒计时波widget;

## 5. 若是有啥不对的地方随时联系我

QQ: 88341189

Email: daodaoliang@yeah.net



