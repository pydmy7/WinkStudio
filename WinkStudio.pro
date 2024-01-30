QT += core gui network
QT += multimedia multimediawidgets
QT += axcontainer openglwidgets

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

include(algorithm/algorithm.pro)
include(global/global.pro)
include(3rdparty/3rdparty.pro)
include(config/config.pro)
include(plugin/plugin.pro)
include(frontend/frontend.pro)
include(templatewidgets/templatewidgets.pro)
include(Record/Record.pri)
include(app/app.pro)

DISTFILES += \
    resource/theme/Acri.qss \
    resource/theme/Acri/bot_hook.png \
    resource/theme/Acri/bot_hook2.png \
    resource/theme/Acri/checkbox_checked.png \
    resource/theme/Acri/checkbox_checked_disabled.png \
    resource/theme/Acri/checkbox_checked_focus.png \
    resource/theme/Acri/checkbox_unchecked.png \
    resource/theme/Acri/checkbox_unchecked_disabled.png \
    resource/theme/Acri/checkbox_unchecked_focus.png \
    resource/theme/Acri/radio_checked.png \
    resource/theme/Acri/radio_checked_disabled.png \
    resource/theme/Acri/radio_checked_focus.png \
    resource/theme/Acri/radio_unchecked.png \
    resource/theme/Acri/radio_unchecked_disabled.png \
    resource/theme/Acri/radio_unchecked_focus.png \
    resource/theme/Acri/sizegrip.png \
    resource/theme/Acri/top_hook.png \
    resource/theme/Dark.qss \
    resource/theme/Dark/alert.svg \
    resource/theme/Dark/close.svg \
    resource/theme/Dark/cogs.svg \
    resource/theme/Dark/collapse.svg \
    resource/theme/Dark/dots-vert.svg \
    resource/theme/Dark/dots.svg \
    resource/theme/Dark/down.svg \
    resource/theme/Dark/entry-clear.svg \
    resource/theme/Dark/expand.svg \
    resource/theme/Dark/filter.svg \
    resource/theme/Dark/interact.svg \
    resource/theme/Dark/left.svg \
    resource/theme/Dark/locked.svg \
    resource/theme/Dark/media-pause.svg \
    resource/theme/Dark/media/media_next.svg \
    resource/theme/Dark/media/media_pause.svg \
    resource/theme/Dark/media/media_play.svg \
    resource/theme/Dark/media/media_previous.svg \
    resource/theme/Dark/media/media_restart.svg \
    resource/theme/Dark/media/media_stop.svg \
    resource/theme/Dark/minus.svg \
    resource/theme/Dark/mute.svg \
    resource/theme/Dark/network-disconnected.svg \
    resource/theme/Dark/network-inactive.svg \
    resource/theme/Dark/no_sources.svg \
    resource/theme/Dark/plus.svg \
    resource/theme/Dark/popout.svg \
    resource/theme/Dark/recording-inactive.svg \
    resource/theme/Dark/recording-pause-inactive.svg \
    resource/theme/Dark/refresh.svg \
    resource/theme/Dark/revert.svg \
    resource/theme/Dark/right.svg \
    resource/theme/Dark/save.svg \
    resource/theme/Dark/settings/accessibility.svg \
    resource/theme/Dark/settings/advanced.svg \
    resource/theme/Dark/settings/audio.svg \
    resource/theme/Dark/settings/general.svg \
    resource/theme/Dark/settings/hotkeys.svg \
    resource/theme/Dark/settings/output.svg \
    resource/theme/Dark/settings/stream.svg \
    resource/theme/Dark/settings/video.svg \
    resource/theme/Dark/sources/brush.svg \
    resource/theme/Dark/sources/camera.svg \
    resource/theme/Dark/sources/default.svg \
    resource/theme/Dark/sources/gamepad.svg \
    resource/theme/Dark/sources/globe.svg \
    resource/theme/Dark/sources/group.svg \
    resource/theme/Dark/sources/image.svg \
    resource/theme/Dark/sources/media.svg \
    resource/theme/Dark/sources/microphone.svg \
    resource/theme/Dark/sources/scene.svg \
    resource/theme/Dark/sources/slideshow.svg \
    resource/theme/Dark/sources/text.svg \
    resource/theme/Dark/sources/window.svg \
    resource/theme/Dark/sources/windowaudio.svg \
    resource/theme/Dark/streaming-inactive.svg \
    resource/theme/Dark/trash.svg \
    resource/theme/Dark/unassigned.svg \
    resource/theme/Dark/up.svg \
    resource/theme/Dark/updown.svg \
    resource/theme/Dark/visible.svg \
    resource/theme/Grey.qss \
    resource/theme/Light.qss \
    resource/theme/Light/alert.svg \
    resource/theme/Light/checkbox_checked.svg \
    resource/theme/Light/checkbox_checked_disabled.svg \
    resource/theme/Light/checkbox_checked_focus.svg \
    resource/theme/Light/checkbox_unchecked.svg \
    resource/theme/Light/checkbox_unchecked_disabled.svg \
    resource/theme/Light/checkbox_unchecked_focus.svg \
    resource/theme/Light/close.svg \
    resource/theme/Light/cogs.svg \
    resource/theme/Light/collapse.svg \
    resource/theme/Light/dots-vert.svg \
    resource/theme/Light/dots.svg \
    resource/theme/Light/down.svg \
    resource/theme/Light/entry-clear.svg \
    resource/theme/Light/expand.svg \
    resource/theme/Light/filter.svg \
    resource/theme/Light/interact.svg \
    resource/theme/Light/left.svg \
    resource/theme/Light/locked.svg \
    resource/theme/Light/media-pause.svg \
    resource/theme/Light/media/media_next.svg \
    resource/theme/Light/media/media_pause.svg \
    resource/theme/Light/media/media_play.svg \
    resource/theme/Light/media/media_previous.svg \
    resource/theme/Light/media/media_restart.svg \
    resource/theme/Light/media/media_stop.svg \
    resource/theme/Light/minus.svg \
    resource/theme/Light/mute.svg \
    resource/theme/Light/no_sources.svg \
    resource/theme/Light/plus.svg \
    resource/theme/Light/popout.svg \
    resource/theme/Light/refresh.svg \
    resource/theme/Light/revert.svg \
    resource/theme/Light/right.svg \
    resource/theme/Light/save.svg \
    resource/theme/Light/settings/accessibility.svg \
    resource/theme/Light/settings/advanced.svg \
    resource/theme/Light/settings/audio.svg \
    resource/theme/Light/settings/general.svg \
    resource/theme/Light/settings/hotkeys.svg \
    resource/theme/Light/settings/output.svg \
    resource/theme/Light/settings/stream.svg \
    resource/theme/Light/settings/video.svg \
    resource/theme/Light/sources/brush.svg \
    resource/theme/Light/sources/camera.svg \
    resource/theme/Light/sources/default.svg \
    resource/theme/Light/sources/gamepad.svg \
    resource/theme/Light/sources/globe.svg \
    resource/theme/Light/sources/group.svg \
    resource/theme/Light/sources/image.svg \
    resource/theme/Light/sources/media.svg \
    resource/theme/Light/sources/microphone.svg \
    resource/theme/Light/sources/scene.svg \
    resource/theme/Light/sources/slideshow.svg \
    resource/theme/Light/sources/text.svg \
    resource/theme/Light/sources/window.svg \
    resource/theme/Light/sources/windowaudio.svg \
    resource/theme/Light/trash.svg \
    resource/theme/Light/up.svg \
    resource/theme/Light/updown.svg \
    resource/theme/Light/visible.svg \
    resource/theme/Rachni.qss \
    resource/theme/Rachni/checkbox_checked.png \
    resource/theme/Rachni/checkbox_checked_disabled.png \
    resource/theme/Rachni/checkbox_checked_focus.png \
    resource/theme/Rachni/checkbox_unchecked.png \
    resource/theme/Rachni/checkbox_unchecked_disabled.png \
    resource/theme/Rachni/checkbox_unchecked_focus.png \
    resource/theme/Rachni/down_arrow.png \
    resource/theme/Rachni/down_arrow_disabled.png \
    resource/theme/Rachni/left_arrow.png \
    resource/theme/Rachni/left_arrow_disabled.png \
    resource/theme/Rachni/radio_checked.png \
    resource/theme/Rachni/radio_checked_disabled.png \
    resource/theme/Rachni/radio_checked_focus.png \
    resource/theme/Rachni/radio_unchecked.png \
    resource/theme/Rachni/radio_unchecked_disabled.png \
    resource/theme/Rachni/radio_unchecked_focus.png \
    resource/theme/Rachni/right_arrow.png \
    resource/theme/Rachni/right_arrow_disabled.png \
    resource/theme/Rachni/sizegrip.png \
    resource/theme/Rachni/up_arrow.png \
    resource/theme/Rachni/up_arrow_disabled.png \
    resource/theme/System.qss \
    resource/theme/Yami.qss \
    resource/theme/Yami/checkbox_checked.svg \
    resource/theme/Yami/checkbox_checked_disabled.svg \
    resource/theme/Yami/checkbox_checked_focus.svg \
    resource/theme/Yami/checkbox_unchecked.svg \
    resource/theme/Yami/checkbox_unchecked_disabled.svg \
    resource/theme/Yami/checkbox_unchecked_focus.svg \
    resource/themes/Yami.qss
