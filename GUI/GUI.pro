QT += widgets printsupport


QMAKE_CXXFLAGS += -std=c++17

HEADERS += \
    MaFenetre.h \
    libusb.h \
    sdradar.h \
    qcustomplot.h \
    graph.h

SOURCES += \
    MaFenetre.cpp \
    main.cpp \
    sdradar.cpp \
    qcustomplot.cpp \
    graph.cpp

CONFIG(release,debug|release):
QMAKE_CFLAGS+=-pg
QMAKE_CXXFLAGS+=-pg
QMAKE_LFLAGS+=-pg

QMAKE_CXXFLAGS_RELEASE+= -O3


SUBDIRS += \
    GUI.pro \
    GUI.pro

LIBS += -L/usr/local/lib -lusb-1.0
LIBS += -lfftw3

FORMS += \
    graph.ui


