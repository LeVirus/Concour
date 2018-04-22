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

const t_vectPairTeam &GamesOpponentsContainer::getGames() const
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
            qDebug() << "Team num :: " << team->getTeamNumber();

            for(unsigned int h = 0; h < playersNumber; ++h)
            {
                qDebug() << "Player :: " << QString(team->getPlayerName(h).c_str());
            }
        }
    }
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
