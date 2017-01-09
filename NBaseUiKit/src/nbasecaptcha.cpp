#include "nbasecaptcha.h"
#include <QTime>
#include <QBrush>
#include <QFontMetrics>
#include <QFont>
#include <QPainter>
#include <QBrush>
#include <QBuffer>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

/**
 * @brief The NBaseCaptcha_p class 验证码操作类
 */
class NBaseCaptcha_p {
public:
    /**
     * @brief NBaseCaptcha_p 构造函数
     * @param parent
     */
    explicit NBaseCaptcha_p(QObject *parent = 0);

public:
    /**
     * @brief generateLetter 获取随机字符串
     * @param paramCount 字符串个数
     * @return
     */
    QString generateLetter(quint16 paramCount);

    /**
     * @brief generateRandom 获取指定范围的随机数
     * @param paramLow 范围的最小数字
     * @param paramHigh 范围的最大数字
     * @return
     */
    qint16 generateRandom(qint16 paramLow, qint16 paramHigh);

    /**
     * @brief generateBrush 获取画刷
     * @param paramText 待画的文字
     * @param paramFont 文字的字体
     * @return 画刷
     */
    QBrush generateBrush(QString paramText, QFont paramFont);

    /**
     * @brief generateRandomColor 获取随机(字体)颜色
     * @return
     */
    QColor generateRandomColor();

    /**
     * @brief generateRandomBgColor 获取随机(背景)颜色
     * @return
     */
    QColor generateRandomBgColor();

    /**
     * @brief sleepNow 休息一会
     * @param paramMilsecond
     */
    void sleepNow(quint32 paramMilsecond);

};

NBaseCaptcha::NBaseCaptcha(QWidget *parent, quint16 width, quint16 height, quint8 count)
    : QWidget(parent)
{
    captchaInstance = new NBaseCaptcha_p(this);
    canvasWidth = width;
    canvasHeight = height;
    captchaSize = count;
}

QPixmap NBaseCaptcha::generateOneCaptcha()
{
    // 验证码个数
    quint8 captchaCount = captchaSize;
    // 生成画布
    int canvas_w = canvasWidth;
    int canvas_h = canvasHeight;
    QImage image(QSize(canvas_w, canvas_h), QImage::Format_RGB32);
    image.fill(captchaInstance->generateRandomBgColor());

    // 噪音线
    QPainter painter(&image);
    for(int i=0; i<10; i++)
    {
        QPen penHText(captchaInstance->generateRandomColor(),2);
        painter.setPen(penHText);
        painter.drawLine(captchaInstance->generateRandom(0,canvas_w),
                         captchaInstance->generateRandom(0,canvas_h),
                         captchaInstance->generateRandom(-canvas_w,canvas_w),
                         captchaInstance->generateRandom(-canvas_h,canvas_h));
        captchaInstance->sleepNow(5);
    }
    painter.end();
    // 验证码
    int xStart = captchaInstance->generateRandom(canvas_w/captchaCount/3*2,canvas_w/captchaCount);
    int yStart = captchaInstance->generateRandom(canvas_h/2,canvas_h/5*4);
    int fontSize = captchaInstance->generateRandom(canvas_h/5*2,canvas_h/5*3);
    int rotateVar = 0;
    QString captchaString;
    for(int i=0; i<captchaCount; i++)
    {
        QPainter painter(&image);
        // 字符颜色
        QPen penC(captchaInstance->generateRandomColor(),2);
        painter.setPen(penC);
        // 字符值
        QString letter = captchaInstance->generateLetter(1);
        captchaString += letter;
        // 字符字体
        painter.setFont(QFont("微软雅黑", fontSize, QFont::Bold));
        // 字体旋转值
        rotateVar = captchaInstance->generateRandom(-10,10);
        painter.rotate(rotateVar);
        // 画出字符
        painter.drawText(xStart,yStart,letter);
        // 休息一会
        captchaInstance->sleepNow(5);
        // 重新计算开始值
        xStart += captchaInstance->generateRandom(canvas_w/captchaCount/3*2, canvas_w/captchaCount);
        yStart = captchaInstance->generateRandom(canvas_h/2,canvas_h/5*4);
        // 偏移量的反方向
        painter.rotate(-rotateVar);
        painter.end();
    }
    // 验证码转小写
    captchaString = captchaString.toLower();
    // 保存验证码
    setCurrentCaptcha(captchaString);
    // 返回图片
    return QPixmap::fromImage(image);
}

