#ifndef MODIFYLINE_H
#define MODIFYLINE_H

#include <QDialog>
class PlayerLine;
class QAbstractButton;
enum{
    HOMME, FEMME
};
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
signals:

private slots:
    void clickedOk();
    void clickedCancel();

private:
    Ui::ModifyLine *ui;
    PlayerLine *m_memPlayerLine = nullptr;
};

#endif // MODIFYLINE_H
