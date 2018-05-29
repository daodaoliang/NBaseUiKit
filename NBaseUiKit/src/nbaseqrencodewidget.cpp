#include "nbaseqrencodewidget.h"

NBaseQREncodeWidget::NBaseQREncodeWidget(QWidget *parent) : QWidget(parent)
{
    qrMargin =5;
    qrSize = QSize(128,128);
    qrForeground = QColor("#0E4963");
    qrBackground = QColor("white");
    qrCasesen = true;
    qrMode = MODE_8;
    qrLevel = LEVEL_Q;
    qrPercent = 0.23;
    qrLogo="daodaoliang.github.io";
    qrData = "daodaoliang.github.io";
    qrFilePath = "";
    resize(qrSize);
}

QString NBaseQREncodeWidget::getQrData() const
{
    return qrData;
}

void NBaseQREncodeWidget::setQrData(const QString &value)
{
    if(qrData != value){
        qrData = value;
        emit qrDataChanged(qrData);
        update();
    }
}

QString NBaseQREncodeWidget::getQrLogo() const
{
    return qrLogo;
}

void NBaseQREncodeWidget::setQrLogo(const QString &value)
{
    if(qrLogo != value){
        qrLogo = value;
        emit qrLogoChanged(qrLogo);
        update();
    }
}

QSize NBaseQREncodeWidget::getQrSize() const
{
    return qrSize;
}

void NBaseQREncodeWidget::setQrSize(const QSize &value)
{
    if(qrSize != value){
        qrSize = value;
        emit qrSizeChanged(qrSize);
        update();
    }
}

NBaseQREncodeWidget::QR_MODE NBaseQREncodeWidget::getQrMode() const
{
    return qrMode;
}

void NBaseQREncodeWidget::setQrMode(const QR_MODE &value)
{
    if(qrMode != value){
        qrMode = value;
        emit qrModeChanged(qrMode);
        update();
    }
}

NBaseQREncodeWidget::QR_LEVEL NBaseQREncodeWidget::getQrLevel() const
{
    return qrLevel;
}

void NBaseQREncodeWidget::setQrLevel(const QR_LEVEL &value)
{
    if(qrLevel != value){
        qrLevel = value;
        emit qrLevelChanged(qrLevel);
        update();
    }
}

bool NBaseQREncodeWidget::getQrCasesen() const
{
    return qrCasesen;
}

void NBaseQREncodeWidget::setQrCasesen(bool value)
{
    if(qrCasesen != value){
        qrCasesen = value;
        emit qrCasesenChanged(qrCasesen);
        update();
    }
}

int NBaseQREncodeWidget::getQrMargin() const
{
    return qrMargin;
}

void NBaseQREncodeWidget::setQrMargin(int value)
{
    if(qrMargin != value){
        qrMargin = value;
        emit qrMarginChanged(qrMargin);
        update();
    }
}

qreal NBaseQREncodeWidget::getQrPercent() const
{
    return qrPercent;
}

void NBaseQREncodeWidget::setQrPercent(const qreal &value)
{
    if(qrPercent != value){
        qrPercent = value;
        emit qrPercentChanged(qrPercent);
        update();
    }
}

QColor NBaseQREncodeWidget::getQrForeground() const
{
    return qrForeground;
}

void NBaseQREncodeWidget::setQrForeground(const QColor &value)
{
    if(qrForeground != value){
        qrForeground = value;
        emit qrForegroundChanged(qrForeground);
        update();
    }
}

QColor NBaseQREncodeWidget::getQrBackground() const
{
    return qrBackground;
}

void NBaseQREncodeWidget::setQrBackground(const QColor &value)
{
    if(qrBackground != value){
        qrBackground = value;
        emit qrBackgroundChanged(qrBackground);
        update();
    }
}

QString NBaseQREncodeWidget::getQrFilePath() const
{
    return qrFilePath;
}

void NBaseQREncodeWidget::setQrFilePath(const QString &value)
{
    qrFilePath = value;
    if(!qrFilePath.isEmpty()){
        saveCurViewToFile();
    }
}

void NBaseQREncodeWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    QRcode *qrcode = QRcode_encodeString(qrData.toUtf8() , 7, (QRecLevel)qrLevel, (QRencodeMode)qrMode, qrCasesen ? 1 : 0);
    QRect rect(0,0,qrSize.width(),qrSize.height());
    if(0 != qrcode) {
        unsigned char *point = qrcode->data;
        painter.setPen(Qt::NoPen);
        painter.setBrush(this->qrBackground);
        painter.drawRect(rect);
        double scale = (rect.width () - 2.0 * qrMargin) / qrcode->width;
        painter.setBrush(this->qrForeground);
        for (int y = 0; y < qrcode->width; y ++) {
            for (int x = 0; x < qrcode->width; x ++) {
                if (*point & 1) {
                    QRectF r(qrMargin + x * scale, qrMargin + y * scale, scale, scale);
                    painter.drawRects(&r, 1);
                }
                point ++;
            }
        }
        point = NULL;
        QRcode_free(qrcode);
        painter.setBrush(QColor("#00ffffff"));
        double icon_width = (rect.width () - 2.0 * qrMargin) * qrPercent;
        double icon_height = icon_width;
        double wrap_x = (rect.width () - icon_width) / 2.0;
        double wrap_y = (rect.width () - icon_height) / 2.0;
        QRectF wrap(wrap_x - 5, wrap_y - 5, icon_width + 10, icon_height + 10);
        painter.drawRoundRect(wrap, 50, 50);
        if(qrLogo.isEmpty() || qrLogo == "daodaoliang.github.io"){
            painter.save();
            QPen pen;
            pen.setColor(Qt::red);
            painter.setFont(QFont("微软雅黑",14));
            painter.setPen(pen);
            painter.drawText(wrap,"daodaoliang.github.io");
            painter.restore();
        }else{
            if(qrLogo.startsWith("qrc")){
                qrLogo = qrLogo.replace("qrc","");
            }
            QPixmap image(qrLogo);
            QRectF target(wrap_x, wrap_y, icon_width, icon_height);
            QRectF source(0, 0, image.width (), image.height ());
            painter.drawPixmap (target, image, source);
        }
    }
}

void NBaseQREncodeWidget::resizeEvent(QResizeEvent *e)
{
    if(e->size().isValid()){
        int w = this->size().width();
        int h = this->size().height();
        if(w>h){
            setQrSize(QSize(h,h));
        }else{
            setQrSize(QSize(w,w));
        }
    }
}

void NBaseQREncodeWidget::saveCurViewToFile()
{
    QString str = qrFilePath;
    if(!str.endsWith(".png")){
        str.append(".png");
    }
    QFile file(str);
    if (!file.open(QIODevice::WriteOnly)){
        file.close();
        return;
    }
    QRect rect(0,0,qrSize.width(),qrSize.height());
    QPixmap pixmap(rect.size());
    this->render(&pixmap, QPoint(), QRegion(rect));
    pixmap.save(str);
}
