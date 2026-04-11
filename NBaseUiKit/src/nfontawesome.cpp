#include "nfontawesome.h"

/**
 * 作者: daodaoliang
 * 时间: 2026年4月09日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QApplication>
#include <QPalette>
#include <QDebug>
#include <QFile>
#include <QFontDatabase>
#include <QFontMetrics>
#include <QString>

static void nfontawesome_init_resources()
{
    Q_INIT_RESOURCE(image_resources);
}

namespace fa {

/**
 * @brief The NFontAwesomeIconPainter class 图标绘制器基类
 */
class NFontAwesomeIconPainter
{
public:
    virtual ~NFontAwesomeIconPainter();
    virtual void paint(NFontAwesome* awesome, QPainter* painter, const QRect& rect, QIcon::Mode mode, QIcon::State state, const QVariantMap& options) = 0;
};

#include "nfontawesomestrings.h"

NFontAwesomeIconPainter::~NFontAwesomeIconPainter()
{
}

/**
 * @brief The NFontAwesomeCharIconPainter class 字符图标绘制器
 */
class NFontAwesomeCharIconPainter: public NFontAwesomeIconPainter
{
protected:

    virtual ~NFontAwesomeCharIconPainter()
    {
    }

    QStringList optionKeysForModeAndState(const QString& key, QIcon::Mode mode, QIcon::State state)
    {
        QString modePostfix;
        switch (mode) {
            case QIcon::Disabled:
                modePostfix = "-disabled";
                break;
            case QIcon::Active:
                modePostfix = "-active";
                break;
            case QIcon::Selected:
                modePostfix = "-selected";
                break;
            default:
                break;
        }

        QString statePostfix;
        if(state == QIcon::Off) {
            statePostfix = "-off";
        }

        QStringList result;
        if (!modePostfix.isEmpty()) {
            if (!statePostfix.isEmpty()) {
                result.push_back(key + modePostfix + statePostfix);
            }
            result.push_back(key + modePostfix);
        }
        if (!statePostfix.isEmpty()) {
            result.push_back(key + statePostfix);
        }
        return result;
    }

    QVariant optionValueForModeAndState(const QString& baseKey, QIcon::Mode mode, QIcon::State state,
                                        const QVariantMap& options )
    {
        for (const QString &key : optionKeysForModeAndState(baseKey, mode, state)) {
            if (options.contains(key) && !(options.value(key).toString().isEmpty())) {
                return options.value(key);
            }
        }
        return options.value(baseKey);
    }

public:

    virtual void paint(NFontAwesome* awesome, QPainter* painter, const QRect& rect, QIcon::Mode mode, QIcon::State state,
                        const QVariantMap& options)
    {
        painter->save();

        painter->setRenderHint(QPainter::Antialiasing);

        QVariant var = options.value("anim");
        NFontAwesomeAnim* anim = var.value<NFontAwesomeAnim*>();
        if (anim) {
            anim->setup(*painter, rect);
        }

        QColor color = optionValueForModeAndState("color", mode, state, options).value<QColor>();
        QString text = optionValueForModeAndState("text", mode, state, options).toString();
        int st = optionValueForModeAndState("style", mode, state, options).toInt();

        painter->setPen(color);
        QRectF textRect(rect);
        int flags = Qt::AlignHCenter | Qt::AlignVCenter;

        int drawSize = qRound(textRect.height() * options.value("scale-factor").toDouble());
        QFont ft = awesome->font(st, drawSize);
        QFontMetricsF fm(ft);
        QRectF tbr = fm.boundingRect(textRect,flags,text);
        if (tbr.width() > textRect.width()) {
            drawSize = static_cast<int>(ft.pixelSize() * qMin(textRect.width() *
                                        0.95/tbr.width(),textRect.height() * 0.95/tbr.height()));
            ft.setPixelSize(drawSize);
        }

        painter->setFont(ft);
        painter->drawText(textRect, flags, text);

        painter->restore();
    }
};

/**
 * @brief The NFontAwesomeIconPainterIconEngine class 图标引擎类
 */
class NFontAwesomeIconPainterIconEngine : public QIconEngine
{
public:
    NFontAwesomeIconPainterIconEngine(NFontAwesome* awesome, NFontAwesomeIconPainter* painter, const QVariantMap& options)
        : mAwesomeRef(awesome)
        , mIconPainterRef(painter)
        , mOptions(options)
    {
    }

