#ifndef NNBASEIMAGECROPPER_H
#define NNBASEIMAGECROPPER_H

/**
 * 作者: daodaoliang
 * 时间: 2016年9月02日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "nbaseuikit_global.h"

class NBaseImageCropper_p;

/**
 * @brief The NBaseImageCropper class 图片截取组件
 */
class NBASEUIKITSHARED_EXPORT NBaseImageCropper : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief NBaseImageCropper
     * @param parent
     * @param isCropBtn 是否有截取按钮
     * @param isToolBtn 是否有工具按钮
     */
    NBaseImageCropper(QWidget* parent = nullptr, bool isCropBtn=false, bool isToolBtn=false);

public slots:
    /**
     * @brief setProportion 设置固定比例
     * @param paramWidth 宽的比例值
     * @param paramHeight 高的比例值
     */
    void setProportion(const quint8 &paramWidth, const quint8 &paramHeight);

    /**
     * @brief setImage 设置要截取的图片
     * @param imagePath 图片路径
     */
    void setImage(const QString imagePath);

    /**
     * @brief setCropStyle 设置截取框的风格
     * @param bgColor 背景颜色
     * @param borderColor 边框线的颜色
     */
    void setCropStyle(const QColor &bgColor, const QColor &borderColor);

    /**
     * @brief setSize 设置尺寸
     * @param width 宽
     * @param height 高
     */
    void setSize(const quint16 &width, const quint16 &height);

    /**
     * @brief cropImage 截取图片
     */
    const QPixmap cropImage();

    /**
     * @brief getCurrentPixMap 获取当前截取的图片
     * @return
     */
    QPixmap getCurrentPixMap() const;

    /**
     * @brief setCurrentPixMap 设置截取的图片
     * @param value
     */
    void setCurrentPixMap(const QPixmap &value);

private slots:
    /**
     * @brief setFTProportion 设置四比三的比例
     */
    void setFTProportion();

    /**
     * @brief setOOProportion 设置一比一的比例
     */
    void setOOProportion();

    /**
     * @brief setNoProportion 不设置固定比例
     */
    void setNoProportion();

signals:
    /**
     * @brief cropImage 截图信号
     * @param image
     */
    void singalCropImage(QPixmap image);

protected:
    /**
     * @brief showEvent showwvent
     * @param event
     */
    void showEvent(QShowEvent *event);

private:

    /**
     * @brief currentPixMap 当前截取的图片
     */
    QPixmap currentPixMap;

    /**
     * @brief imageInstance 图片处理实例
     */
    NBaseImageCropper_p *imageInstance;

    /**
     * @brief shortCut 双击显示截图的label
     */
    QLabel *shortCut;

    /**
     * @brief showBtn 是否显示截取按钮
     */
    bool showConfirmBtn;

    /**
     * @brief showToolBtn 是否显示工具按钮
     */
    bool showToolBtn;

    /**
     * @brief isFixed 是否已经固定4:3比例
     */
    bool isFTFixed;

    /**
     * @brief isOOFixed 是否已经固定1:1比例
     */
    bool isOOFixed;

    /**
     * @brief cropBtn 截取按钮
     */
    QPushButton *cropBtn;

    /**
     * @brief ftsBtn 4:3比例按钮
     */
    QPushButton *ftsBtn;

    /**
     * @brief ooBtn 1:1比例按钮
     */
    QPushButton *ooBtn;

};

#endif // NNBASEIMAGECROPPER_H
