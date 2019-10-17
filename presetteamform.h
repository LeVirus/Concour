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
    void displayError(const std::string &message)const;
    void setLayouts();
    void clearLineEdit();
    bool checkExistingPlayers(const std::string &strA,
                              const std::string &strB,
                              const std::string &strC) const;
    bool checkEqualsEntries(const std::string &strA,
                            const std::string &strB,
                            const std::string &strC) const;
private slots:
    void on_pushButton_clicked();

private:
    Ui::PresetTeamForm *ui;
    QLineEdit *playerA, *playerB, *playerC;
    vectTeam_t m_vectTeam;
    std::vector<std::string> m_vectPlayers;
    QVBoxLayout *m_TeamLayout;
};

#endif // PRESETTEAMFORM_H
