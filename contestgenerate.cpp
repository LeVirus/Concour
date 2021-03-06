#include "contestgenerate.h"
#include "ui_contestgenerate.h"
#include "meleemeleeform.h"
#include "team.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDebug>
#include <QSpinBox>
#include <QLabel>
#include <QWidget>
#include <QTabWidget>
#include <QScrollArea>
#include <QFileDialog>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <versusteams.h>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std::chrono_literals;

ContestGenerate::ContestGenerate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContestGenerate)
{
    ui->setupUi(this);
    if(! linkWidgets())
    {
        QMessageBox::warning(this, "Erreur", "Problème de liens.");
    }
    QPushButton* buttonGenerate = findChild<QPushButton*>("pushButton");

    if(buttonGenerate)
    {
        QObject::connect(buttonGenerate, SIGNAL(clicked()), this, SLOT(pdfGeneration()));
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

bool ContestGenerate::updateCurrentContestMeleeMelee(const QVBoxLayout* manLayout, const QVBoxLayout* womanLayout)
{
    m_teamBuildOption = TeamGenerationMode::MELEE_MELEE;
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

void ContestGenerate::updateContestPresetTeam(const std::vector<vectString> &vectTeam)
{
    m_vectPresetTeam.clear();
    m_vectPresetTeam.reserve(vectTeam.size());
    for(uint32_t i = 0; i < vectTeam.size(); ++i)
    {
        if(vectTeam[i].size() == 2)
        {
            m_vectPresetTeam.emplace_back(Team(vectTeam[i][0], vectTeam[i][1]));
        }
        else if(vectTeam[i].size() == 3)
        {
            m_vectPresetTeam.emplace_back(Team(vectTeam[i][0],
                                          vectTeam[i][1],
                                          vectTeam[i][2]));
        }
    }
}

bool ContestGenerate::setNumberContestTeam()
{
    uint32_t totalPlayers = m_manLayout->count() + m_womanLayout->count();
    if(totalPlayers < 5)
    {
        QMessageBox::warning(this, "Erreur", "Le Nombre de joueur est insuffisant. Minimum 5.");
        return false;
    }
    uint32_t threePlayersTeamNumberModulo = totalPlayers % 3;
    m_threePlayersTeamNumber = totalPlayers / 3;
    m_twoPlayersTeamNumber = threePlayersTeamNumberModulo / 2;
    //set a pair number of team
    do
    {
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
    return true;
}

void ContestGenerate::setTeamBuildOption(uint32_t gamesNumber,
                                         TeamGenerationMode mode)
{
    m_teamBuildOption = mode;
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

void ContestGenerate::generateTeamMeleeMelee()
{
    if(m_stockPlayersMen.empty() && m_stockPlayersWomen.empty())
    {
        return;
    }
    Team::static_reinitCmpt();
    m_threePlayersTeam.clear();
    m_twoPlayersTeam.clear();
    instanciateTeams(m_threePlayersTeamNumber, m_twoPlayersTeamNumber);

    vectString vectMenNames = m_stockPlayersMen,
               vectWomenNames = m_stockPlayersWomen;
    generateThreePlayersTeam(vectMenNames, vectWomenNames);
    generateTwoPlayersTeam(vectMenNames, vectWomenNames);
}

void ContestGenerate::generateThreePlayersTeam(vectString &men, vectString &women)
{
    for(uint32_t i = 0; i < m_threePlayersTeamNumber; ++i)
    {
        for(uint32_t j = 0; j < 3; ++j)
        {
            std::this_thread::sleep_for(10ms);
            if( (j == 0 && !women.empty()) || men.empty())
            {
                uint32_t rand = std::rand() % women.size();
                m_threePlayersTeam[i].modifyPlayerName(women[rand], j);
                women.erase(women.begin() + rand);
                continue;
            }
            if(!men.empty())
            {
                uint32_t rand = std::rand() % men.size();
                m_threePlayersTeam[i].modifyPlayerName(men[rand], j);
                men.erase(men.begin() + rand);
            }
        }
    }
}

void ContestGenerate::generateTwoPlayersTeam(vectString &men, vectString &women)
{
    for(uint32_t i = 0; i < m_twoPlayersTeamNumber; ++i)
    {
        for(uint32_t j = 0; j < 2; ++j)
        {
            if( (j == 0 && !women.empty()) || men.empty())
            {
                uint32_t rand = std::rand() % women.size();
                m_twoPlayersTeam[i].modifyPlayerName(women[rand], j);
                women.erase(women.begin() + rand);
                continue;
            }
            if(!men.empty())
            {
                uint32_t rand = std::rand() % men.size();
                m_twoPlayersTeam[i].modifyPlayerName(men[rand], j);
                men.erase(men.begin() + rand);
            }
        }
    }
}

void ContestGenerate::displayTeams() const
{
    for(uint32_t i = 0; i < m_threePlayersTeamNumber;++i)
    {
        qDebug() << "\nTeam 3 Players:: number";
        qDebug() <<  m_threePlayersTeam[i].getTeamNumber();
        for(uint32_t j = 0; j < 3;++j)
        {
            qDebug() <<  QString(m_threePlayersTeam[i].getPlayerName(j).c_str());
        }

    }
    for(uint32_t i = 0; i < m_twoPlayersTeamNumber;++i)
    {
        qDebug() << "\nTeam 2 Players:: number";
        qDebug() <<  m_twoPlayersTeam[i].getTeamNumber();
        for(uint32_t j = 0; j < 2;++j)
        {
            qDebug() <<  QString(m_twoPlayersTeam[i].getPlayerName(j).c_str());
        }
    }
}

void ContestGenerate::displayNames() const
{
    qDebug("man");

    for(uint32_t i = 0; i < m_stockPlayersWomen.size();++i)
    {
        qDebug(m_stockPlayersWomen[i].c_str());
    }
    qDebug("woman");

    for(uint32_t i = 0; i < m_stockPlayersMen.size();++i)
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
    m_vectGamesOpContainer.clear();
    m_vectGamesOpContainer.reserve(m_gamesNumber - 1);
    std::srand(std::time(nullptr));
    for(uint32_t i = 1; i < m_gamesNumber; ++i)
    {
        if(m_teamBuildOption == TeamGenerationMode::MELEE_MELEE)
        {
            generateTeamMeleeMelee();
            setTeamsOpponentsMeleeMelee(i);
        }
        //preset
        else
        {
            setTeamsOpponentsPresetTeam(i);
        }
        createNewTeamTab(i);
    }
}

void ContestGenerate::createNewTeamTab(uint32_t gameNumber)
{
    QWidget *scrollAreaWidgetContents = new QWidget(this);
    scrollAreaWidgetContents->setLayout(new VersusTeams(m_vectGamesOpContainer.back()));
    QScrollArea *scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setWidget(scrollAreaWidgetContents);
    scroll->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    m_gamesTab->addTab(scroll, QString(std::string("Team " + std::to_string(gameNumber)).c_str()));
}

void ContestGenerate::setTeamsOpponentsMeleeMelee(uint32_t gameNumber)
{
    if(m_threePlayersTeam.size() + m_twoPlayersTeam.size() % 2 == 1)//if error
    {
        return;
    }
    vectUi threeSomeMem, doubletMem;
    getVectNumberTeam(threeSomeMem, doubletMem);//get Number from existing team
    uint32_t iterationNumber = (m_threePlayersTeam.size() + m_twoPlayersTeam.size()) / 2;
    m_vectGamesOpContainer.push_back(GamesOpponentsContainer());
    GamesOpponentsContainer &currentGameContainer = m_vectGamesOpContainer.back();
    for(uint32_t i = 0; i < iterationNumber; ++i)
    {
        std::this_thread::sleep_for(50ms);
        uint32_t currentDoubletOpponent = 0, currentThreesomeOpponent = 0;
        if(doubletMem.size() > 1)
        {
            currentDoubletOpponent = (std::rand() % (doubletMem.size()));
        }
        if(! threeSomeMem.empty())
        {
            //(1 + gameNumber) % threeSomeMem.size();
            if(threeSomeMem.size() > 1)
            {
                currentThreesomeOpponent = (std::rand() % (threeSomeMem.size()));
            }
            assert(currentThreesomeOpponent < threeSomeMem.size());
            if(threeSomeMem.size() >= 2)
            {
                if(currentThreesomeOpponent == 0)
                {
                    ++currentThreesomeOpponent;
                }
                uint32_t otherThreesome = getOtherRand(threeSomeMem.size(), currentThreesomeOpponent);
                currentGameContainer.addGames(m_threePlayersTeam[threeSomeMem[otherThreesome]],
                        m_threePlayersTeam[threeSomeMem[currentThreesomeOpponent]]);
                if(otherThreesome > currentThreesomeOpponent)
                {
                    std::swap(currentThreesomeOpponent, otherThreesome);
                }
                threeSomeMem.erase(threeSomeMem.begin() + currentThreesomeOpponent);
                threeSomeMem.erase(threeSomeMem.begin() + otherThreesome);
            }
            //threeSomeMem :: 1 item
            else
            {
                currentGameContainer.addGames(m_twoPlayersTeam[doubletMem[currentDoubletOpponent]],
                        m_threePlayersTeam[threeSomeMem[0]]);
                doubletMem.erase(doubletMem.begin() + currentDoubletOpponent);
                threeSomeMem.erase(threeSomeMem.begin());
            }
        }
        else//if m_threePlayersTeam finished
        {
            if(currentDoubletOpponent == 0)
            {
                ++currentDoubletOpponent;
            }
            uint32_t otherDoublet = getOtherRand(doubletMem.size(), currentDoubletOpponent);
            currentGameContainer.addGames(m_twoPlayersTeam[doubletMem[otherDoublet]],
                    m_twoPlayersTeam[doubletMem[currentDoubletOpponent]]);
            if(otherDoublet > currentDoubletOpponent)
            {
                std::swap(currentDoubletOpponent, otherDoublet);
            }
            doubletMem.erase(doubletMem.begin() + currentDoubletOpponent);
            doubletMem.erase(doubletMem.begin() + otherDoublet);
        }
    }
}

uint32_t ContestGenerate::getOtherRand(uint32_t arraySize, uint32_t exclude)
{
    assert(arraySize);
    uint32_t currentRandom;
    do
    {
    currentRandom = (std::rand() % arraySize);
    }while(currentRandom == exclude);
    return currentRandom;
}

void ContestGenerate::setTeamsOpponentsPresetTeam(uint32_t gameNumber)
{
    m_vectGamesOpContainer.emplace_back(GamesOpponentsContainer());
    GamesOpponentsContainer &opContainer = m_vectGamesOpContainer.back();
    vectUi vectTeamNum(m_vectPresetTeam.size());
    std::iota(vectTeamNum.begin(), vectTeamNum.end(), 0);
    //in case of odd number one team doesn't play
    while(vectTeamNum.size() >= 2)
    {
        uint32_t i = (gameNumber < vectTeamNum.size()) ?
                    gameNumber : gameNumber % vectTeamNum.size();
        if(i == 0)
        {
            ++i;
        }
        opContainer.addGames(m_vectPresetTeam[vectTeamNum[0]],
                             m_vectPresetTeam[vectTeamNum[i]]);
        assert(vectTeamNum.size() > i);
        vectTeamNum.erase(vectTeamNum.begin() + i);
        vectTeamNum.erase(vectTeamNum.begin());
    }
    //set resting team play on the other round
    if(!vectTeamNum.empty())
    {
        assert(vectTeamNum[0] < m_vectPresetTeam.size());
        std::swap(m_vectPresetTeam[0], m_vectPresetTeam[vectTeamNum[0]]);
    }
}

void ContestGenerate::instanciateTeams(uint32_t threesomeNumber, uint32_t doubletNumber)
{
    m_threePlayersTeam.reserve(threesomeNumber);
    m_twoPlayersTeam.reserve(doubletNumber);
    for(uint32_t i = 0; i < threesomeNumber; ++i)
    {
        m_threePlayersTeam.emplace_back(Team(true));
    }
    for(uint32_t i = 0; i < doubletNumber; ++i)
    {
        m_twoPlayersTeam.emplace_back(Team(false));
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
    for(uint32_t i = 0; i < m_threePlayersTeam.size(); ++i)
    {
        threeSome.push_back(i);
    }
    for(uint32_t i = 0; i < m_twoPlayersTeam.size(); ++i)
    {
        doublet.push_back(i);
    }
}

void ContestGenerate::pdfGeneration()
{
    QString path = QFileDialog::getExistingDirectory();
    if(!path.isEmpty()&& !path.isNull())
    {
        path += m_slash;
        PdfDocGeneration::setSaveDirectory(path);
        for(size_t i = 0; i < m_vectGamesOpContainer.size(); ++i)
        {
            PdfDocGeneration::updateDocFromGames(m_vectGamesOpContainer[i], i + 1);
        }
        QMessageBox::information(this, "Info", "Fichiers PDF générés");
    }
}

ContestGenerate::~ContestGenerate()
{
    delete ui;
}

/**
 * Petanque Competition Management Program
 * Copyright (C) 2018 Cyril Charbonneau
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * his program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
