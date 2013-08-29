cache()

QT       -= core gui

TARGET = avdecc
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += include
DEPENDPATH += $$INCLUDEPATH

SOURCES += $$files( src/*.c )

HEADERS += $$files( include/*.h )

