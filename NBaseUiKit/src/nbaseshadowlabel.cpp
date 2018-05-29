#include "nbaseshadowlabel.h"
#include <QGraphicsDropShadowEffect>

NBaseShadowLabel::NBaseShadowLabel(QLabel *parent) : QLabel(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setAutoFillBackground(false);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect;
    shadow_effect->setOffset(-5, 5);
    shadow_effect->setColor(Qt::darkBlue);
    shadow_effect->setBlurRadius(8);
    setGraphicsEffect(shadow_effect);
}

NBaseShadowLabel::NBaseShadowLabel(const QString &text, QLabel *parent)
    :QLabel(text, parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setAutoFillBackground(false);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect;
    shadow_effect->setOffset(-5, 5);
    shadow_effect->setColor(Qt::darkBlue);
    shadow_effect->setBlurRadius(8);
    setGraphicsEffect(shadow_effect);
}
