QT += widgets printsupport

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

SUBDIRS += \
    GUI.pro \
    GUI.pro

LIBS += -L/usr/local/lib -lusb-1.0
LIBS += -lfftw3
LIBS += -L$$PWD/../Ne10-master/build/modules/ -lNE10

FORMS += \
    graph.ui


INCLUDEPATH += $$PWD/../Ne10-master/inc
