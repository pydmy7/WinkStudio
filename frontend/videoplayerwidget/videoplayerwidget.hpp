#ifndef VIDEOPLAYERWIDGET_HPP
#define VIDEOPLAYERWIDGET_HPP

#include <QWidget>

namespace Ui {
class VideoPlayerWidget;
}

class VideoPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayerWidget(QWidget *parent = nullptr);
    ~VideoPlayerWidget();

private:
    Ui::VideoPlayerWidget *ui;
};

#endif // VIDEOPLAYERWIDGET_HPP
