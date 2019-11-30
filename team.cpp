#include "team.h"
#include <QDebug>
#include <cassert>

unsigned int Team::m_cmpt = 0;

Team::Team(bool threesome):m_threesome(threesome)
{
    m_teamNumber = m_cmpt;
    ++m_cmpt;
    if(m_threesome)
    {
        m_vectPlayers.resize(3);
    }
    else
    {
        m_vectPlayers.resize(2);
    }
}

Team::Team(const std::string &nameA,
           const std::string &nameB,
           const std::string &nameC)
{
    m_teamNumber = m_cmpt;
    ++m_cmpt;
    m_vectPlayers.reserve(3);
    m_vectPlayers.emplace_back(nameA);
    m_vectPlayers.emplace_back(nameB);
    m_vectPlayers.emplace_back(nameC);
    m_threesome = true;
}

Team::Team(const std::string &nameA, const std::string &nameB)
{
    m_teamNumber = m_cmpt;
    ++m_cmpt;
    m_vectPlayers.reserve(2);
    m_vectPlayers.emplace_back(nameA);
    m_vectPlayers.emplace_back(nameB);
    m_threesome = false;
}

size_t Team::getPlayerNumber() const
{
    return m_vectPlayers.size();
}

void Team::modifyPlayerName(const std::string &name, unsigned int index)
{
    if(index < m_vectPlayers.size())
    {
        m_vectPlayers[index] = name;
    }
}

std::string Team::getPlayerName(unsigned int index)const
{
    if(!m_vectPlayers.empty() && index < m_vectPlayers.size())
    {
        return m_vectPlayers[index];
    }
    return "";
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
