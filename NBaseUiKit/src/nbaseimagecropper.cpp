#include "nbaseimagecropper.h"
#include "imagecropper.h"
#include <QPixmap>
#include <QDebug>
#include <QGridLayout>
#include <QPushButton>

/**
 * @brief imageInstance 图片截取
 */

class NBaseImageCropper_p{
public:
    NBaseImageCropper_p();

public:
    ImageCropper *imageInstance;
};

NBaseImageCropper::NBaseImageCropper(QWidget *parent, bool isCropBtn, bool isToolBtn)
    :QWidget(parent)
{
    imageInstance = new NBaseImageCropper_p();
    imageInstance->imageInstance = new ImageCropper;
    // 风格设置
    setCropStyle(QColor(98,92,82), QColor(231,105,63));
    // 窗体属性
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowModality(Qt::WindowModal);
    // 标识设置
    shortCut = nullptr;
    showConfirmBtn = isCropBtn;
    showToolBtn = isToolBtn;
    isFTFixed = false;
    isOOFixed = false;
    // 工具布局
    QGridLayout *tempLayout = new QGridLayout;
    // 主区域
    tempLayout->addWidget(imageInstance->imageInstance,1,1,5,5);
    // 截取并上传按钮
    if(showConfirmBtn) {
        cropBtn = new QPushButton(tr(""),this);
        cropBtn->setProperty("cropBtn",true);
        cropBtn->setAttribute(Qt::WA_TranslucentBackground);
        cropBtn->setStyleSheet(tr("QPushButton[cropBtn=\"true\"]{border-image:url(:upload)}"
                                  "QPushButton[cropBtn=\"true\"]:hover{border-image:url(:upload_h)}"
                                  "QPushButton[cropBtn=\"true\"]:pressed{border-image:url(:upload_p)}"));
        cropBtn->setFixedSize(80,80);
        cropBtn->setToolTip(tr("裁剪并上传图像"));
        tempLayout->addWidget(cropBtn,6,3);
        connect(cropBtn,SIGNAL(clicked(bool)), this,SLOT(cropImage()));
    }
    // 右边栏工具按钮
    if(showToolBtn){
        // 4:3 比例按钮
        ftsBtn = new QPushButton(tr(""),this);
        ftsBtn->setProperty("ftsBtn",true);
        ftsBtn->setAttribute(Qt::WA_TranslucentBackground);
        ftsBtn->setStyleSheet(tr("QPushButton[ftsBtn=\"true\"]{border-image:url(:image_bg);color:#e8853b;}"
                                 "QPushButton[ftsBtn=\"true\"]:hover{border-image:url(:bright);color:#e8853b;}"));
        ftsBtn->setText(tr("4:3"));
        ftsBtn->setFont(QFont("微软雅黑",12,QFont::Bold));
        ftsBtn->setFixedSize(50,50);
        ftsBtn->setToolTip(tr("固定4:3的比例"));
        tempLayout->addWidget(ftsBtn,2,6);
        connect(ftsBtn,SIGNAL(clicked(bool)), this,SLOT(setFTProportion()));

        // 1:1 比例按钮
        ooBtn = new QPushButton(tr(""),this);
        ooBtn->setProperty("ooBtn",true);
        ooBtn->setAttribute(Qt::WA_TranslucentBackground);
        ooBtn->setStyleSheet(tr("QPushButton[ooBtn=\"true\"]{border-image:url(:image_bg);color:#e8853b;}"
                                 "QPushButton[ooBtn=\"true\"]:hover{border-image:url(:bright);color:#e8853b;}"));
        ooBtn->setText(tr("1:1"));
        ooBtn->setFont(QFont("微软雅黑",12,QFont::Bold));
        ooBtn->setFixedSize(50,50);
        ooBtn->setToolTip(tr("固定1:1的比例"));
        tempLayout->addWidget(ooBtn,3,6);
        connect(ooBtn,SIGNAL(clicked(bool)), this,SLOT(setOOProportion()));
    }
    // 布局设置
    tempLayout->setSpacing(0);
    tempLayout->setMargin(0);
    setLayout(tempLayout);
}

void NBaseImageCropper::setProportion(const quint8 &paramWidth, const quint8 &paramHeight)
{
    isFTFixed = true;
    imageInstance->imageInstance->setProportionFixed(true);
    imageInstance->imageInstance->setProportion(QSize(paramWidth, paramHeight));
}

void NBaseImageCropper::setImage(const QString imagePath)
{
    imageInstance->imageInstance->setImage(QPixmap(imagePath));
}

void NBaseImageCropper::setCropStyle(const QColor &bgColor, const QColor &borderColor)
{
    imageInstance->imageInstance->setBackgroundColor(bgColor);
    imageInstance->imageInstance->setCroppingRectBorderColor(borderColor);
}

void NBaseImageCropper::setSize(const quint16 &width, const quint16 &height)
{
    imageInstance->imageInstance->resize(width, height);
}

const QPixmap NBaseImageCropper::cropImage()
{
    setCurrentPixMap(imageInstance->imageInstance->cropImage());
    emit singalCropImage(getCurrentPixMap());
    return getCurrentPixMap();
}

QPixmap NBaseImageCropper::getCurrentPixMap() const
{
    return currentPixMap;
}

void NBaseImageCropper::setCurrentPixMap(const QPixmap &value)
{
    currentPixMap = value;
}

void NBaseImageCropper::setFTProportion()
{
    if(!isFTFixed){
        ftsBtn->setStyleSheet(tr("QPushButton[ftsBtn=\"true\"]{border-image:url(:lock_t);color:#e8853b;}"
                                 "QPushButton[ftsBtn=\"true\"]:hover{border-image:url(:bright);color:#e8853b;}"));
        setProportion(4,3);
        isFTFixed = true;
    } else {
        setNoProportion();
        isFTFixed = false;
    }
}

void NBaseImageCropper::setOOProportion()
{
    if(!isOOFixed){
        ooBtn->setStyleSheet(tr("QPushButton[ooBtn=\"true\"]{border-image:url(:lock_t);color:#e8853b;}"
                                 "QPushButton[ooBtn=\"true\"]:hover{border-image:url(:bright);color:#e8853b;}"));
        setProportion(1,1);
        isOOFixed = true;
    } else {
        setNoProportion();
        isOOFixed = false;
    }
}

void NBaseImageCropper::setNoProportion()
{
    ftsBtn->setStyleSheet(tr("QPushButton[ftsBtn=\"true\"]{border-image:url(:image_bg);color:#e8853b;}"
                             "QPushButton[ftsBtn=\"true\"]:hover{border-image:url(:bright);color:#e8853b;}"));
    ooBtn->setStyleSheet(tr("QPushButton[ooBtn=\"true\"]{border-image:url(:image_bg);color:#e8853b;}"
                             "QPushButton[ooBtn=\"true\"]:hover{border-image:url(:bright);color:#e8853b;}"));
    imageInstance->imageInstance->setProportionFixed(false);
}

void NBaseImageCropper::showEvent(QShowEvent *event)
{
    if(showConfirmBtn){
        cropBtn->show();
    }
    QWidget::showEvent(event);
}

NBaseImageCropper_p::NBaseImageCropper_p()
{
    imageInstance = NULL;
}
