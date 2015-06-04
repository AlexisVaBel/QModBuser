#QT       += core
#QT       -= gui
#CONFIG   += console
#CONFIG   -= app_bundle

TEMPLATE=app
QT+=core
QT+=widgets

TARGET=QModBuser

SOURCES += \
    main.cpp \
    cntr/port/comport.cpp \
    cntr/portlistener.cpp \
    view/consoleview.cpp \
    view/mainwindow.cpp \
    view/viewportadaptor.cpp \
    view/comportview.cpp \
    cmn/charcoder.cpp \
    view/encodeview.cpp

HEADERS += \
    cntr/port/portinterface.hpp \
    cntr/port/comport.hpp \
    cntr/port/cmn/serialparams.hpp \
    cntr/portlistener.hpp \
    view/consoleview.hpp \
    view/mainwindow.hpp \
    view/viewportadaptor.hpp \
    view/comportview.hpp \
    cmn/charcoder.h \
    view/encodeview.h

win32{
INCLUDEPATH += C:/qwt-6.0.2/include
LIBS += -LC:/qwt-6.0.2/lib -lqwt
}

unix{
INCLUDEPATH += /usr/include/qwt6_0_2
LIBS += -L/usr/local/qwt-6.0.2/lib -lqwt
LIBS += -lX11
}

