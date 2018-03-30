#ifndef MODIFYLINE_H
#define MODIFYLINE_H

#include <QDialog>

class PlayerLine;
class QAbstractButton;
class QComboBox;
class QLineEdit;

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
    void setParams(const QString &nom, bool homme, PlayerLine *refPlayerLine);
    ~ModifyLine();
signals:

private slots:
    void clickedOk();
    void clickedCancel();

private:
    Ui::ModifyLine *ui;
    PlayerLine *m_memPlayerLine = nullptr;
    QComboBox* m_comboBox = nullptr;
    QLineEdit* m_lineEdit = nullptr;
    QString m_PreviousLabelValue;
private:
    void changeArrayLine();
};

#endif // MODIFYLINE_H
