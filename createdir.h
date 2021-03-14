#ifndef CREATEDIR_H
#define CREATEDIR_H

#include <QString>
class Createdir{
 public:
  void rootDirCreator(QString &selectedDrive, QString &year,
                      QString &semester, QString labOrTheory);
  QString labOrtheory(bool isLabSelected, bool isTheorySelected);
  ~Createdir();
};

#endif // CREATEDIR_H
