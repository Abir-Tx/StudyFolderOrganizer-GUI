#include "sfo.h"
#include "ui_sfo.h"

sfo::sfo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sfo)
{
    ui->setupUi(this);
}

sfo::~sfo()
{
    delete ui;
}

