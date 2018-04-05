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

private:
    QLabel *m_MenTotal, *m_WomenTotal;
    QSpinBox *m_ThreePlayersTeam, *m_TwoPlayersTeam;
    unsigned int m_threePlayersTeam, m_twoPlayersTeam;
    const QVBoxLayout* m_manLayout, *m_womanLayout;
    unsigned int m_numberMan = 0, m_numberWoman = 0;
    Ui::ContestGenerate *ui;
private:
    bool setNumberContestTeam();
    bool linkWidgets();
    void updateUI();

public:
    explicit ContestGenerate(QWidget *parent = 0);
    bool updateCurrentContest(const QVBoxLayout *manLayout, const QVBoxLayout *womanLayout);
    ~ContestGenerate();
private slots:
    void updateTeam();
};

#endif // CONTESTGENERATE_H
