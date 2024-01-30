#include "openglwidget.hpp"

#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

OpenGLWidget::OpenGLWidget(QWidget* parent) :
    QOpenGLWidget(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        this->update();
    });
    m_timer->start(20);
}

void OpenGLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawImage(this->rect(), m_image);
    event->accept();
}

void OpenGLWidget::receiveImage(const QImage &image)
{
    m_image = image;
    this->update();
}
