QT       += core gui
TARGET = borderless
TEMPLATE = app

CONFIG += debug
DESTDIR = ./bin
MOC_DIR = ./tmp
OBJECTS_DIR = ./tmp

SOURCES += \
    src/main.cpp\
    src/MainFrame.cpp\
    src/TitleBar.cpp

HEADERS  += \
    src/MainFrame.h\
    src/TitleBar.h
