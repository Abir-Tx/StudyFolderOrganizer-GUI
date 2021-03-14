#include "createdir.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>

void Createdir::rootDirCreator(QString &driveLetter, QString &year, QString &semester){
  // Checking the year
  if (year == "1")
    year+="st";
  else if (year=="2")
    year+="nd";
  else if(year=="3")
    year+="rd";
  else
    year+="th";

  // Checking the semester
  if (semester == "1")
    semester+="st";
  else if (semester=="2")
    semester+="nd";
  else if(semester=="3")
    semester+="rd";
  else
    semester+="th";

  QString rootDir = driveLetter+"University Study/Study Materials/"+year+" Year/"+semester+" Semester/";
  QDir dir(rootDir);

  if (dir.exists()){
    qDebug()<<"Folder already exixts";
  }
  else
  {
     dir.mkpath(rootDir);
     qDebug()<<"Root Directory created";
  }
}
