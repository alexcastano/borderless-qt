TARGET = borderless
TEMPLATE = app

QT = core gui
greaterThan(QT_MAJOR_VERSION, 4) {
	QT += widgets
}

CONFIG += debug
DESTDIR = ./bin
MOC_DIR = ./tmp
OBJECTS_DIR = ./tmp

SOURCES += \
	src/main.cpp\
	src/MainFrame.cpp\
	src/TitleBar.cpp\
	src/WindowTitleFilter.cpp

HEADERS  += \
	src/MainFrame.h\
	src/TitleBar.h\
	src/WindowTitleFilter.h
