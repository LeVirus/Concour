#ifndef MODTEAM_H
#define MODTEAM_H

#include <QDialog>

namespace Ui {
class ModTeam;
}

class ModTeam : public QDialog
{
    Q_OBJECT

public:
    explicit ModTeam(QWidget *parent = 0);
    ~ModTeam();

private:
    Ui::ModTeam *ui;
};

#endif // MODTEAM_H
