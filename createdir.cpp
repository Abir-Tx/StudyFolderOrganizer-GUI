#include "createdir.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>

// Global vars
QString rootDir;
QDir dir;


void Createdir::rootDirCreator(QString &driveLetter, QString &year,
                               QString &semester, QString labOrTheory){
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

  //Creating the folders

  rootDir = driveLetter+"University Study/Study Materials/"
                    +year+" Year/"+semester+" Semester/"+labOrTheory
                    +"/";
  dir.setPath(rootDir);
  dir.mkpath(rootDir);
  if (dir.exists()){
    qDebug()<<"Root folders created successfully";
  }
  else
  {
    qDebug()<<"Could not create root folders";
  }
//  if (dir.exists()){
//    qDebug()<<"Folder already exixts";
//  }
//  else
//  {
//     dir.mkpath(rootDir);
//     qDebug()<<"Root Directory created";
//  }
}

// Return Lab or Theory depending on what user has selected
QString Createdir::labOrtheory(bool isLabSelected, bool isTheorySelected){
  if (isLabSelected) return "Lab";
  else if (isTheorySelected) return "Theory";
  else return 0;
}


// Creates Subject folders based on user's given names & adds mid-term & final-term folders inside each sub folder
void Createdir::subFolderCreator(QString *subNameHolder, int labSubNo){
  for (int i= 0; i< labSubNo; i++){
    dir.mkpath(rootDir+subNameHolder[i]+"/Mid-Term/Lessons");
    dir.mkpath(rootDir+subNameHolder[i]+"/Final-Term/Lessons");
  }

  // Checking if the subject folders have been created or not
  dir.setPath(rootDir+subNameHolder[0]);
  if (dir.exists())
    qDebug()<<"Subject folders created successfully";
  else
    qDebug()<<"Could not created subject folders";
}

bool Createdir::isdDirCreationSuccessfull(){
  dir.setPath(rootDir);
  if (dir.exists())
    return true;
  else
    return false;
}
