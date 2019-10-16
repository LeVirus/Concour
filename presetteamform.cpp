#include "presetteamform.h"
#include "ui_presetteamform.h"
#include "teamline.h"
#include <QMessageBox>

PresetTeamForm::PresetTeamForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PresetTeamForm)
{
    ui->setupUi(this);
    setLayouts();
    linkUIElement();
}

PresetTeamForm::~PresetTeamForm()
{
    delete ui;
}

void PresetTeamForm::linkUIElement()
{
    playerA = findChild<QLineEdit*>("lineEdit");
    playerB = findChild<QLineEdit*>("lineEdit_2");
    playerC = findChild<QLineEdit*>("lineEdit_3");

}

void PresetTeamForm::displayError()
{
    QMessageBox msgBox;
    msgBox.setText("Erreur: Mauvaises entrée(s) d'équipe.");
    msgBox.exec();
}


void PresetTeamForm::on_pushButton_clicked()
{
    QString strA = playerA->text();
    QString strB = playerB->text();
    QString strC = playerC->text();
    if(strA.isEmpty() || strB.isEmpty())
    {
        displayError();
        return;
    }
    m_vectTeam.push_back({strA.toStdString(),
                          strB.toStdString(),
                          strC.toStdString()});
    m_TeamLayout->addLayout(new TeamLine(strA + QString("\t") +
                                         strB + QString("\t") + strC));
    clearLineEdit();
}

void PresetTeamForm::setLayouts()
{
    QScrollArea *sds = findChild<QScrollArea*>("scrollArea");
    m_TeamLayout = new QVBoxLayout(sds);
    sds->setLayout(m_TeamLayout);
    QWidget* wid = findChild<QScrollArea*>("scrollArea")->
            findChild<QWidget*>("scrollAreaWidgetContents");
    wid->setLayout(m_TeamLayout);
    wid->setMaximumWidth(300);
}

void PresetTeamForm::clearLineEdit()
{
    playerA->clear();
    playerB->clear();
    playerC->clear();
}
