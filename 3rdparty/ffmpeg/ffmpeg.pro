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

# 其实不需要它们暴露出来，因为我们只是include并不去修改
HEADERS += \
    $$PWD/include/libavcodec/* \
    $$PWD/include/libavdevice/* \
    $$PWD/include/libavfilter/* \
    $$PWD/include/libavformat/* \
    $$PWD/include/libavutil/* \
    $$PWD/include/libpostproc/* \
    $$PWD/include/libswresample/* \
    $$PWD/include/libswscale/* \
