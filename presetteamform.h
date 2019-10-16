#ifndef PRESETTEAMFORM_H
#define PRESETTEAMFORM_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <tuple>
#include <string>

class QVBoxLayout;
using vectTeam_t = std::vector<std::tuple<std::string, std::string, std::string>>;

namespace Ui {
class PresetTeamForm;
}

class PresetTeamForm : public QDialog
{
    Q_OBJECT

public:
    explicit PresetTeamForm(QWidget *parent = 0);
    ~PresetTeamForm();
private:
    void linkUIElement();
    void displayError();
    void setLayouts();
    void clearLineEdit();
private slots:
    void on_pushButton_clicked();

private:
    Ui::PresetTeamForm *ui;
    QLineEdit *playerA, *playerB, *playerC;
    vectTeam_t m_vectTeam;
    QVBoxLayout *m_TeamLayout;

};

#endif // PRESETTEAMFORM_H
