#include "nbaselogowidget.h"
#include <QDebug>
#include <QFileDialog>
#include <QCoreApplication>
#include "nbasetoastr.h"

NBaseLogoWidget::NBaseLogoWidget(QWidget *parent) : QLabel(parent)
{
    isProcessing = false;
    imageCrop = new NBaseImageCropper(nullptr, true, true);
    imageCrop->setSize(400,400);
    setFixedSize(100,100);
    connect(imageCrop,SIGNAL(singalCropImage(QPixmap)),this,SLOT(cropImage(QPixmap)));
    setLogoPath(QCoreApplication::applicationDirPath() + "/default.jpg");
}

void NBaseLogoWidget::editLogo()
{
    isProcessing = true;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("选择头像文件"),
                                                    "./",
                                                    "Images (*.png *.xpm *.jpg)");
    if(QFile::exists(fileName)){
        imageCrop->setImage(fileName);
        imageCrop->show();
    }
    isProcessing = false;
}

void NBaseLogoWidget::cropImage(QPixmap paramValue)
{
    QString tempPath = QCoreApplication::applicationDirPath() + "/logo.jpg";
    QString defaultPath = QCoreApplication::applicationDirPath() + "/default.jpg";
    paramValue.save(tempPath);
    if(QFile::exists(tempPath)){
        setStyleSheet(tr("border-image: url(%1);").arg(tempPath));
        setLogoPath(tempPath);
    } else {
        setStyleSheet(tr("border-image: url(%1);").arg(defaultPath));
        setLogoPath(defaultPath);
    }
    qDebug()<<getLogoPath();
    imageCrop->hide();
}

void NBaseLogoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(!isProcessing){
        editLogo();
    }
    QLabel::mouseDoubleClickEvent(event);
}

QString NBaseLogoWidget::getLogoPath() const
{
    return logoPath;
}

void NBaseLogoWidget::setLogoPath(const QString &value)
{
    logoPath = value;
}
