#include <QApplication>
#include "nbaseuikittest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NBaseUiKitTest test_widget;
    test_widget.show();
    return a.exec();
}
