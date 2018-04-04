#ifndef CONTESTGENERATE_H
#define CONTESTGENERATE_H

#include <QDialog>

namespace Ui {
class ContestGenerate;
}

class ContestGenerate : public QDialog
{
    Q_OBJECT

public:
    explicit ContestGenerate(QWidget *parent = 0);
    ~ContestGenerate();

private:
    unsigned int m_numberMan = 0, m_numberWoman = 0;
    Ui::ContestGenerate *ui;
};

#endif // CONTESTGENERATE_H
