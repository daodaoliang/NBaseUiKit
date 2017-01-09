#ifndef NBASECAPTCHA_H
#define NBASECAPTCHA_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月31日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include "nbaseuikit_global.h"

class NBaseCaptcha_p;
/**
 * @brief The NBaseCaptcha class 验证码窗体
 */
class NBASEUIKITSHARED_EXPORT NBaseCaptcha : public QWidget
{
    Q_OBJECT
public:
    explicit NBaseCaptcha(QWidget *parent = nullptr, quint16 width = 180, quint16 height = 50, quint8 count = 6);

    /**
     * @brief generateOneCaptcha 生成一个验证码
     * @return
     */
    QPixmap generateOneCaptcha();

    /**
     * @brief getCurrentCaptcha 获取当前验证码串
     * @return
     */
    QString getCurrentCaptcha() const;

    /**
     * @brief setCurrentCaptcha 设置当前验证码
     * @param value
     */
    void setCurrentCaptcha(const QString &value);

    /**
     * @brief getCanvasWidth 获取画布的宽度
     * @return
     */
    quint16 getCanvasWidth() const;

    /**
     * @brief setCanvasWidth 设置画布的宽度
     * @param value
     */
    void setCanvasWidth(const quint16 &value);

    /**
     * @brief getCanvasHeight 获取画布的高度
     * @return
     */
    quint16 getCanvasHeight() const;

    /**
     * @brief setCanvasHeight 设置画布的高度
     * @param value
     */
    void setCanvasHeight(const quint16 &value);

    /**
     * @brief getCaptchaCount 获取验证码的数量
     * @return
     */
    quint8 getCaptchaSize() const;

    /**
     * @brief setCaptchaCount 设置验证码的数量
     * @param value
     */
    void setCaptchaSize(const quint8 &value);

private:
    /**
     * @brief captchaInstance 验证码操作类
     */
    NBaseCaptcha_p *captchaInstance;

    /**
     * @brief currentCaptcha 当前验证码串
     */
    QString currentCaptcha;

    /**
     * @brief canvasWidth 画布的宽度
     */
    quint16 canvasWidth;

    /**
     * @brief canvasHeight 画布的高度
     */
    quint16 canvasHeight;

    /**
     * @brief captchaCount 验证码的高度
     */
    quint8 captchaSize;
};

#endif // NBASECAPTCHA_H
