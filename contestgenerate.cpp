#include "contestgenerate.h"
#include "ui_contestgenerate.h"
#include "form.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDebug>
#include <QSpinBox>
#include <QLabel>
#include <QWidget>
#include <QTabWidget>
#include <QScrollArea>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <versusteams.h>


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
    m_MenTotal = findChild<QLabel*>("label");
    m_WomenTotal = findChild<QLabel*>("label_2");
    m_DoubletNumber = findChild<QLabel*>("label_4");
    m_ThreesomeNumber = findChild<QLabel*>("label_3");
    m_gamesTab = findChild<QTabWidget*>("tabWidget");
    return m_DoubletNumber && m_ThreesomeNumber && m_MenTotal && m_WomenTotal && m_gamesTab;
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
    storePlayersNames();

    if(! setNumberContestTeam())
    {
        return false;
    }
    return true;
}

bool ContestGenerate::setNumberContestTeam()
{
    unsigned int totalPlayers = m_manLayout->count() + m_womanLayout->count();
    if(totalPlayers < 5)
    {
        QMessageBox::warning(this, "Erreur", "Le Nombre de joueur est insuffisant. Minimum 5.");
        return false;
    }
    unsigned int threePlayersTeamNumberModulo = totalPlayers % 3;
    m_threePlayersTeamNumber = totalPlayers / 3;
    m_twoPlayersTeamNumber = threePlayersTeamNumberModulo / 2;
    //set a pair number of team
    do
    {
//        qDebug() << "\nTotal:: " << totalPlayers
//                 << "\nTT3 players team:: " << threePlayersTeamNumber << "\n2 players team:: " << twoPlayersTeamNumber
//                 << "\n3 players team mod:: "<< threePlayersTeamNumberModulo << "\n\n";
        if(threePlayersTeamNumberModulo % 2 || (m_threePlayersTeamNumber + m_twoPlayersTeamNumber) % 2)
        {
            if(m_threePlayersTeamNumber == 0)
            {
                m_threePlayersTeamNumber = totalPlayers / 3;
                threePlayersTeamNumberModulo = totalPlayers % 3;
                m_twoPlayersTeamNumber = threePlayersTeamNumberModulo / 2;
                QMessageBox::warning(this, "Attention", "Résolution impossible.");
                break;
            }
            --m_threePlayersTeamNumber;
            threePlayersTeamNumberModulo += 3;
            m_twoPlayersTeamNumber = threePlayersTeamNumberModulo / 2;
        }
        else
        {
            break;
        }
    }while(true);

    qDebug() << "\nOKKKKKK\nTotal:: " << totalPlayers
             << "\nTT3 players team:: " << m_threePlayersTeamNumber << "\n2 players team:: " << m_twoPlayersTeamNumber
             << "\n3 players team mod:: "<< threePlayersTeamNumberModulo << "\n\n";

    return true;

}

void ContestGenerate::setTeamBuildOption(unsigned int option, unsigned int gamesNumber)
{
    if(option > MELEE_MELEE)//if bad option
    {
        m_teamBuildOption = MELEE;
    }
    else
    {
        m_teamBuildOption = option;
    }
    if(gamesNumber != 0 && gamesNumber < 10)
    {
        m_gamesNumber = ++gamesNumber;
    }
    else
    {
       m_gamesNumber = 5;
    }
}

void ContestGenerate::storePlayersNames()
{
    m_stockPlayersMen.clear();
    m_stockPlayersWomen.clear();
    for(int i = 0; i < m_manLayout->count(); ++i)
    {
        PlayerLine* memLine = static_cast<PlayerLine*>(m_manLayout->itemAt(i));
        if(memLine)
        {
            m_stockPlayersMen.push_back(memLine->getLabel()->text().toStdString());//get name
        }
    }
    for(int i = 0; i < m_womanLayout->count(); ++i)
    {
        PlayerLine* memLine = static_cast<PlayerLine*>(m_womanLayout->itemAt(i));
        if(memLine)
        {
            m_stockPlayersWomen.push_back(memLine->getLabel()->text().toStdString());
        }
    }
}

void ContestGenerate::generateTeam()
{
    if(m_stockPlayersMen.empty() && m_stockPlayersWomen.empty())
    {
        return;
    }
    Team::static_reinitCmpt();
    m_threePlayersTeam.clear();
    m_twoPlayersTeam.clear();
    instanciateTeams(m_threePlayersTeamNumber, m_twoPlayersTeamNumber);

    std::srand(rand());
    vectString vectMenNames = m_stockPlayersMen,
               vectWomenNames = m_stockPlayersWomen;
    generateThreePlayersTeam(vectMenNames, vectWomenNames);
    generateTwoPlayersTeam(vectMenNames, vectWomenNames);
//    displayTeams();
//    displayNames();
}

