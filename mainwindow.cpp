#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    linkButtons();
}

void MainWindow::linkButtons()
{
    QPushButton* buttonNew = findChild<QPushButton*>("pushButton_2");
    if(buttonNew)
    {
        QObject::connect(buttonNew, SIGNAL(clicked()), this, SLOT(loadDatasFromFile()));
    }
    QPushButton* buttonLoad = findChild<QPushButton*>("pushButton_3");
    if(buttonLoad)
    {
        QObject::connect(buttonLoad, SIGNAL(clicked()), this, SLOT(close()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    f.cleanUpPlayers();
    f.setDataSaved(true);
    f.exec();
}

QString MainWindow::getPathFile(QWidget* ptrWidget)
{
    if(! ptrWidget)
    {
        return "";
    }
    QFileDialog dialog;
    dialog.setDefaultSuffix("json");//doesn't work
    return dialog.getOpenFileName(ptrWidget,
                       tr("Load File"),
                       ".",
                       tr("json(*.json);;All files (*)"));
}

void MainWindow::loadDatasFromFile()
{
    QString fileName = getPathFile(this), jsonContent;
    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream >> jsonContent;
        QMessageBox::warning(this, "Erreur", jsonContent);
        file.close();
    }
}
