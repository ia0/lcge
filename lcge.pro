CONFIG += debug

TEMPLATE = app
TARGET = 
DEPENDPATH += . include src
INCLUDEPATH += . include

# Input
HEADERS += include/abs.hh include/app.hh include/term.hh include/var.hh
SOURCES += src/abs.cc src/app.cc src/main.cc src/term.cc src/var.cc