void ContestGenerate::generateThreePlayersTeam(vectString &men, vectString &women)
{
    for(unsigned int i = 0; i < m_threePlayersTeamNumber; ++i)
    {
        for(unsigned int j = 0; j < 3; ++j)
        {
            if( (j == 0 && !women.empty()) || men.empty())
            {
                unsigned int rand = std::rand()/((RAND_MAX + 1u) / women.size());  // Note: 1+rand()%6 is wrong!
                m_threePlayersTeam[i].modifyPlayerName(women[rand], j);
                women.erase(women.begin() + rand);
                continue;
            }
            if(!men.empty())
            {
                unsigned int rand = std::rand()/((RAND_MAX + 1u) / men.size());
                m_threePlayersTeam[i].modifyPlayerName(men[rand], j);
                men.erase(men.begin() + rand);
            }
        }
    }
}

void ContestGenerate::generateTwoPlayersTeam(vectString &men, vectString &women)
{
    for(unsigned int i = 0; i < m_twoPlayersTeamNumber; ++i)
    {
        for(unsigned int j = 0; j < 2; ++j)
        {
            if( (j == 0 && !women.empty()) || men.empty())
            {
                unsigned int rand = std::rand()/((RAND_MAX + 1u) / women.size());  // Note: 1+rand()%6 is wrong!
                m_twoPlayersTeam[i].modifyPlayerName(women[rand], j);
                women.erase(women.begin() + rand);
                continue;
            }
            if(!men.empty())
            {
                unsigned int rand = std::rand()/((RAND_MAX + 1u) / men.size());  // Note: 1+rand()%6 is wrong!
                m_twoPlayersTeam[i].modifyPlayerName(men[rand], j);
                men.erase(men.begin() + rand);
            }
        }
    }
}

void ContestGenerate::displayTeams() const
{
    for(unsigned int i = 0; i < m_threePlayersTeamNumber;++i)
    {
        qDebug() << "\nTeam 3 Players:: number";
        qDebug() <<  m_threePlayersTeam[i].getTeamNumber();
        for(unsigned int j = 0; j < 3;++j)
        {
            qDebug() <<  QString(m_threePlayersTeam[i].getPlayerName(j).c_str());
        }

    }
    for(unsigned int i = 0; i < m_twoPlayersTeamNumber;++i)
    {
        qDebug() << "\nTeam 2 Players:: number";
        qDebug() <<  m_twoPlayersTeam[i].getTeamNumber();
        for(unsigned int j = 0; j < 2;++j)
        {
            qDebug() <<  QString(m_twoPlayersTeam[i].getPlayerName(j).c_str());
        }
    }
    //<< "\nTT3 players team:: " << threePlayersTeamNumber << "\n2 players team:: " << twoPlayersTeamNumber
}

void ContestGenerate::displayNames() const
{
    qDebug("man");

    for(unsigned int i = 0; i < m_stockPlayersWomen.size();++i)
    {
        qDebug(m_stockPlayersWomen[i].c_str());
    }
    qDebug("woman");

    for(unsigned int i = 0; i < m_stockPlayersMen.size();++i)
    {
        qDebug(m_stockPlayersMen[i].c_str());
    }
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
    if(m_DoubletNumber && m_ThreesomeNumber)
    {
        std::string doublet = "Doublettes : " + std::to_string(m_twoPlayersTeamNumber);
        std::string threeSome = "Triplettes : " + std::to_string(m_threePlayersTeamNumber);
        m_DoubletNumber->setText(QString(doublet.c_str()));
        m_ThreesomeNumber->setText(QString(threeSome.c_str()));
    }
}

void ContestGenerate::generateGlobalGames()
{
    if(m_gamesTab)
    {
        m_gamesTab->clear();
    }
    m_pdfGen.clear();

    if(m_teamBuildOption == MELEE)
    {
        generateTeam();
        generateMeleeGames();
    }
    else if(m_teamBuildOption == MELEE_MELEE)
    {
        for(unsigned int i = 1; i < m_gamesNumber; ++i)
        {
            generateTeam();
            setTeamsOpponents(0);
            m_pdfGen.push_back(PdfDocGeneration(m_gamesOpContainer, i));
            createNewTeamTab(i);
        }
    }
}

