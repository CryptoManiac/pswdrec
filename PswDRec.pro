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
    sim.cpp \
    systeminfo.cpp \
    common.cpp \
    kftpgrabber.cpp
HEADERS += mainwindow.h \
    messengers.h \
    psi.h \
    kopete.h \
    sim.h \
    systeminfo.h \
    common.h \
    kftpgrabber.h
FORMS += mainwindow.ui
OTHER_FILES += CHANGELOG
LIBS += -lQtXml \
    -lQtNetwork
