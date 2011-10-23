CONFIG += debug

TEMPLATE = app
TARGET = 
DEPENDPATH += . include src
INCLUDEPATH += . include

# Input
HEADERS += include/abs.hh \
           include/app.hh \
           include/painter.hh \
           include/term.hh \
           include/var.hh \
           include/window.hh
SOURCES += src/abs.cc \
           src/app.cc \
           src/main.cc \
           src/painter.cc \
           src/term.cc \
           src/var.cc \
           src/window.cc
