#ifndef NFONT_AWESOME_TEST_H
#define NFONT_AWESOME_TEST_H

#include <QMainWindow>
#include "nfontawesome.h"

namespace Ui {
class NFontAwesomeTest;
}

class NFontAwesomeTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit NFontAwesomeTest(QWidget *parent = 0);
    ~NFontAwesomeTest();

private slots:
    void styleChanged(int index);

private:
    Ui::NFontAwesomeTest *mUi;
    fa::NFontAwesome *mAwesome;
};

#endif // NFONT_AWESOME_TEST_H