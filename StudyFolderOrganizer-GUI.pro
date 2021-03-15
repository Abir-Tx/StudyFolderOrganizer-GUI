QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    createdir.cpp \
    main.cpp \
    sfo.cpp

HEADERS += \
    appinfo.h \
    createdir.h \
    sfo.h

FORMS += \
    sfo.ui

TRANSLATIONS += \
    StudyFolderOrganizer-GUI_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

# Setting the binary executable icon
RC_ICONS += res/logo/SFO_v2.ico
