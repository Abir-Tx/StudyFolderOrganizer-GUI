#include "sfo.h"

#include <QMessageBox>

#include "ui_sfo.h"

#include <QFile>
#include <QPixmap>
#include <QTextStream>
#include <QtDebug>
#include <QDir>

// Global Vars
QString selectedDrive;
QString year;
QString semester;
bool isLabSelected = false;



sfo::sfo(QWidget *parent) : QMainWindow(parent), ui(new Ui::sfo) {
    ui->setupUi(this);
    QPixmap sfologo(":/res/logo/SFO_v2.ico");
    ui->sfologo->setPixmap(sfologo);
    ui->stackedWidget->setCurrentIndex(0);

    // Listing the drive letter in the combobox
    QDir dir;
    foreach (QFileInfo drive, dir.drives()){
            ui->driveslist->addItem(drive.absoluteFilePath());
    }

        ui->next_2->setDisabled(true);
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
