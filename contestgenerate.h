#ifndef CONTESTGENERATE_H
#define CONTESTGENERATE_H

#include <QDialog>

class QVBoxLayout;
class QLabel;
class QSpinBox;
namespace Ui {
class ContestGenerate;
}

class ContestGenerate : public QDialog
{
    Q_OBJECT

public:
    explicit ContestGenerate(QWidget *parent = 0);
    bool updateCurrentContest(const QVBoxLayout *manLayout, const QVBoxLayout *womanLayout);
    ~ContestGenerate();

private:
    QLabel *m_MenTotal, *m_WomenTotal;
    QSpinBox *m_ThreePlayersTeam, *m_TwoPlayersTeam;
    unsigned int m_threePlayersTeam, m_twoPlayersTeam;
    const QVBoxLayout* m_manLayout, *m_womanLayout;
    bool setNumberContestTeam(unsigned int totalPlayers);
    bool linkWidgets();
    void updateUI();
    unsigned int m_numberMan = 0, m_numberWoman = 0;
    Ui::ContestGenerate *ui;
};

#endif // CONTESTGENERATE_H
