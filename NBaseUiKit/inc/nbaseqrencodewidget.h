#ifndef NBASEQRENCODEWIDGET_H
#define NBASEQRENCODEWIDGET_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月15日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QResizeEvent>
#include <QPainter>
#include <QSize>
#include <QWidget>
#include <QPaintEvent>
#include "../3rdparty/qrencode/qrencode/qrencode.h"
#include "nbaseuikit_global.h"

/**
 * @brief The NBaseQREncodeWidget class 二维码生成组件
 */
class NBASEUIKITSHARED_EXPORT NBaseQREncodeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NBaseQREncodeWidget(QWidget *parent = 0);

public:
    /**
     * @brief The QR_MODE enum 设置二维码的编码模式
     */
    enum QR_MODE {
        MODE_NUL = QR_MODE_NUL,
        MODE_NUM = QR_MODE_NUM,
        MODE_AN = QR_MODE_AN,
        MODE_8 = QR_MODE_8,
        MODE_KANJI = QR_MODE_KANJI,
        MODE_STRUCTURE = QR_MODE_STRUCTURE,
        MODE_ECI = QR_MODE_ECI,
        MODE_FNC1FIRST = QR_MODE_FNC1FIRST,
        MODE_FNC1SECOND = QR_MODE_FNC1SECOND
    };

    /**
     * @brief The QR_LEVEL enum 设置二维码编码的识别质量的级别
     */
    enum QR_LEVEL {
        LEVEL_L = QR_ECLEVEL_L,
        LEVEL_M = QR_ECLEVEL_M,
        LEVEL_Q = QR_ECLEVEL_Q,
        LEVEL_H = QR_ECLEVEL_H
    };

public:
    /**
     * @brief getQrData 获取原始数据
     * @return
     */
    QString getQrData() const;

    /**
     * @brief setQrData 设置原始数据
     * @param value
     */
    void setQrData(const QString &value);

    /**
     * @brief getQrLogo 获取中间图标数据
     * @return
     */
    QString getQrLogo() const;

    /**
     * @brief setQrLogo 设置中间图标
     * @param value
     */
    void setQrLogo(const QString &value);

    /**
     * @brief getQrSize 获取二维码尺寸
     * @return
     */
    QSize getQrSize() const;

    /**
     * @brief setQrSize 设置二维码尺寸
     * @param value
     */
    void setQrSize(const QSize &value);

    /**
     * @brief getQrMode 获取二维码模式
     * @return
     */
    QR_MODE getQrMode() const;

    /**
     * @brief setQrMode 设置二维码模式
     * @param value
     */
    void setQrMode(const QR_MODE &value);

    /**
     * @brief getQrLevel 获取等级
     * @return
     */
    QR_LEVEL getQrLevel() const;

    /**
     * @brief setQrLevel 设置等级
     * @param value
     */
    void setQrLevel(const QR_LEVEL &value);

    bool getQrCasesen() const;
    void setQrCasesen(bool value);

    /**
     * @brief getQrMargin 获取边框
     * @return
     */
    int getQrMargin() const;

    /**
     * @brief setQrMargin 设置边框
     * @param value
     */
    void setQrMargin(int value);

    /**
     * @brief getQrPercent 获取Percent
     * @return
     */
    qreal getQrPercent() const;

    /**
     * @brief setQrPercent 设置Percent
     * @param value
     */
    void setQrPercent(const qreal &value);

    /**
     * @brief getQrForeground 获取前景色
     * @return
     */
    QColor getQrForeground() const;

    /**
     * @brief setQrForeground 设置前景色
     * @param value
     */
    void setQrForeground(const QColor &value);

    /**
     * @brief getQrBackground 获取背景色
     * @return
     */
    QColor getQrBackground() const;

    /**
     * @brief setQrBackground设置背景色
     * @param value
     */
    void setQrBackground(const QColor &value);

    /**
     * @brief getQrFilePath 获取文件路径
     * @return
     */
    QString getQrFilePath() const;

    /**
     * @brief setQrFilePath 保存为文件
     * @param value
     */
    void setQrFilePath(const QString &value);

signals:
    void qrDataChanged(const QString& qrdata);
    void qrLogoChanged(const QString& qrlogo);
    void qrSizeChanged(const QSize& qrsize);
    void qrModeChanged(QR_MODE qrmodel);
    void qrLevelChanged(QR_LEVEL qrlevel);
    void qrCasesenChanged(bool qrcasesen);
    void qrMarginChanged(int qrmargin);
    void qrPercentChanged(qreal qrpercent);
    void qrForegroundChanged(const QColor& qrfg);
    void qrBackgroundChanged(const QColor& qrbg);
    void qrSaveFileChanged(const QString& qrfilepath);

protected:
    /**
     * @brief paintEvent 绘制事件
     * @param e
     */
    void paintEvent(QPaintEvent *e);

    /**
     * @brief resizeEvent 尺寸改变事件
     * @param e
     */
    void resizeEvent(QResizeEvent *e);

private:
    /**
     * @brief saveCurViewToFile 保存二维码到文件
     */
    void saveCurViewToFile();

private:
    QString qrData;
    QString qrLogo;
    QSize qrSize;
    QR_MODE qrMode;
    QR_LEVEL qrLevel;
    bool qrCasesen;
    int qrMargin;
    qreal qrPercent;
    QColor qrForeground;
    QColor qrBackground;
    QString qrFilePath;
};

#endif // NBASEQRENCODEWIDGET_H
