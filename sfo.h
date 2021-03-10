#ifndef SFO_H
#define SFO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class sfo; }
QT_END_NAMESPACE

class sfo : public QMainWindow
{
    Q_OBJECT

public:
    sfo(QWidget *parent = nullptr);
    ~sfo();

private:
    Ui::sfo *ui;
};
#endif // SFO_H
