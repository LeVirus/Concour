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
    void setButtons();
    void linkButtons();
private:
    PresetTeamForm &m_memPresetTeamForm;
    std::string m_playerA, m_playerB, m_playerC;
public:
    TeamLine(PresetTeamForm &memPresetTeamForm, const std::string &playerA,
             const std::string &playerB, const std::string &playerC = "");
    ~TeamLine();
private slots:
    void delThis();
    void createModifyWindow();
};

#endif // TEAMLINE_H
