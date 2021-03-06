#ifndef SFO_H
#define SFO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class sfo;
}
QT_END_NAMESPACE

class sfo : public QMainWindow {
  Q_OBJECT

public:
  sfo(QWidget *parent = nullptr);
  void about();
  void listLabSubNo();
  void takeLabSubName();
  void createLineEdits();
  ~sfo();

private slots:
  void on_exit_clicked();

  void on_about_clicked();

  void on_create_clicked();

  void on_pushButton_clicked();

  void on_back_clicked();

  void on_driveslist_currentTextChanged(const QString &arg1);

  void on_next_clicked();

  void on_next_2_clicked();

  void on_actionExit_triggered();

  void on_back_3_clicked();

  void on_checkBox_stateChanged(int arg1);

  void on_actionHome_triggered();

  void on_actionAbout_SFO_triggered();

  void on_next_3_clicked();

  void on_back_4_clicked();

  void on_next_4_clicked();

  void on_back_5_clicked();

  void on_createLabs_clicked();

  void on_actionFeedback_triggered();

  void on_pushButton_2_clicked();

  void on_next_5_clicked();

  void on_delete_2_clicked();

private:
  Ui::sfo *ui;
};
#endif // SFO_H
