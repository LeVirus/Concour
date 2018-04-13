#ifndef WINDOWTEAMCONSTRUCT_H
#define WINDOWTEAMCONSTRUCT_H

#include <QDialog>



namespace Ui {
class WindowTeamConstruct;
}
class QRadioButton;
class QSpinBox;

class WindowTeamConstruct : public QDialog
{
    Q_OBJECT

public:
    explicit WindowTeamConstruct(QWidget *parent = 0);
    ~WindowTeamConstruct();

private:
    Ui::WindowTeamConstruct *ui;
    QRadioButton *m_radMelee = nullptr,
                *m_radMeleeMelee = nullptr;
    QSpinBox * m_spinNumberGames = nullptr;
private:
    void linkButtons();
    void linkRadio();
private slots:
    void launchGenerationWindow();
    void cancel();

};

#endif // WINDOWTEAMCONSTRUCT_H
