#include "keyecholabel.hpp"

#include <QGuiApplication>
#include <QScreen>
#include <QRect>

#include <QKeyEvent>

KeyEchoLabel::KeyEchoLabel(QLabel *parent) : QLabel(parent)
{
    this->setText("hhhhhhh");
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowModality(Qt::NonModal);
    this->setWindowFlags(Qt::SplashScreen
                         | Qt::CustomizeWindowHint
                         | Qt::FramelessWindowHint
                         | Qt::WindowStaysOnTopHint
                         // | Qt::WindowTransparentForInput
                         // | Qt::WindowDoesNotAcceptFocus
                         );
    this->setAttribute(Qt::WA_TranslucentBackground);
    QFont font;
    font.setPointSize(30);
    this->setFont(font);
    this->resize(270, 80);
    QRect availabdesktoprect = QGuiApplication::primaryScreen()->availableGeometry();
    int right = availabdesktoprect.right(), bottom = availabdesktoprect.bottom();
    int labelwidth = this->width(), labelheight = this->height();
    this->move(right - labelwidth, bottom - labelheight);
}


void KeyEchoLabel::keyPressEvent(QKeyEvent *event)
{
    this->setText("Get a key: " + event->text());
}
