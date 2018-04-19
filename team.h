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
    size_t getPlayerNumber()const;
    inline bool isThreesome()const{return m_threesome;}
    inline unsigned int getTeamNumber()const{return m_teamNumber;}
    std::string getPlayerName(unsigned int index)const;
    void modifyPlayerName(const std::string &name, unsigned int index);
    static inline void static_reinitCmpt(){m_cmpt = 0;}
};

#endif // TEAM_H
