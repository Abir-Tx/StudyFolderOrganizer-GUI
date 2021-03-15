#ifndef APPINFO_H
#define APPINFO_H

#include <QApplication>

const QString applicationName = "SFO";
const QString applicationVersion = "v1.0";
const QString applicationDisplayName = "Study Folder Organizer";

unsigned short int minWidth = 650;
unsigned short int minHeight = 350;
QSize minAppSize(minWidth, minHeight);
#endif // APPINFO_H
