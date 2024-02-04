TEMPLATE = lib

HEADERS += \
    $$PWD/socketthread.hpp

SOURCES += \
    $$PWD/socketthread.cpp

include(Server/server.pro)
