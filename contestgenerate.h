#ifndef CONTESTGENERATE_H
#define CONTESTGENERATE_H

#include <QDialog>

class QVBoxLayout;
class QLabel;
class QSpinBox;
namespace Ui {
class ContestGenerate;
}

enum
{
    MELEE, MELEE_MELEE, MANUAL
};

class ContestGenerate : public QDialog
{
    Q_OBJECT

private:
    QLabel *m_MenTotal, *m_WomenTotal, *m_DoubletNumber, *m_ThreesomeNumber;
    unsigned int m_threePlayersTeam, m_twoPlayersTeam;
    const QVBoxLayout* m_manLayout, *m_womanLayout;
    unsigned int m_numberMan = 0, m_numberWoman = 0;
    Ui::ContestGenerate *ui;
    unsigned int m_teamBuildOption = MELEE;
private:
    bool setNumberContestTeam();
    bool setNumberContestTeamForDefinedThreesome();
    bool linkWidgets();
    void updateUI();

public:
    explicit ContestGenerate(QWidget *parent = 0);
    void setTeamBuildOption(unsigned int option);

    bool updateCurrentContest(const QVBoxLayout *manLayout, const QVBoxLayout *womanLayout);
    ~ContestGenerate();
};

#endif // CONTESTGENERATE_H
