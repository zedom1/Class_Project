#-------------------------------------------------
#
# Project created by QtCreator 2018-06-21T14:13:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
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
        widget.cpp \
    rect.cpp \
    item.cpp \
    record.cpp \
    recordlist.cpp \
    event.cpp \
    sortalgorithm.cpp \
    selectionsort.cpp \
    quicksort.cpp \
    mergesort.cpp \
    insertionsort.cpp \
    bubblesort.cpp \
    heapsort.cpp \
    heapsortrect.cpp \
    radixsort.cpp \
    itemforr.cpp

HEADERS += \
        mainwindow.h \
    rect.h \
    item.h \
    record.h \
    recordlist.h \
    event.h \
    sortalgorithm.h \
    selectionsort.h \
    quicksort.h \
    mergesort.h \
    insertionsort.h \
    bubblesort.h \
    heapsort.h \
    heapsortrect.h \
    widget.h \
    radixsort.h \
    itemforr.h

FORMS += \
        mainwindow.ui \
    widget.ui

