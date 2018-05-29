#ifndef NBASEROUNDPROGRESSBAR_H
#define NBASEROUNDPROGRESSBAR_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月16日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QPainter>
#include "nbaseuikit_global.h"

/**
 * @brief The NBaseRoundProgressBar class 圆形进度条
 */
class NBASEUIKITSHARED_EXPORT NBaseRoundProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit NBaseRoundProgressBar(QWidget *parent = 0);

    static const int PositionLeft = 180;
    static const int PositionTop = 90;
    static const int PositionRight = 0;
    static const int PositionBottom = -90;

    enum BarStyle
    {
        // 甜甜圈风格
        StyleDonut,
        // 圆饼风格
        StylePie,
        // 线风格
        StyleLine
    };
public:
    double nullPosition() const;
    void setNullPosition(double position);

    void setBarStyle(BarStyle style);
    BarStyle barStyle() const;

    void setOutlinePenWidth(double penWidth);
    double outlinePenWidth() const;

    void setDataPenWidth(double penWidth);
    double dataPenWidth() const;

    void setDataColors(const QGradientStops& stopPoints);

    void setFormat(const QString& format);
    void resetFormat();
    QString	format() const;

    void setDecimals(int count);
    int decimals() const;

    double value() const;

    double minimum() const;

    double maximum() const;

public slots:
    void setRange(double min, double max);
    void setMinimum(double min);
    void setMaximum(double max);
    void setValue(double val);
    void setValue(int val);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void drawBackground(QPainter& p, const QRectF& baseRect);
    virtual void drawBase(QPainter& p, const QRectF& baseRect);
    virtual void drawValue(QPainter& p, const QRectF& baseRect, double value, double arcLength);
    virtual void calculateInnerRect(const QRectF& baseRect, double outerRadius, QRectF& innerRect, double& innerRadius);
    virtual void drawInnerBackground(QPainter& p, const QRectF& innerRect);
    virtual void drawText(QPainter& p, const QRectF& innerRect, double innerRadius, double value);
    virtual QString valueToText(double value) const;
    virtual void valueFormatChanged();
    virtual QSize minimumSizeHint() const { return QSize(32,32); }
    virtual bool hasHeightForWidth() const { return true; }
    virtual int heightForWidth(int w) const { return w; }
    void rebuildDataBrushIfNeeded();

protected:
    double m_min, m_max;
    double m_value;
    double m_nullPosition;
    BarStyle m_barStyle;
    double m_outlinePenWidth, m_dataPenWidth;
    QGradientStops m_gradientData;
    bool m_rebuildBrush;
    QString m_format;
    int m_decimals;
    static const int UF_VALUE = 1;
    static const int UF_PERCENT = 2;
    static const int UF_MAX = 4;
    int m_updateFlags;
};

#endif // NBASEROUNDPROGRESSBAR_H
