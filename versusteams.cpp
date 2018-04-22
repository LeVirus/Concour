#include "versusteams.h"
#include "gamesopponnentscontainer.h"
#include "team.h"
#include <string>
#include <QLabel>


VersusTeams::VersusTeams(const GamesOpponentsContainer &gamesOpp, QWidget *parent):QHBoxLayout(parent)
{
    m_firstTeams = new QVBoxLayout();
    addLayout(m_firstTeams);
    m_secondTeams = new QVBoxLayout();
    addLayout(m_secondTeams);
    setVersusUI(gamesOpp);
}

void VersusTeams::setVersusUI(const GamesOpponentsContainer &gamesOpp)
{
    const t_vectPairTeam &m_gamesOpponents = gamesOpp.getGames();
    for(size_t i = 0; i < m_gamesOpponents.size(); ++i)
    {
        for(size_t k = 0; k < 2; ++k)
        {
            std::string mem, current;
            size_t teamSize;
            if(k == 0)
            {
                teamSize = m_gamesOpponents[i].first.getPlayerNumber();
            }
            else
            {
                teamSize = m_gamesOpponents[i].second.getPlayerNumber();
            }
            for(size_t j = 0; j < teamSize; ++j)
            {
                if(k == 0)
                {
                    current = m_gamesOpponents[i].first.getPlayerName(j);
                }
                else
                {
                    current = m_gamesOpponents[i].second.getPlayerName(j);
                }

                if(current.empty())
                {
                    continue;
                }
                if(j != 0)
                {
                    mem += '\n';
                }
                mem += current;
            }
            if(k == 0)
            {
                m_firstTeams->addWidget(new QLabel(mem.c_str()));
            }
            else
            {
                m_secondTeams->addWidget(new QLabel(mem.c_str()));
            }
        }
    }
}

VersusTeams::~VersusTeams()
{
    if(m_firstTeams)delete m_firstTeams;
    if(m_secondTeams)delete m_secondTeams;
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
