#-------------------------------------------------
#
# Project created by QtCreator 2019-05-08T00:37:26
#
#-------------------------------------------------

QT       += core gui
QT += opengl

CONFIG += address_sanitizer
QMAKE_CXXFLAGS += "-fsanitize=address -std=c++11 -fno-omit-frame-pointer"
QMAKE_LFLAGS += "-fsanitize=address"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = asteroid-4-sem
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

ASAN_OPTIONS=fast_unwind_on_malloc=0

SOURCES += \
    grav_calc.cpp \
        main.cpp \
        mainwindow.cpp \
    predicates.cxx \
    scene3d.cpp \
    tetgen.cxx

HEADERS += \
    grav_calc.h \
        mainwindow.h \
    scene3d.h \
    tetgen.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    html/index.html
