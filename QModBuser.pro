TEMPLATE=app
QT+=core
QT+=widgets
#CONFIG+=static

TARGET=QModBuser

SOURCES += \
    main.cpp \
    cntr/portlistener.cpp \
    view/consoleview.cpp \
    view/mainwindow.cpp \
    view/viewportadaptor.cpp \
    view/comportview.cpp \
    cmn/charcoder.cpp \
    view/encodeview.cpp \
    cntr/port/comportlnx.cpp \
    cmn/simpleyaml.cpp \
    cntr/device/devmodbus.cpp \
    cntr/port/portfactory.cpp

HEADERS += \
    cntr/port/portinterface.hpp \
    cntr/port/cmn/serialparams.hpp \
    cntr/portlistener.hpp \
    view/consoleview.hpp \
    view/mainwindow.hpp \
    view/viewportadaptor.hpp \
    view/comportview.hpp \
    cmn/charcoder.h \
    view/encodeview.h \
    cntr/port/comportlnx.hpp \
    cntr/device/deviceinterface.hpp \
    cmn/simpleyaml.hpp \
    cntr/device/cmdinterface.hpp \
    cntr/device/devmodbus.hpp \
    cntr/port/portfactory.hpp

unix{
    INCLUDEPATH+=/usr/local/include/yaml
    LIBS+=-L/usr/local/lib -lyaml-cpp
}
