#ifndef FORM_H
#define FORM_H

#include "playerline.h"

#include <QWidget>
#include <memory>

class QVBoxLayout;

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
private:
    Ui::Form *m_ui;
    QVBoxLayout* m_memListMan = nullptr;
    QVBoxLayout* m_memListWoman = nullptr;

private:
    bool checkExist(const QString &str, QVBoxLayout &memVbox);
    void setLayouts();
    void setScrolls();
public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private slots:
    void on_pushButton_clicked();


};

#endif // FORM_H
