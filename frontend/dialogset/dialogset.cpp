#include "dialogset.hpp"
#include "ui_dialogset.h"

#include "utility/config/config.hpp"

#include <QCoreApplication>
#include <QFileDialog>

DialogSet::DialogSet(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogSet)
{
    ui->setupUi(this);
    initMembers();
    initSignalSlots();
}

DialogSet::~DialogSet()
{
    delete ui;
}

void DialogSet::initMembers()
{
    ui->lineedit_directoryaddress->setText(config::fileaddress);
}

void DialogSet::initSignalSlots()
{
    connect(ui->btn_selectdirectory, &QPushButton::clicked, this, [this]() {
        QString selectdir = QFileDialog::getExistingDirectory(this, "选择一个目录", config::fileaddress);
        if (!selectdir.isEmpty()) {
            this->ui->lineedit_directoryaddress->setText(selectdir);
        }
    });
    connect(ui->btn_confirm, &QPushButton::clicked, this, [this]() {
        QString curaddress = ui->lineedit_directoryaddress->text();
        config::writeFileAddress(curaddress);
        this->close();
    });
    connect(ui->btn_cancel, &QPushButton::clicked, this, [this]() {
        this->close();
    });
}
