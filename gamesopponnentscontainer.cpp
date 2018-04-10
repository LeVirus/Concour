#include "gamesopponnentscontainer.h"
#include "team.h"
#include <QDebug>
#include <QString>

GamesOpponentsContainer::GamesOpponentsContainer()
{

}

void GamesOpponentsContainer::clear()
{
    m_gamesOpponents.clear();
}

void GamesOpponentsContainer::addGames(const Team &a, const Team &b)
{
    m_gamesOpponents.push_back({a, b});
}

const t_vectPairUIBool &GamesOpponentsContainer::getGames() const
{
    return m_gamesOpponents;
}

void GamesOpponentsContainer::display() const
{
    for(unsigned int i = 0; i < m_gamesOpponents.size(); ++i)
    {
        for(unsigned int j = 0; j < 2; ++j)
        {
            const Team *team = nullptr;
            if(j == 0)
            {
                team = &m_gamesOpponents[i].first;
            }
            else
            {
                team = &m_gamesOpponents[i].second;
            }
            unsigned int playersNumber;
            if(team->isThreesome())
            {
                playersNumber = 3;
            }
            else
            {
                playersNumber = 2;
            }
            qDebug() << "\nTeam 3 Players:: number";

            qDebug() << "Team num :: " << team->getTeamNumber();

            for(unsigned int h = 0; h < playersNumber; ++h)
            {
                qDebug() << "Player :: " << QString(team->getPlayerName(h).c_str());
            }
        }
    }
}