    virtual ~NFontAwesomeIconPainterIconEngine(){}

    NFontAwesomeIconPainterIconEngine* clone() const
    {
        return new NFontAwesomeIconPainterIconEngine(mAwesomeRef, mIconPainterRef, mOptions);
    }

    virtual void paint(QPainter* painter, const QRect& rect, QIcon::Mode mode, QIcon::State state)
    {
        Q_UNUSED(mode);
        Q_UNUSED(state);
        mIconPainterRef->paint(mAwesomeRef, painter, rect, mode, state, mOptions);
    }

    virtual QPixmap pixmap(const QSize& size, QIcon::Mode mode, QIcon::State state)
    {
        QPixmap pm(size);
        pm.fill(Qt::transparent);
        QPainter p(&pm);
        paint(&p, QRect(QPoint(0,0),size), mode, state);
        return pm;
    }

private:
    NFontAwesome* mAwesomeRef;
    NFontAwesomeIconPainter* mIconPainterRef;
    QVariantMap mOptions;
};

const QString NFontAwesome::FA_BRANDS_FONT_FILENAME = ":/img/fonts/Font Awesome 7 Brands-Regular-400.otf";
const QString NFontAwesome::FA_REGULAR_FONT_FILENAME = ":/img/fonts/Font Awesome 7 Free-Regular-400.otf";
const QString NFontAwesome::FA_SOLID_FONT_FILENAME = ":/img/fonts/Font Awesome 7 Free-Solid-900.otf";
const QFont::Weight NFontAwesome::FA_BRANDS_FONT_WEIGHT = QFont::Normal;
const QFont::Weight NFontAwesome::FA_REGULAR_FONT_WEIGHT = QFont::Normal;
const QFont::Weight NFontAwesome::FA_SOLID_FONT_WEIGHT = QFont::Black;

NFontAwesome* NFontAwesome::mInstance = nullptr;

NFontAwesomeFontData::NFontAwesomeFontData(const QString &fontFileName, QFont::Weight fontWeight)
    : mFontFamily()
    , mFontFilename(fontFileName)
    , mFontId(-1)
    , mFontWeight(fontWeight)
{
}

const QString& NFontAwesomeFontData::fontFamily() const
{
    return mFontFamily;
}

void NFontAwesomeFontData::setFontFamily(const QString &family)
{
    mFontFamily = family;
}

const QString& NFontAwesomeFontData::fontFilename() const
{
    return mFontFilename;
}

int NFontAwesomeFontData::fontId() const
{
    return mFontId;
}

void NFontAwesomeFontData::setFontId(int id)
{
    mFontId = id;
}

QFont::Weight NFontAwesomeFontData::fontWeight() const
{
    return mFontWeight;
}

void NFontAwesomeFontData::setFontWeight(QFont::Weight weight)
{
    mFontWeight = weight;
}

NFontAwesome* NFontAwesome::instance()
{
    if (!mInstance) {
        mInstance = new NFontAwesome(qApp);
        mInstance->initFontAwesome();
    }
    return mInstance;
}

NFontAwesome::NFontAwesome(QObject* parent)
    : QObject(parent)
    , mInitialized(false)
{
    nfontawesome_init_resources();
    mInstance = this;
}

NFontAwesome::~NFontAwesome()
{
    qDeleteAll(mFonts);
    qDeleteAll(mPainters);
}

void NFontAwesome::initFontAwesome()
{
    if (mInitialized) {
        return;
    }

    mDefaultOptions.insert("color", QApplication::palette().color(QPalette::Normal, QPalette::Text));
    mDefaultOptions.insert("color-disabled", QApplication::palette().color(QPalette::Disabled, QPalette::Text));
    mDefaultOptions.insert("color-active", QApplication::palette().color(QPalette::Active, QPalette::Text));
    mDefaultOptions.insert("color-selected", QApplication::palette().color(QPalette::Active, QPalette::HighlightedText));
    mDefaultOptions.insert("scale-factor", 0.875);
    mDefaultOptions.insert("style", fa_solid);

    mPainters.insert(styleKey(fa::fa_brands), static_cast<NFontAwesomeIconPainter*>(new NFontAwesomeCharIconPainter()));
    mPainters.insert(styleKey(fa::fa_regular), static_cast<NFontAwesomeIconPainter*>(new NFontAwesomeCharIconPainter()));
    mPainters.insert(styleKey(fa::fa_solid), static_cast<NFontAwesomeIconPainter*>(new NFontAwesomeCharIconPainter()));

    initializeNamedIcons();

    mInitialized = true;
    emit fontAwesomeInitialized();
}

