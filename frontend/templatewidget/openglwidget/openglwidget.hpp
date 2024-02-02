#ifndef OPENGLWIDGET_HPP
#define OPENGLWIDGET_HPP

#include <QOpenGLWidget>

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget* parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_pixmap;
    QTimer* m_timer;

public slots:
    void receivePixmap(const QPixmap& pixmap);
};

#endif // OPENGLWIDGET_HPP
