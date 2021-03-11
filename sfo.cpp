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
}

sfo::~sfo() { delete ui; }

void sfo::on_exit_clicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Quit?", "Are you sure?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::exit();
    }
}

void sfo::on_about_clicked() {
    QFile about(":/about/res/about/about.txt");

    if (!about.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "File is not open. ERROR !";
    }

    QTextStream readAbout(&about);
    QString aboutText = readAbout.readAll();
    QMessageBox::about(this, "About SFO", aboutText);
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
