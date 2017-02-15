
QT       += core gui widgets serialport xml printsupport
#greaterThan(QT_MAJOR_VERSION,4): QT += widgets

#DEFINES += QT_NO_DEBUG_OUTPUT

TARGET = SerialPlus
TEMPLATE = app

DESTDIR = ./build

INCLUDEPATH += ./include \

#DEPENDPATH=./include

OBJECTS_DIR= ./obj
MOC_DIR = ./moc 

SOURCES += src/main.cpp \
           src/datadisplay.cpp \
           src/asciidisplay.cpp \
           src/hexdisplay.cpp \
           src/binarydisplay.cpp \
           src/monitorwidget.cpp \
           src/datasender.cpp \
           src/normalsender.cpp \
           src/terminalsender.cpp \
           src/senderwidget.cpp \
           src/mainwindow.cpp \
           src/terminaledit.cpp \
    src/configdialog.cpp \
    src/aboutdialog.cpp \
    src/searchdialog.cpp


HEADERS += include/datadisplay.h \
           include/asciidisplay.h \
           include/hexdisplay.h \
           include/binarydisplay.h \
           include/monitorwidget.h \
           include/config.h \
           include/datasender.h \
           include/normalsender.h \
           include/terminalsender.h \
           include/mainwindow.h \
           include/terminaledit.h \
    include/configdialog.h \
    include/aboutdialog.h \
    include/senderwidget.h \
    include/searchdialog.h


RESOURCES += \
    application.qrc







