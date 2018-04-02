#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void linkButtons();
    QString getPathFile(QWidget *ptrWidget);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void loadDatasFromFile();

private:
    Ui::MainWindow *ui;
    Form f;
};


#endif // MAINWINDOW_H