QString NBaseCaptcha::getCurrentCaptcha() const
{
    return currentCaptcha;
}

void NBaseCaptcha::setCurrentCaptcha(const QString &value)
{
    currentCaptcha = value;
}

quint16 NBaseCaptcha::getCanvasWidth() const
{
    return canvasWidth;
}

void NBaseCaptcha::setCanvasWidth(const quint16 &value)
{
    canvasWidth = value;
}

quint16 NBaseCaptcha::getCanvasHeight() const
{
    return canvasHeight;
}

void NBaseCaptcha::setCanvasHeight(const quint16 &value)
{
    canvasHeight = value;
}

quint8 NBaseCaptcha::getCaptchaSize() const
{
    return captchaSize;
}

void NBaseCaptcha::setCaptchaSize(const quint8 &value)
{
    captchaSize = value;
}

NBaseCaptcha_p::NBaseCaptcha_p(QObject *parent)
{
    Q_UNUSED(parent);
}

QString NBaseCaptcha_p::generateLetter(quint16 paramCount)
{
    QString randKey;
    std::string allowedChars = "abcdfhikmnstuvwxyzABCDEFGHJKLMNPRSTUVWXYZ01245689";
    int randomIndex;
    std::string outputString = "";
    for (uint i = 0; i < paramCount; ++i) {
        randomIndex = rand() % allowedChars.length();
        outputString += allowedChars[randomIndex];
    }
    std::string ss11 = outputString;
    char *ss = new char[ss11.length() + 1];
    strcpy(ss, ss11.c_str());
    randKey = ss;
    return randKey;
}

qint16 NBaseCaptcha_p::generateRandom(qint16 paramLow, qint16 paramHigh)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    sleepNow(2);
    if (paramLow > 0){
        return paramLow + rand() % (paramHigh - paramLow);
    } else {
        return paramLow + rand() % (abs(paramLow) + paramHigh);
    }
}

QBrush NBaseCaptcha_p::generateBrush(QString paramText, QFont paramFont)
{
    QFontMetrics font_metrics(paramFont);
    QPixmap pixmap(font_metrics.boundingRect(paramText).size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setFont(paramFont);
    painter.drawText(pixmap.rect(),paramText);
    painter.end();
    return QBrush(pixmap);
}

QColor NBaseCaptcha_p::generateRandomColor()
{
    QVector<QColor> avaliableColor;
    // 灯草灰
    avaliableColor.push_back(QColor(54,53,50));
    // 草黄
    avaliableColor.push_back(QColor(219,206,84));
    // 湛蓝
    avaliableColor.push_back(QColor(27,84,242));
    // 紫薇花
    avaliableColor.push_back(QColor(238,165,209));
    // 洋红
    avaliableColor.push_back(QColor(220,20,60));
    // 紫藤灰
    avaliableColor.push_back(QColor(133,126,149));
    // 鹦鹉绿
    avaliableColor.push_back(QColor(0,142,89));
    // 柠檬黄
    avaliableColor.push_back(QColor(233,219,57));
    // 桔黄
    avaliableColor.push_back(QColor(232,133,59));
    // 柏坊灰蓝
    avaliableColor.push_back(QColor(78,24,146));
    return avaliableColor[generateRandom(1, avaliableColor.size()) - 1];
}

QColor NBaseCaptcha_p::generateRandomBgColor()
{
    QVector<QColor> avaliableColor;
    // 鸭蛋青
    avaliableColor.push_back(QColor(209,227,219));
    // 米色
    avaliableColor.push_back(QColor(245,245,220));
    // 胡粉
    avaliableColor.push_back(QColor(235,232,219));
    // 米灰
    avaliableColor.push_back(QColor(197,191,173));
    // 甘石粉
    avaliableColor.push_back(QColor(234,220,214));
    // 雪色
    avaliableColor.push_back(QColor(255,250,25));
    // 水黄
    avaliableColor.push_back(QColor(190,210,182));
    // 春蓝
    avaliableColor.push_back(QColor(123,161,168));
    // 浅藤紫
    avaliableColor.push_back(QColor(186,195,203));
    // 浅血牙
    avaliableColor.push_back(QColor(234,205,209));
    return avaliableColor[generateRandom(1, avaliableColor.size()) - 1];
}

void NBaseCaptcha_p::sleepNow(quint32 paramMilsecond)
{
    QEventLoop eventloop;
    QTimer::singleShot(paramMilsecond, &eventloop, SLOT(quit()));
    eventloop.exec();
}
