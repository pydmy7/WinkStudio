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
    painter.drawPixmap(this->rect(), m_pixmap);
    event->accept();
}

void OpenGLWidget::receivePixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
}