void ContestGenerate::generateMeleeGames()
{
    //displayTeams();
    for(unsigned int i = 1; i < m_gamesNumber;++i)
    {
        setTeamsOpponents(i);//set m_gamesOpContainer
        m_pdfGen.push_back(PdfDocGeneration(m_gamesOpContainer, i));
        createNewTeamTab(i);
    }
}

void ContestGenerate::createNewTeamTab(unsigned int gameNumber)
{
    QWidget *scrollAreaWidgetContents = new QWidget;
    scrollAreaWidgetContents->setLayout(new VersusTeams(m_gamesOpContainer));
    QScrollArea *scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setWidget(scrollAreaWidgetContents);
    scroll->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    m_gamesTab->addTab(scroll, QString(std::string("Team " + std::to_string(gameNumber)).c_str()));
//        m_gamesOpContainer.display();
    m_gamesOpContainer.clear();
}

void ContestGenerate::setTeamsOpponents(unsigned int gameNumber)
{
    if(m_threePlayersTeam.size() + m_twoPlayersTeam.size() % 2 == 1)//if error
    {
        return;
    }
    vectUi threeSomeMem, doubletMem;
    getVectNumberTeam(threeSomeMem, doubletMem);//get Number from existing team

    unsigned int iterationNumber = (m_threePlayersTeam.size() + m_twoPlayersTeam.size()) / 2;
    m_gamesOpContainer.clear();
    for(unsigned int i = 0; i < iterationNumber;++i)
    {
        unsigned int currentDoubletOpponent = 0, currentThreesomeOpponent = 0;
        if(! doubletMem.empty())
        {
            currentDoubletOpponent = (1 + gameNumber) % doubletMem.size();
        }
        if(! threeSomeMem.empty())
        {
            currentThreesomeOpponent = (1 + gameNumber) % threeSomeMem.size();
        }
        if(! doubletMem.empty())
        {
            if(! threeSomeMem.empty())
            {
                if(threeSomeMem.size() >= 2)
                {
                    m_gamesOpContainer.addGames(m_threePlayersTeam[threeSomeMem[0]],
                            m_threePlayersTeam[threeSomeMem[currentThreesomeOpponent]]);
                    threeSomeMem.erase(threeSomeMem.begin() + currentThreesomeOpponent);
                    threeSomeMem.erase(threeSomeMem.begin());
                }
                else
                {
                    m_gamesOpContainer.addGames(m_twoPlayersTeam[doubletMem[0]],
                            m_threePlayersTeam[threeSomeMem[currentThreesomeOpponent]]);
                    doubletMem.erase(doubletMem.begin());
                    threeSomeMem.erase(threeSomeMem.begin() + currentThreesomeOpponent);
                }
            }
            else//if m_threePlayersTeam finished
            {
                if(currentDoubletOpponent == 0)
                {
                    ++currentDoubletOpponent;
                }
                m_gamesOpContainer.addGames(m_twoPlayersTeam[doubletMem[0]],
                        m_twoPlayersTeam[doubletMem[currentDoubletOpponent]]);
                doubletMem.erase(doubletMem.begin() + currentDoubletOpponent);
                doubletMem.erase(doubletMem.begin());
            }
        }
//        else//if m_twoPlayersTeam finished
//        {
//            if(currentThreesomeOpponent == 0)
//            {
//                ++currentThreesomeOpponent;
//            }
//            m_gamesOpContainer.addGames(m_threePlayersTeam[threeSomeMem[0]],
//                                        m_threePlayersTeam[threeSomeMem[currentThreesomeOpponent]]);
//            threeSomeMem.erase(threeSomeMem.begin() + currentThreesomeOpponent);
//            threeSomeMem.erase(threeSomeMem.begin());
//        }
    }
}

void ContestGenerate::instanciateTeams(unsigned int threesomeNumber, unsigned int doubletNumber)
{
    for(unsigned int i = 0; i < threesomeNumber;++i)
    {
        m_threePlayersTeam.push_back(Team(true));
    }
    for(unsigned int i = 0; i < doubletNumber;++i)
    {
        m_twoPlayersTeam.push_back(Team(false));
    }
}

void ContestGenerate::getVectNumberTeam(vectUi &threeSome, vectUi &doublet) const
{
    if(! threeSome.empty())
    {
        threeSome.clear();
    }
    if(! doublet.empty())
    {
        doublet.clear();
    }
    for(unsigned int i = 0; i < m_threePlayersTeam.size(); ++i)
    {
        threeSome.push_back(i);
    }
    for(unsigned int i = 0; i < m_twoPlayersTeam.size(); ++i)
    {
        doublet.push_back(i);
    }
}

ContestGenerate::~ContestGenerate()
{
    delete ui;
}
