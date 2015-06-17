TEMPLATE=app
QT+=core
QT+=widgets
QT+=xml
CONFIG+=static

TARGET=QModBuser

SOURCES += \
    main.cpp \    
    view/consoleview.cpp \
    view/mainwindow.cpp \
    view/comportview.cpp \
    cmn/charcoder.cpp \
    view/encodeview.cpp \
    port/comportlnx.cpp \
    port/portfactory.cpp \
    cntr/rwadaptor.cpp \
    rw/rwprovider.cpp \
    rw/devbase.cpp \
    rw/devlistener.cpp \
    rw/devfactory.cpp \
    rw/devrw.cpp


HEADERS += \    
    view/consoleview.hpp \
    view/mainwindow.hpp \
    view/comportview.hpp \
    view/encodeview.hpp \
    cmn/charcoder.h \
    cmn/serialparams.hpp \
    port/portinterface.hpp \
    port/comportlnx.hpp \
    port/portfactory.hpp \
    cntr/rwadaptor.hpp \
    rw/rwprovider.hpp \
    rw/devbase.hpp \
    rw/devlistener.hpp \
    rw/devfactory.hpp \
    rw/devrw.hpp


#unix{
#    INCLUDEPATH+=/usr/local/include/yaml
#    LIBS+=-L/usr/local/lib -lyaml-cpp
#}
