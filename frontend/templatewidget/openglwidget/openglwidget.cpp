#include "openglwidget.hpp"

#include <QPaintEvent>
#include <QPainter>

OpenGLWidget::OpenGLWidget(QWidget* parent) :
    QOpenGLWidget(parent)
{
}

void OpenGLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawImage(this->rect(), QImage{":/images/wink.png"});
    event->accept();
}
