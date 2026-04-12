#ifndef NBASEUIKITTEST_H
#define NBASEUIKITTEST_H

#include <QMainWindow>
#include <functional>

namespace Ui {
class NBaseUiKitTest;
}

class NBaseUiKitTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit NBaseUiKitTest(QWidget *parent = 0);
    ~NBaseUiKitTest();

private slots:
    void onCategoryClicked();

private:
    Ui::NBaseUiKitTest *ui;
    
    // 分类显示函数
    void showLayoutComponents();
    void showAnimationComponents();
    void showInputComponents();
    void showDisplayComponents();
    void showDialogComponents();
    void showIconComponents();
    void showOtherComponents();
    
    // 辅助函数
    void clearContentLayout();
    void addComponent(const QString &name, const QString &description, const QString &code, std::function<void()> demoFunction);
};

#endif // NBASEUIKITTEST_H
