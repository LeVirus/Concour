#ifndef PRESETTEAMFORM_H
#define PRESETTEAMFORM_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <tuple>
#include <string>

class QVBoxLayout;

using vectStr_t = std::vector<std::string>;
using itStrVect_t = std::vector<vectStr_t>::iterator;
using cstItStrVect_t = std::vector<vectStr_t>::const_iterator;

namespace Ui
{
class PresetTeamForm;
}

class PresetTeamForm : public QDialog
{
    Q_OBJECT

public:
    explicit PresetTeamForm(QWidget *parent = 0);
    bool delTeam(const std::string &playerA,
                 const std::string &playerB,
                 const std::string &playerC);
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
    std::vector<std::vector<std::string>> m_vectPlayers;
    QVBoxLayout *m_TeamLayout;
};

#endif // PRESETTEAMFORM_H