void NFontAwesome::initializeNamedIcons()
{
    const int count = sizeof(faCommonIconArray)/sizeof(faCommonIconArray[0]);
    for (int i = 0; i < count; i++) {
        mIconNames << faCommonIconArray[i].name;
        mIconNameToCodeMap.insert(QString::fromLatin1(faCommonIconArray[i].name), faCommonIconArray[i].icon);
    }
    mIconNames.sort();
}

int NFontAwesome::styleKey(int style)
{
    return style;
}

void NFontAwesome::ensureFont(int style)
{
    if (mFonts.contains(style)) {
        return;
    }

    QString filename;
    QFont::Weight fontWeight;
    switch (style) {
        case fa_brands:
            filename = NFontAwesome::FA_BRANDS_FONT_FILENAME;
            fontWeight = NFontAwesome::FA_BRANDS_FONT_WEIGHT;
            break;
        case fa_regular:
            filename = NFontAwesome::FA_REGULAR_FONT_FILENAME;
            fontWeight = NFontAwesome::FA_REGULAR_FONT_WEIGHT;
            break;
        case fa_solid:
            filename = NFontAwesome::FA_SOLID_FONT_FILENAME;
            fontWeight = NFontAwesome::FA_SOLID_FONT_WEIGHT;
            break;
        default:
            filename = NFontAwesome::FA_SOLID_FONT_FILENAME;
            fontWeight = NFontAwesome::FA_SOLID_FONT_WEIGHT;
            break;
    }

    NFontAwesomeFontData* fontData = new NFontAwesomeFontData(filename, fontWeight);
    QFile fontFile(filename);
    if (fontFile.open(QFile::ReadOnly)) {
        int fontId = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
        fontData->setFontId(fontId);
        fontData->setFontFamily(QFontDatabase::applicationFontFamilies(fontId).first());
        fontFile.close();
    } else {
        qDebug() << "NFontAwesome: could not open font file " << filename;
    }

    mFonts.insert(style, fontData);
}

QFont NFontAwesome::font(int style, int size)
{
    ensureFont(style);
    QFont font(mFonts[style]->fontFamily());
    font.setPixelSize(size);
    font.setWeight(mFonts[style]->fontWeight());
    return font;
}

QIcon NFontAwesome::icon(int character, const QVariantMap& options)
{
    return QIcon(createIconEngine(character, options));
}

QIcon NFontAwesome::icon(const QString& name, const QVariantMap& options)
{
    int character = mIconNameToCodeMap.value(name, 0);
    return icon(character, options);
}

bool NFontAwesome::exists(const QString& name)
{
    return mIconNameToCodeMap.contains(name);
}

const QStringList& NFontAwesome::iconNames()
{
    return mIconNames;
}

void NFontAwesome::setDefaultOption(const QString& name, const QVariant& value)
{
    mDefaultOptions.insert(name, value);
}

const QVariant NFontAwesome::defaultOption(const QString& name)
{
    return mDefaultOptions.value(name);
}

QIconEngine* NFontAwesome::createIconEngine(int character, const QVariantMap& options)
{
    initFontAwesome();

    QVariantMap optionsCopy = mDefaultOptions;
    for (auto it = options.begin(); it != options.end(); ++it) {
        optionsCopy.insert(it.key(), it.value());
    }
    optionsCopy.insert("text", QChar(character));

    int st = optionsCopy.value("style").toInt();
    NFontAwesomeIconPainter* painter = mPainters.value(styleKey(st), nullptr);
    return new NFontAwesomeIconPainterIconEngine(this, painter, optionsCopy);
}

void NFontAwesome::render(int character, QPainter* painter, const QRect& rect, const QVariantMap& options)
{
    initFontAwesome();

    QVariantMap optionsCopy = mDefaultOptions;
    for (auto it = options.begin(); it != options.end(); ++it) {
        optionsCopy.insert(it.key(), it.value());
    }
    optionsCopy.insert("text", QChar(character));

    int st = optionsCopy.value("style").toInt();
    NFontAwesomeIconPainter* icoPainter = mPainters.value(styleKey(st), nullptr);
    if (icoPainter) {
        icoPainter->paint(this, painter, rect, QIcon::Normal, QIcon::On, optionsCopy);
    }
}

} // namespace fa
