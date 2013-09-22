cache()

QT       -= core gui

TARGET = jdksavdecc-c
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += include
DEPENDPATH += $$INCLUDEPATH

SOURCES += $$files( src/*.c )

HEADERS += $$files( include/*.h )

