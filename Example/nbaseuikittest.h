#ifndef NBASEUIKITTEST_H
#define NBASEUIKITTEST_H

#include <QWidget>

namespace Ui {
class NBaseUiKitTest;
}

class NBaseUiKitTest : public QWidget
{
    Q_OBJECT

public:
    explicit NBaseUiKitTest(QWidget *parent = 0);
    ~NBaseUiKitTest();

private slots:
    /**
     * @brief on_pushButton_clicked 可以移动窗体的测试用例
     */
    void on_pushButton_clicked();

    /**
     * @brief on_pushButton_2_clicked 渐入渐出窗体测试用例
     */
    void on_pushButton_2_clicked();

    /**
     * @brief on_pushButton_3_clicked 迷你窗体测试用例
     */
    void on_pushButton_3_clicked();

    /**
     * @brief on_pushButton_4_clicked 阴影窗体测试用例
     */
    void on_pushButton_4_clicked();

    /**
     * @brief on_pushButton_5_clicked 弹出窗体测试用例
     */
    void on_pushButton_5_clicked();

    /**
     * @brief on_pushButton_6_clicked snowLabel测试用例
     */
    void on_pushButton_6_clicked();

    /**
     * @brief on_pushButton_8_clicked 圆周运动窗体测试用例
     */
    void on_pushButton_8_clicked();

    /**
     * @brief on_pushButton_7_clicked LED窗体测试用例
     */
    void on_pushButton_7_clicked();

    /**
     * @brief on_pushButton_9_clicked LED窗体测试用例(闪光灯效果)
     */
    void on_pushButton_9_clicked();

    /**
     * @brief on_pushButton_10_clicked 跑马灯label测试用例
     */
    void on_pushButton_10_clicked();

    /**
     * @brief on_pushButton_11_clicked QR测试用例
     */
    void on_pushButton_11_clicked();

    /**
     * @brief on_pushButton_12_clicked 圆形进度条测试用例(甜甜圈样式)
     */
    void on_pushButton_12_clicked();

    /**
     * @brief on_pushButton_13_clicked 圆形进度条测试用例(线性样式)
     */
    void on_pushButton_13_clicked();

    /**
     * @brief on_pushButton_14_clicked toastr 测试用例
     */
    void on_pushButton_14_clicked();

    /**
     * @brief on_pushButton_15_clicked 阴影Label 测试用例
     */
    void on_pushButton_15_clicked();

    /**
     * @brief on_pushButton_16_clicked 等待框(box) 测试用例
     */
    void on_pushButton_16_clicked();

    /**
     * @brief on_pushButton_16_clicked 等待框(android) 测试用例
     */
    void on_pushButton_17_clicked();

    /**
     * @brief on_pushButton_17_clicked 触屏垂直滚动 测试用例
     */
    void on_pushButton_18_clicked();

    /**
     * @brief on_pushButton_19_clicked 反转窗体 测试用例
     */
    void on_pushButton_19_clicked();

    /**
     * @brief on_pushButton_20_clicked 触屏水平滚动 测试用例
     */
    void on_pushButton_20_clicked();

    /**
     * @brief on_pushButton_21_clicked 验证码窗体 测试用例
     */
    void on_pushButton_21_clicked();

    /**
     * @brief on_pushButton_22_clicked 图片截取 测试用例
     */
    void on_pushButton_22_clicked();

    /**
     * @brief on_pushButton_23_clicked switch按钮 测试用例
     */
    void on_pushButton_23_clicked();

    /**
     * @brief on_pushButton_24_clicked 卷轴widget 测试用例
     */
    void on_pushButton_24_clicked();

    /**
     * @brief on_pushButton_25_clicked 头像编辑 测试用例
     */
    void on_pushButton_25_clicked();

    /**
     * @brief on_pushButton_26_clicked 点击波按钮
     */
    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

private:
    Ui::NBaseUiKitTest *ui;
};

#endif // NBASEUIKITTEST_H
