#ifndef TEAMLINE_H
#define TEAMLINE_H

#include <QHBoxLayout>
#include <QScrollArea>

class QLabel;
class QPushButton;
class PresetTeamForm;

class TeamLine : public QHBoxLayout
{
    Q_OBJECT
private:
    QLabel *m_label = nullptr;
    QPushButton *m_del = nullptr, *m_modif = nullptr;
    QScrollArea m_scroll;
    PresetTeamForm &m_memPresetTeamForm;
    std::string m_playerA, m_playerB, m_playerC;
    bool m_ThreePlayer;
private:
    void setButtons();
    void linkButtons();
public:
    TeamLine(PresetTeamForm &memPresetTeamForm, const std::string &playerA,
             const std::string &playerB, const std::string &playerC = "");
    inline const std::string &getPlayerA()const{return m_playerA;}
    inline const std::string &getPlayerB()const{return m_playerB;}
    inline const std::string &getPlayerC()const{return m_playerC;}
    inline bool threePlayers()const{return m_ThreePlayer;}
    PresetTeamForm &getPresetTeamForm(){return m_memPresetTeamForm;}
    bool checkEntries(const std::string &playerA,
                      const std::string &playerB,
                      const std::string &playerC);
    void setPlayers(const std::string &playerA,
                    const std::string &playerB,
                    const std::string &playerC);
    ~TeamLine();
private slots:
    void delThis();
    void createModifyWindow();
};

#endif // TEAMLINE_H
