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
    view/comportview.cpp

HEADERS += \
    cntr/port/portinterface.hpp \
    cntr/port/comport.hpp \
    cntr/port/cmn/serialparams.hpp \
    cntr/portlistener.hpp \
    view/consoleview.hpp \
    view/mainwindow.hpp \
    view/viewportadaptor.hpp \
    view/comportview.hpp
