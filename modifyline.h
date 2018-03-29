#ifndef MODIFYLINE_H
#define MODIFYLINE_H

#include <QDialog>

namespace Ui {
class ModifyLine;
}

class ModifyLine : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyLine(QWidget *parent = 0);
    ~ModifyLine();

private:
    Ui::ModifyLine *ui;
};

#endif // MODIFYLINE_H
