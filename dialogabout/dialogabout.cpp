#include "dialogabout.h"
#include "ui_dialogabout.h"

#include <QCoreApplication>
#include <QDesktopServices>
#include <QUrl>

DialogAbout::DialogAbout(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    initMembers();
    initSignalSlots();
}

DialogAbout::~DialogAbout()
{
    delete ui;
}

void DialogAbout::initMembers()
{
    ui->label_version->setText(QCoreApplication::applicationVersion());
}

void DialogAbout::initSignalSlots()
{
    connect(ui->label_author, &QLabel::linkActivated, [](const QString& url) {
        QDesktopServices::openUrl(QUrl(url));
    });
    connect(ui->label_opensourceaddress, &QLabel::linkActivated, [](const QString& url) {
        QDesktopServices::openUrl(QUrl(url));
    });
}
