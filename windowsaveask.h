#ifndef WINDOWSAVEASK_H
#define WINDOWSAVEASK_H

#include <QDialog>

namespace Ui {
class WindowSaveAsk;
}

class WindowSaveAsk : public QDialog
{
    Q_OBJECT

public:
    explicit WindowSaveAsk(QWidget *parent = 0);
    ~WindowSaveAsk();

private:
    void linkButtons();
private:
    Ui::WindowSaveAsk *ui;
private slots:
    void closeForm();
    void saveForm();
};

#endif // WINDOWSAVEASK_H
