#ifndef MODECHOOSEWINDOW_H
#define MODECHOOSEWINDOW_H

#include <QDialog>
#include <QRadioButton>

namespace Ui {
class ModeChooseWindow;
}

class ModeChooseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModeChooseWindow(QWidget *parent = 0);
    inline bool checkOK(){return m_OK;}
    inline bool isMeleeMeleeMode(){return m_radioMeleeMeleeButton->isChecked();}
    ~ModeChooseWindow();

private slots:
    void on_OKButton_clicked();
    void on_CancelButton_clicked();

private:
    Ui::ModeChooseWindow *ui;
    QRadioButton *m_radioMeleeMeleeButton;
    bool m_OK;
};

#endif // MODECHOOSEWINDOW_H
