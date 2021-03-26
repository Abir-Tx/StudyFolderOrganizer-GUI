#include "sfo.h"

#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QLineEdit>
#include <QMessageBox>
#include <QPixmap>
#include <QProcess>
#include <QTextStream>
#include <QUrl>
#include <QVBoxLayout>
#include <QtDebug>

#include "createdir.h"
#include "ui_sfo.h"
//#include <memory>

// Global Vars
QString selectedDrive;
QString year;
QString semester;
bool isLabSelected = false;
bool isTheorySelected = false;
int labSubNo;
QVBoxLayout *vlayout = new QVBoxLayout;
QVector<QLineEdit *> lineEditHolder;
QString subNameHolder[5];
bool isDirCreated = false;

sfo::sfo(QWidget *parent) : QMainWindow(parent), ui(new Ui::sfo) {
  ui->setupUi(this);

  // Hiding the labsubname page back and next button as they are brute forced in
  // a vert layout
  ui->back_4->hide();
  ui->next_4->hide();

  // Setting startup logo image
  QPixmap sfologo(":/res/logo/SFO_v2.ico");
  ui->sfologo->setPixmap(sfologo);

  ui->stackedWidget->setCurrentIndex(0);
  // Listing the drive letter in the combobox
  QDir dir;
  foreach (QFileInfo drive, dir.drives()) {
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

void sfo::about() {
  QFile about(":/about/res/about/about.txt");

  if (!about.open(QFile::ReadOnly | QFile::Text)) {
    qDebug() << "File is not open. ERROR !";
  }

  QTextStream readAbout(&about);
  QString aboutText = readAbout.readAll();
  QMessageBox::about(this, "About SFO", aboutText);
}

void sfo::listLabSubNo() {
  QDir dir;
  for (int i = 1; i < 6; i++) {
    ui->labsubno->addItem(QString::number(i));
  }
}

void sfo::on_about_clicked() { about(); }

void sfo::on_create_clicked() { ui->stackedWidget->setCurrentIndex(1); }

void sfo::on_back_clicked() { ui->stackedWidget->setCurrentIndex(0); }

void sfo::on_driveslist_currentTextChanged(const QString &selected) {
  ui->selecteddrive->setText("Selected Drive is: " + selected);
  selectedDrive = selected;
}

void sfo::on_next_clicked() {
  ui->stackedWidget->setCurrentIndex(2);

  // Show debug & user feedback message about selected drive
  QString selectedDriveMessage = "Selected Drive -> " + selectedDrive;
  qDebug() << selectedDriveMessage;
  ui->statusbar->showMessage(selectedDriveMessage);

  // Set the year and semester line edits validator to take only integeres
  // To limit the input number range use the second constractor of the
  // QIntValidator
  QIntValidator *yearSemValidator = new QIntValidator(this);
  ui->year->setValidator(yearSemValidator);
  ui->semester->setValidator(yearSemValidator);
}

void sfo::on_pushButton_clicked() { ui->stackedWidget->setCurrentIndex(1); }

void sfo::on_next_2_clicked() {
  if (isLabSelected)
    ui->labsubnolabel->setText("How many Lab Subjects have you got");
  if (isTheorySelected)
    ui->labsubnolabel->setText("How many Theory Subjects have you got");
  else
    ui->labsubnolabel->setText("How many Subjects have you got");

  ui->stackedWidget->setCurrentIndex(3);
}

void sfo::on_actionExit_triggered() { QApplication::exit(); }

void sfo::on_back_3_clicked() { ui->stackedWidget->setCurrentIndex(2); }

void sfo::on_checkBox_stateChanged(int arg1) {
  ui->next_2->setDisabled(true);
  bool isInfoGiven = false;

  year = ui->year->text();
  qDebug() << "Given Year-> " + year;

  semester = ui->semester->text();
  qDebug() << "Given Semester-> " + semester;

  if (year == "" || semester == "") {
    isInfoGiven = false;
  } else {
    isInfoGiven = true;
  }

  // Checking if lab radio button is selected or not
  if (ui->labradio->isChecked()) {
    isLabSelected = true;
    qDebug() << "Selected -> Lab";
  }

  // Checking if theory radio button is selected or not
  if (ui->theoryradio->isChecked()) {
    isTheorySelected = true;
    qDebug() << "Selected -> Theory";
  }

  else {
    isTheorySelected = false;
  }

  // Checking for if lab is selected or not.
  // If the lab readio button is not selected then set the
  // next button to disbaled whether the checkbox is selected
  // or not selected
  //
  // 0 == Unchecked && 1 == Partially Checked && 2 == Checked

  if ((arg1 == 0 || arg1 == 2) && !isLabSelected && !isInfoGiven &&
      !isTheorySelected) {
    ui->next_2->setDisabled(true);
  } else if (arg1 == 2 && (isLabSelected || isTheorySelected) && isInfoGiven) {
    ui->next_2->setDisabled(false);
  }
}

void sfo::on_actionHome_triggered() { ui->stackedWidget->setCurrentIndex(0); }

void sfo::on_actionAbout_SFO_triggered() { about(); }

void sfo::on_next_3_clicked() {
  labSubNo = ui->labsubno->currentIndex();
  labSubNo += 1;
  qDebug() << "Selected number of Lab Subjects -> " + QString::number(labSubNo);

  createLineEdits();
  ui->stackedWidget->setCurrentIndex(4);
  ui->back_4->show();
  ui->next_4->show();
}

void sfo::on_back_4_clicked() {
  ui->back_4->hide();
  ui->next_4->hide();
  ui->stackedWidget->setCurrentIndex(3);
}

void sfo::createLineEdits() {
  // qDeleteAll deletes all the previous QLineEdits from the lineEditHolder to
  // solve memory leak
  // u/micod helped on this fix a lot
  qDeleteAll(lineEditHolder);
  lineEditHolder.clear();

  // Showing the line edits depending on the labsubno count
  for (int i = 0; i < labSubNo; i++) {
    lineEditHolder.push_back(new QLineEdit());
  }

  for (int i = 0; i < lineEditHolder.size(); i++) {
    vlayout->addWidget(lineEditHolder[i]);
  }
}

void sfo::takeLabSubName() {
  // Saving the input from the line edits
  for (int i = 0; i < lineEditHolder.size(); i++) {
    subNameHolder[i] = lineEditHolder[i]->text();
  }
}
void sfo::on_next_4_clicked() {
  takeLabSubName();
  for (int i = 0; i < lineEditHolder.size(); ++i) {
    qDebug() << "Lab Sub no: " + QString::number(i + 1) + " name is -> " +
                    subNameHolder[i];
  }

  ui->back_4->hide();
  ui->next_4->hide();
  ui->stackedWidget->setCurrentIndex(5);

  // Disable the open location button
  ui->pushButton_2->setDisabled(true);

  // Disbale and hide the back_5 button to disable the users to go to previous
  // Page as the dynamic QlineEdit is currently leaking memory if called twice
  // So untill this is fixed I am hiding the back button to prevent users from
  // going to previous screen easily

  ui->back_5->setDisabled(true);
  ui->back_5->hide();

  ui->createLabs->setDisabled(false);
  ui->delete_2->setDisabled(true);
}

void sfo::on_back_5_clicked() {

  ui->back_4->show();
  ui->next_4->show();
  ui->stackedWidget->setCurrentIndex(4);
}

void sfo::on_createLabs_clicked() {
  // Create the createdir class object to use it's functions
  Createdir *createdir = new Createdir;

  createdir->rootDirCreator(
      selectedDrive, year, semester,
      createdir->labOrtheory(isLabSelected, isTheorySelected));

  createdir->subFolderCreator(subNameHolder, labSubNo);
  if (createdir->isdDirCreationSuccessfull()) {
    // Set the isDirCreated var value to true to let other funcs
    // know that the selected folders have been created successfully
    isDirCreated = true;

    ui->createLabs->setDisabled(true);
    ui->successornot->setText("Successfully created the folders");
    // Enable the open location button
    ui->pushButton_2->setDisabled(false);
    ui->delete_2->setDisabled(false);
  } else {
    ui->createLabs->setDisabled(false);
    ui->successornot->setText("Could not create the folders");
  }
}

void sfo::on_actionFeedback_triggered() {
  // TODO: Uncomment the line below in v2 -> report a bug menu bar item
  //  QDesktopServices::openUrl(QUrl("https://github.com/Abir-Tx/StudyFolderOrganizer-GUI/issues/new/choose",
  //  QUrl::TolerantMode));
  QDesktopServices::openUrl(
      QUrl("mailto:abirtx@yandex.com", QUrl::TolerantMode));
}

// Open the folder button
void sfo::on_pushButton_2_clicked() {
  ui->statusbar->showMessage(
      "Openning the parent folder in Windows File Explorer", 2000);

  // Openning the created folder as said in #4 issue

  //  QDesktopServices::openUrl(test);
  QString createdFolderParent = selectedDrive + "University Study";
  QProcess::startDetached(
      "explorer.exe",
      {"/select,", QDir::toNativeSeparators(createdFolderParent)});
}

void sfo::on_next_5_clicked() {
  if (!isDirCreated) {
    QMessageBox::StandardButton reply = QMessageBox::warning(
        this, "Folders Not Created Yet !",
        "Your selected folders and structures have not been created yet. Click "
        "on create to create the folders.\n Are you sure you want to exit the "
        "app without creating the folders?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
      QApplication::exit(0);
    else
      return;
  } else
    QApplication::exit(0);
}

void sfo::on_delete_2_clicked() {
  QMessageBox::StandardButton reply = QMessageBox::question(
      this, "Are you sure?", "Deleting the folder will also delete all of it's "
                             "content. This can not be undone.",
      QMessageBox::Yes | QMessageBox::No);

  if (reply == QMessageBox::Yes) {
    QDir dir;
    dir.setCurrent(selectedDrive + "University Study");
    if (dir.exists()) {
      dir.removeRecursively();
      dir.setCurrent(selectedDrive);
      dir.rmdir(selectedDrive + "University Study");
      qDebug() << "Successfully deleted directory University Study";
      QMessageBox::information(this, "Success",
                               "Folder has been deleted successfully");

      // Disable the Open Location button upon folder deletion
      ui->pushButton_2->setDisabled(true);

      // set back the value of isDirCreated to false as the folders have been
      // deleted
      isDirCreated = false;
      // Enable the create folders button after a successfull deletion so users
      // can create folders again if they wants
      ui->createLabs->setDisabled(false);
    } else {
      qDebug() << "Directory does not exist";
      QMessageBox::information(this, "Error", "The folder was not found");
    }
  } else
    return;
}
