# -------------------------------------------------
# Project created by QtCreator 2009-04-24T14:05:45
# -------------------------------------------------
TARGET = PswDRec
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    messengers.cpp \
    psi.cpp \
    kopete.cpp \
    systeminfo.cpp
HEADERS += mainwindow.h \
    messengers.h \
    psi.h \
    kopete.h \
    systeminfo.h
FORMS += mainwindow.ui
OTHER_FILES += CHANGELOG
LIBS += -lQtXml \
        -lQtNetwork
