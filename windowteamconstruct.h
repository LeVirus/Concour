#ifndef WINDOWTEAMCONSTRUCT_H
#define WINDOWTEAMCONSTRUCT_H

#include <QDialog>



namespace Ui {
class WindowTeamConstruct;
}

class WindowTeamConstruct : public QDialog
{
    Q_OBJECT

public:
    explicit WindowTeamConstruct(QWidget *parent = 0);
    ~WindowTeamConstruct();

private:
    Ui::WindowTeamConstruct *ui;
private:
    void linkButtons();
private slots:
    void launchGenerationWindow(unsigned int option);

};

#endif // WINDOWTEAMCONSTRUCT_H
