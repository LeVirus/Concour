#include "team.h"

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
