#-------------------------------------------------
#
# Project created by QtCreator 2016-07-25T08:41:14
#
#-------------------------------------------------

QT       += core gui

RC_FILE = RunDosbox.rc

static:win32:QMAKE_LFLAGS += -static-libgcc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RunTbProg
TEMPLATE = app


SOURCES += main.cpp\
        RunDosbox.cpp

HEADERS  += RunDosbox.h

FORMS    += RunDosbox.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    resources/table.css
