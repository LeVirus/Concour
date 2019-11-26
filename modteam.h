#ifndef MODTEAM_H
#define MODTEAM_H

#include <QDialog>

class QLineEdit;
class TeamLine;
class QLabel;

namespace Ui {
class ModTeam;
}

class ModTeam : public QDialog
{
    Q_OBJECT
public:
    explicit ModTeam(TeamLine &teamLine, QWidget *parent = 0);
    ~ModTeam();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    void initForm();
    void linkFormWidgets();
private:
    Ui::ModTeam *ui;
    TeamLine &m_teamLine;
    QLineEdit *m_linePlayerA, *m_linePlayerB, *m_linePlayerC;
    QPushButton *m_buttonCancel, *m_buttonOk;
    QLabel *m_labelPlayerC = nullptr;
    std::string m_oldPlayerA, m_oldPlayerB, m_oldPlayerC;
};

#endif // MODTEAM_H
