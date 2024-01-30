TEMPLATE = lib

HEADERS += \
    $$PWD/CaptureVideoThread.h\
    $$PWD/CaptureAudioThread.h\
    $$PWD/FpsControl.h \
    $$PWD/Recorder.h \
    $$PWD/SingletonUtils.h
	
SOURCES += \
    $$PWD/CaptureVideoThread.cpp\
    $$PWD/CaptureAudioThread.cpp\
    $$PWD/FpsControl.cpp \
    $$PWD/Recorder.cpp \
    $$PWD/SingletonUtils.cpp
