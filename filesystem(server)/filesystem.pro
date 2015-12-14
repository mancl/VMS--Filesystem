#CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    cdir.cpp \
    cfile.cpp \
    chandler.cpp

HEADERS += \
    global.h \
    cdir.h \
    cfile.h \
    chandler.h
LIBS += -lpthread
