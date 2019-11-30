#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>

class Team
{
private:
    std::vector<std::string> m_vectPlayers;
    bool m_threesome;
    unsigned int m_teamNumber;
    static unsigned int m_cmpt;
public:
    Team(bool threesome);
    Team(const std::string &nameA, const std::string &nameB, const std::string &nameC);
    Team(const std::string &nameA, const std::string &nameB);
    size_t getPlayerNumber()const;
    inline bool isThreesome()const{return m_threesome;}
    inline unsigned int getTeamNumber()const{return m_teamNumber;}
    std::string getPlayerName(unsigned int index)const;
    void modifyPlayerName(const std::string &name, unsigned int index);
    static inline void static_reinitCmpt(){m_cmpt = 0;}
};

#endif // TEAM_H

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
