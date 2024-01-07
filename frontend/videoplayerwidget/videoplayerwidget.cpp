#include "videoplayerwidget.hpp"
#include "ui_videoplayerwidget.h"

VideoPlayerWidget::VideoPlayerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoPlayerWidget)
{
    ui->setupUi(this);
}

VideoPlayerWidget::~VideoPlayerWidget()
{
    delete ui;
}
