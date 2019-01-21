#-------------------------------------------------
#
# Project created by QtCreator 2018-11-16T18:42:42
#
#-------------------------------------------------

QT       += core gui
 RC_ICONS = maze.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PathFinding
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    cell.cpp \
    searchproblem.cpp \
    breadthfirstsearch.cpp \
    depthfirstsearch.cpp \
    bidirectionalsearch.cpp \
    iterativedeepensearch.cpp \
    greedybestfirstsearch.cpp \
    astarsearch.cpp \
    dialogsetmapsize.cpp \
    dialogsetcost.cpp \
    dwastarsearch.cpp \
    uniformcostsearch.cpp

HEADERS += \
        mainwindow.h \
    cell.h \
    searchproblem.h \
    config.h \
    breadthfirstsearch.h \
    depthfirstsearch.h \
    bidirectionalsearch.h \
    iterativedeepensearch.h \
    greedybestfirstsearch.h \
    astarsearch.h \
    dialogsetmapsize.h \
    dialogsetcost.h \
    dwastarsearch.h \
    uniformcostsearch.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    img.qrc \
    qss.qrc
