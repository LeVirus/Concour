#ifndef TEAMLINE_H
#define TEAMLINE_H

#include <QHBoxLayout>

class QLabel;
class QPushButton;

class TeamLine : public QHBoxLayout
{
    Q_OBJECT
private:
    QLabel *m_label = nullptr;
    QPushButton *m_del = nullptr, *m_modif = nullptr;
    void setButtons();
    void linkButtons();
public:
    TeamLine(const QString &playerNames);
    ~TeamLine();
private slots:
    void delThis();
    void createModifyWindow();
};

#endif // TEAMLINE_H
