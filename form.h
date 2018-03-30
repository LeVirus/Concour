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
    static Form* m_FormInstance;
    Ui::Form *m_ui;
    QVBoxLayout* m_memListMan = nullptr;
    QVBoxLayout* m_memListWoman = nullptr;

private:
    bool checkExist(const QString &str, QVBoxLayout &memVbox)const;
    void setLayouts();
    void setScrolls();
public:
    explicit Form(QWidget *parent = 0);
    bool checkGlobalExist(const QString &str)const;

    void changePlayerLineGenderArray(PlayerLine *playerLine);
    static inline Form *getInstance(){return m_FormInstance;}
    ~Form();

private slots:
    void on_pushButton_clicked();
    void clearPlayerLines();

};

#endif // FORM_H
