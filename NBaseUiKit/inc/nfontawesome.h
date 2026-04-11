#ifndef NFONTAWESOME_H
#define NFONTAWESOME_H

/**
 * 作者: daodaoliang
 * 时间: 2026年4月09日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QIcon>
#include <QIconEngine>
#include <QPainter>
#include <QRect>
#include <QVariantMap>
#include "nfontawesomeanim.h"
#include "nfontawesomecodes.h"
#include "nbaseuikit_global.h"

namespace fa {

/**
 * @brief The fa_styles enum 字体图标样式
 */
enum fa_styles {
    fa_solid = 0,
    fa_regular = 1,
    fa_brands = 2
};

/**
 * @brief The NFontAwesomeNamedIcon struct 命名图标结构体
 */
struct NFontAwesomeNamedIcon {
    const char *name;
    ushort icon;
};

class NFontAwesomeIconPainter;

/**
 * @brief The NFontAwesomeFontData class 字体数据类
 */
class NBASEUIKITSHARED_EXPORT NFontAwesomeFontData
{
public:
    NFontAwesomeFontData() : NFontAwesomeFontData(QString()) {}
    NFontAwesomeFontData(const QString &fontFileName, QFont::Weight fontWeight = QFont::Normal);
    const QString& fontFamily() const;
    void setFontFamily(const QString &family);
    const QString& fontFilename() const;
    int fontId() const;
    void setFontId(int id);
    QFont::Weight fontWeight() const;
    void setFontWeight(QFont::Weight weight);

private:
    QString mFontFamily;
    QString mFontFilename;
    int mFontId;
    QFont::Weight mFontWeight;
};

/**
 * @brief The NFontAwesome class Font Awesome 图标管理类
 */
class NBASEUIKITSHARED_EXPORT NFontAwesome : public QObject
{
    Q_OBJECT

public:
    static const QString FA_BRANDS_FONT_FILENAME;
    static const QString FA_REGULAR_FONT_FILENAME;
    static const QString FA_SOLID_FONT_FILENAME;
    static const QFont::Weight FA_BRANDS_FONT_WEIGHT;
    static const QFont::Weight FA_REGULAR_FONT_WEIGHT;
    static const QFont::Weight FA_SOLID_FONT_WEIGHT;

public:
    explicit NFontAwesome(QObject* parent = nullptr);
    virtual ~NFontAwesome();

    /**
     * @brief initFontAwesome 初始化 Font Awesome 字体
     */
    void initFontAwesome();

    /**
     * @brief icon 获取图标
     * @param character 图标编码
     * @param options 图标选项
     * @return 图标对象
     */
    QIcon icon(int character, const QVariantMap& options = QVariantMap());

    /**
     * @brief icon 获取图标
     * @param name 图标名称
     * @param options 图标选项
     * @return 图标对象
     */
    QIcon icon(const QString& name, const QVariantMap& options = QVariantMap());

    /**
     * @brief setDefaultOption 设置默认选项
     * @param name 选项名
     * @param value 选项值
     */
    void setDefaultOption(const QString& name, const QVariant& value);

    /**
     * @brief defaultOption 获取默认选项
     * @param name 选项名
     * @return 选项值
     */
    const QVariant defaultOption(const QString& name);

    /**
     * @brief font 获取字体
     * @param style 样式
     * @param size 字号
     * @return 字体对象
     */
    QFont font(int style, int size);

    /**
     * @brief exists 检查图标是否存在
     * @param name 图标名称
     * @return 是否存在
     */
    bool exists(const QString& name);

    /**
     * @brief iconNames 获取所有图标名称
     * @return 图标名称列表
     */
    const QStringList& iconNames();

    /**
     * @brief instance 获取单例实例
     * @return 单例实例
     */
    static NFontAwesome* instance();

signals:
    /**
     * @brief fontAwesomeInitialized 初始化完成信号
     */
    void fontAwesomeInitialized();

protected:
    virtual QIconEngine* createIconEngine(int character, const QVariantMap& options);
    void render(int character, QPainter* painter, const QRect& rect, const QVariantMap& options);

private:
    void initializeNamedIcons();
    int styleKey(int style);
    void ensureFont(int style);

private:
    QHash<int, NFontAwesomeFontData*> mFonts;
    QHash<int, NFontAwesomeIconPainter*> mPainters;
    QVariantMap mDefaultOptions;
    QStringList mIconNames;
    QHash<QString, int> mIconNameToCodeMap;
    bool mInitialized;
    static NFontAwesome* mInstance;
};

} // namespace fa

#endif // NFONTAWESOME_H
