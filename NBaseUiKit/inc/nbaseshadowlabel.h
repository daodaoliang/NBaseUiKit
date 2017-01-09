#ifndef NBASESHADOWLABEL_H
#define NBASESHADOWLABEL_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月18日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QLabel>
#include "nbaseuikit_global.h"

/**
 * @brief The NBaseShadowLabel class  文字阴影的label
 */
class NBASEUIKITSHARED_EXPORT NBaseShadowLabel : public QLabel
{
    Q_OBJECT
public:
    explicit NBaseShadowLabel(QLabel *parent = 0);
    explicit NBaseShadowLabel(const QString &text, QLabel *parent = 0);
};

#endif // NBASESHADOWLABEL_H
