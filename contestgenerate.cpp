#include "contestgenerate.h"
#include "ui_contestgenerate.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDebug>
#include <QSpinBox>
#include <QLabel>

ContestGenerate::ContestGenerate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContestGenerate)
{
    ui->setupUi(this);
    if(! linkWidgets())
    {
        QMessageBox::warning(this, "Erreur", "Problème de liens.");
    }
}

bool ContestGenerate::linkWidgets()
{
    m_ThreePlayersTeam = findChild<QSpinBox*>("spinBox");
    m_TwoPlayersTeam = findChild<QSpinBox*>("spinBox_2");

    m_MenTotal = findChild<QLabel*>("label");
    m_WomenTotal = findChild<QLabel*>("label_2");
    return m_ThreePlayersTeam && m_TwoPlayersTeam && m_MenTotal && m_WomenTotal;
}

bool ContestGenerate::updateCurrentContest(const QVBoxLayout* manLayout, const QVBoxLayout* womanLayout)
{
    m_manLayout = manLayout;
    m_womanLayout = womanLayout;
    if(! m_manLayout || ! m_womanLayout)
    {
        QMessageBox::warning(this, "Erreur", "Données corrompues.");
        return false;
    }

    if(! setNumberContestTeam(m_manLayout->count() + m_womanLayout->count()))
    {
        return false;
    }
    updateUI();
    return true;
}

bool ContestGenerate::setNumberContestTeam(unsigned int totalPlayers)
{
    if(totalPlayers < 5)
    {
        QMessageBox::warning(this, "Erreur", "Le Nombre de joueur est insuffisant. Minimum 5.");
        return false;
    }
    unsigned int threePlayersTeamNumberModulo = totalPlayers % 3;
    m_threePlayersTeam = totalPlayers / 3;
    m_twoPlayersTeam = threePlayersTeamNumberModulo / 2;
    //set a pair number of team
    do
    {
//        qDebug() << "\nTotal:: " << totalPlayers
//                 << "\nTT3 players team:: " << threePlayersTeamNumber << "\n2 players team:: " << twoPlayersTeamNumber
//                 << "\n3 players team mod:: "<< threePlayersTeamNumberModulo << "\n\n";
        if(threePlayersTeamNumberModulo % 2 || (m_threePlayersTeam + m_twoPlayersTeam) % 2)
        {
            if(m_threePlayersTeam == 0)
            {
                m_threePlayersTeam = totalPlayers / 3;
                threePlayersTeamNumberModulo = totalPlayers % 3;
                m_twoPlayersTeam = threePlayersTeamNumberModulo / 2;
                QMessageBox::warning(this, "Attention", "Résolution impossible.");
                break;
            }
            --m_threePlayersTeam;
            threePlayersTeamNumberModulo += 3;
            m_twoPlayersTeam = threePlayersTeamNumberModulo / 2;
        }
        else
        {
            break;
        }
    }while(true);

    qDebug() << "\nOKKKKKK\nTotal:: " << totalPlayers
             << "\nTT3 players team:: " << m_threePlayersTeam << "\n2 players team:: " << m_twoPlayersTeam
             << "\n3 players team mod:: "<< threePlayersTeamNumberModulo << "\n\n";

    return true;

}

void ContestGenerate::updateUI()
{
    if(m_manLayout && m_womanLayout)
    {
        std::string man = "Effectif hommes : " + std::to_string(m_manLayout->count());
        std::string woman = "Effectif femmes : " + std::to_string(m_womanLayout->count());
        m_MenTotal->setText(QString(man.c_str()));
        m_WomenTotal->setText(QString(woman.c_str()));
    }
    m_ThreePlayersTeam->setValue(m_threePlayersTeam);
    m_TwoPlayersTeam->setValue(m_twoPlayersTeam);
}

ContestGenerate::~ContestGenerate()
{
    delete ui;
}
