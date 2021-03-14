#include "sfo.h"

#include <QMessageBox>

#include "ui_sfo.h"

#include <QFile>
#include <QPixmap>
#include <QTextStream>
#include <QtDebug>
#include <QDir>
#include <QLineEdit>
#include <QVBoxLayout>
#include "createdir.h"
//#include <memory>

// Global Vars
QString selectedDrive;
QString year;
QString semester;
bool isLabSelected = false;
int labSubNo;
QVBoxLayout *vlayout = new QVBoxLayout;
QVector<QLineEdit*> lineEditHolder;
QString labSubNameHolder[5];


sfo::sfo(QWidget *parent) : QMainWindow(parent), ui(new Ui::sfo) {
    ui->setupUi(this);

    // Hiding the labsubname page back and next button as they are brute forced in a vert layout
    ui->back_4->hide();
    ui->next_4->hide();

    // Setting startup logo image
    QPixmap sfologo(":/res/logo/SFO_v2.ico");
    ui->sfologo->setPixmap(sfologo);


    ui->stackedWidget->setCurrentIndex(0);
    // Listing the drive letter in the combobox
    QDir dir;
    foreach (QFileInfo drive, dir.drives()){
            ui->driveslist->addItem(drive.absoluteFilePath());
    }

    listLabSubNo();
    ui->next_2->setDisabled(true);

    ui->labfoldername->setLayout(vlayout);
}

sfo::~sfo() { delete ui; }

void sfo::on_exit_clicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Quit?", "Are you sure?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::exit();
    }
}

void sfo::about(){
    QFile about(":/about/res/about/about.txt");

    if (!about.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "File is not open. ERROR !";
    }

    QTextStream readAbout(&about);
    QString aboutText = readAbout.readAll();
    QMessageBox::about(this, "About SFO", aboutText);
}

void sfo::listLabSubNo(){
    QDir dir;
    for (int i = 1; i < 6; i++) {
        ui->labsubno->addItem(QString::number(i));
    }
}

void sfo::on_about_clicked() {
    about();
}

void sfo::on_create_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void sfo::on_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void sfo::on_driveslist_currentTextChanged(const QString &selected)
{
    ui->selecteddrive->setText("Selected Drive is: "+selected);
    selectedDrive = selected;
}

void sfo::on_next_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void sfo::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void sfo::on_next_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void sfo::on_actionExit_triggered()
{
    QApplication::exit();
}

void sfo::on_back_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void sfo::on_checkBox_stateChanged(int arg1)
{
    ui->next_2->setDisabled(true);
    bool isInfoGiven = false;


    year = ui->year->text();
    qDebug()<<"Given Year-> "+year;

    semester = ui->semester->text();
    qDebug()<<"Given Semester-> "+semester;


    if(year=="" || semester==""){
        isInfoGiven=false;
    }
    else{
        isInfoGiven=true;
    }

    if (ui->labradio->isChecked()){
        isLabSelected = true;
        qDebug()<<"Selected -> Lab";
    }
    else{
        isLabSelected = false;
//        qDebug()<<"Selected -> None";
    }


    if((arg1==0 || arg1==2) && !isLabSelected && !isInfoGiven){
        ui->next_2->setDisabled(true);
    }
    else if (arg1==2 && isLabSelected && isInfoGiven){
        ui->next_2->setDisabled(false);
    }
}

void sfo::on_actionHome_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void sfo::on_actionAbout_SFO_triggered()
{
    about();
}

void sfo::on_next_3_clicked()
{
    labSubNo = ui->labsubno->currentIndex();
    labSubNo+=1;
    qDebug()<<"Selected number of Lab Subjects -> "+QString::number(labSubNo);

    createLineEdits();
    ui->stackedWidget->setCurrentIndex(4);
    ui->back_4->show();
    ui->next_4->show();
}

void sfo::on_back_4_clicked()
{
    ui->back_4->hide();
    ui->next_4->hide();
    ui->stackedWidget->setCurrentIndex(3);
}

void sfo::createLineEdits(){
  // Showing the line edits depending on the labsubno count
  for(int i = 0; i < labSubNo; i++){
    lineEditHolder.push_back(new QLineEdit());
  }


  for (int i = 0 ; i < lineEditHolder.size(); i++){
    vlayout->addWidget(lineEditHolder[i]);
  }
}

void sfo::takeLabSubName(){
  // Saving the input from the line edits
  for (int i = 0 ; i< lineEditHolder.size(); i++){
    labSubNameHolder[i] = lineEditHolder[i]->text();
  }
}
void sfo::on_next_4_clicked()
{
  takeLabSubName();
  for (int i = 0; i < lineEditHolder.size(); ++i) {
    qDebug()<<"Lab Sub no: "+QString::number(i+1)+" name is -> "+labSubNameHolder[i];
  }

  ui->back_4->hide();
  ui->next_4->hide();
  ui->stackedWidget->setCurrentIndex(5);
}

void sfo::on_back_5_clicked()
{

  ui->back_4->show();
  ui->next_4->show();
  ui->stackedWidget->setCurrentIndex(4);
}

void sfo::on_createLabs_clicked()
{
  Createdir *createdir = new Createdir;

  createdir->rootDirCreator(selectedDrive, year, semester);

}
