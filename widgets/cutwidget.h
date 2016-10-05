#ifndef CUT_H
#define CUT_H

#include <QWidget>

namespace Ui {
class CutWidget;
}

class CutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CutWidget(QWidget *parent = 0);
    ~CutWidget();

private:
    Ui::CutWidget *ui;
};

#endif // CUT_H
