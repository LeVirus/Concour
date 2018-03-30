#ifndef MODIFYLINE_H
#define MODIFYLINE_H

#include <QDialog>

class QAbstractButton;

namespace Ui {
class ModifyLine;
}

class ModifyLine : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyLine(QWidget *parent = 0);
    void setParams(const QString &nom, bool homme);
    ~ModifyLine();

private slots:
    void on_buttonBox_clicked();

private:
    Ui::ModifyLine *ui;
};

#endif // MODIFYLINE_H
