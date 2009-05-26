# -------------------------------------------------
# Project created by QtCreator 2009-04-24T14:05:45
# -------------------------------------------------
TARGET = PswDRec
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    systeminfo.cpp \
    common.cpp \
    kftpgrabber.cpp \
    mail/kmail.cpp \
    messengers/psi.cpp \
    messengers/messengers.cpp \
    messengers/sim.cpp \
    messengers/kopete.cpp \
    messengers/mdc.cpp \
    messengers/licq.cpp \
    messengers/alicq.cpp \
    messengers/pidgin.cpp \
    messengers/gajim.cpp \
    messengers/sipcom.cpp \
    messengers/saje.cpp
HEADERS += mainwindow.h \
    systeminfo.h \
    common.h \
    kftpgrabber.h \
    mail/kmail.h \
    messengers/psi.h \
    messengers/messengers.h \
    messengers/sim.h \
    messengers/kopete.h \
    messengers/mdc.h \
    messengers/licq.h \
    messengers/alicq.h \
    messengers/pidgin.h \
    messengers/gajim.h \
    messengers/sipcom.h \
    messengers/saje.h
FORMS += mainwindow.ui
OTHER_FILES += CHANGELOG \
    COPYING
LIBS += -lQtXml \
    -lQtNetwork
RESOURCES += 
