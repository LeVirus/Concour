#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
//#include <QDebug>

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
    Form *form = Form::getInstance();
    if(!form)
    {
        return;
    }
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream >> jsonContent;
//        QMessageBox::warning(this, "test", jsonContent);
        file.close();
    }
    else
    {
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonContent.toUtf8());
    if(jsonDoc.isNull() || jsonDoc.isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Le fichier est vide.");
        return;
    }
    QJsonObject obj = jsonDoc.object();
    if(! obj["Femmes"].isArray() || ! obj["Hommes"].isArray())
    {
        QMessageBox::warning(this, "Erreur", "Les données de ce fichier sont corrompues.");
        return;
    }

    //clean up existing form
    f.cleanUpPlayers();
    f.setDataSaved(true);

    QJsonArray women = obj["Femmes"].toArray();
    QJsonArray men = obj["Hommes"].toArray();
//        qDebug() << men.count() << women.count();
    for(int i = 0; i < women.count(); ++i)
    {
        form->insertPlayer(false, women.at(i).toString());
    }
    for(int i = 0; i < men.count(); ++i)
    {
        form->insertPlayer(true, men.at(i).toString());
    }
    f.exec();
}
