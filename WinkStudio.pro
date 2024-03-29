QT += core gui network openglwidgets
QT += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

###########################################

TEMPLATE = subdirs

RESOURCES += \
    $$PWD/resource/themes/dark/darkstyle.qrc \
    $$PWD/resource/themes/light/lightstyle.qrc \
    $$PWD/resource/images/images.qrc

include(3rdparty/3rdparty.pro)
include(utils/utils.pro)
include(network/network.pro)
include(core/core.pro)
include(frontend/frontend.pro)
include(app/app.pro)
