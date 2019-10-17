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

void PresetTeamForm::displayError(const std::string &message)const
{
    QMessageBox msgBox;
    msgBox.setText(QString(message.c_str()));
    msgBox.exec();
}


void PresetTeamForm::on_pushButton_clicked()
{
    QString strA = playerA->text();
    QString strB = playerB->text();
    QString strC = playerC->text();
    if(strA.isEmpty() || strB.isEmpty())
    {
        displayError("Erreur: Mauvaises entrée(s) d'équipe.");
        return;
    }
    std::string strStdA = strA.toStdString();
    std::string strStdB = strB.toStdString();
    std::string strStdC = strC.toStdString();
    if(!checkEqualsEntries(strStdA, strStdB, strStdC) ||
            !checkExistingPlayers(strStdA, strStdB, strStdC))
    {
        return;
    }
    m_vectPlayers.emplace_back(strStdA);
    m_vectPlayers.emplace_back(strStdB);
    if(!strC.isEmpty())
    {
        m_vectPlayers.emplace_back(strStdC);
    }
    m_vectTeam.push_back({strStdA, strStdB, strStdC});
    m_TeamLayout->addLayout(new TeamLine(*this, strStdA, strStdB, strStdC));
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

bool PresetTeamForm::checkEqualsEntries(const std::string &strA,
                                        const std::string &strB,
                                        const std::string &strC)const
{
    if(strA == strB || strA == strC || strB == strC)
    {
        displayError("Erreur noms entrés similaires.");
        return false;
    }
    return true;
}

bool PresetTeamForm::checkExistingPlayers(const std::string &strA,
                                          const std::string &strB,
                                          const std::string &strC)const
{
    bool res = true;
    std::vector<std::string>::const_iterator it;
    std::string message = "Erreur joueur(s) déja existant(s)\n";
    if(std::find(m_vectPlayers.begin(), m_vectPlayers.end(), strA) != m_vectPlayers.end())
    {
        res = false;
        message += " " + strA;
    }
    if(std::find(m_vectPlayers.begin(), m_vectPlayers.end(), strB) != m_vectPlayers.end())
    {
        res = false;
        message += " " + strB;
    }
    if(!strC.empty() && std::find(m_vectPlayers.begin(), m_vectPlayers.end(), strC) != m_vectPlayers.end())
    {
        res = false;
        message += " " + strC;
    }
    if(!res)
    {
        displayError(message);
    }
    return res;
}
