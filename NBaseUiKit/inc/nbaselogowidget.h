#ifndef NBASELOGOWIDGET_H
#define NBASELOGOWIDGET_H

/**
 * 作者: daodaoliang
 * 时间: 2016年9月22日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include "nbaseuikit_global.h"
#include "nbaseimagecropper.h"


/**
 * @brief The NbaseLogoWidget class 头像编辑空间
 */
class NBASEUIKITSHARED_EXPORT NBaseLogoWidget : public QLabel
{
    Q_OBJECT
public:
    /**
     * @brief NbaseLogoWidget 构造函数
     * @param parent
     */
    explicit NBaseLogoWidget(QWidget *parent = 0);

public:
    /**
     * @brief editLogo 编辑头像的处理函数
     */
    void editLogo();

    /**
     * @brief getLogoPath 获取头像路径
     * @return
     */
    QString getLogoPath() const;

    /**
     * @brief setLogoPath 设置头像路径
     * @param value
     */
    void setLogoPath(const QString &value);

private slots:
    /**
     * @brief cropImage 图片截取
     * @param paramValue
     */
    void cropImage(QPixmap paramValue);

protected:
    /**
     * @brief mouseDoubleClickEvent 鼠标双击事件
     * @param event
     */
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    /**
     * @brief isProcessing 是否正在处理
     */
    bool isProcessing;
    /**
     * @brief imageCrop 图片截取
     */
    NBaseImageCropper *imageCrop;

    /**
     * @brief logoPath 头像路径
     */
    QString logoPath;
};

#endif // NBASELOGOWIDGET_H
