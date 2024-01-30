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
    QImage m_image;
    QTimer* m_timer;

public slots:
    void receiveImage(const QImage& image);
};

#endif // OPENGLWIDGET_HPP
