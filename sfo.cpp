#include "sfo.h"

#include <QMessageBox>

#include "ui_sfo.h"

#include <QFile>
#include <QTextStream>
#include <QtDebug>

sfo::sfo(QWidget *parent) : QMainWindow(parent), ui(new Ui::sfo) {
    ui->setupUi(this);
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
