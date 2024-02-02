TEMPLATE = lib

INCLUDEPATH += \
    $$PWD/include

LIBS += \
    -L$$PWD/lib \
    -lavutil \
    -lavformat \
    -lavcodec \
    -lavdevice \
    -lavfilter \
    -lpostproc \
    -lswresample \
    -lswscale
