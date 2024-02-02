TEMPLATE = lib

INCLUDEPATH += \
    $$PWD/include

LIBS += \
    -L$$PWD/lib/ \
    -lBXC_AudioRecorder \
    -lBXC_VideoRecorder \
    -lBXC_AvEncoder
