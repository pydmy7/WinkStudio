#include "dialogset.h"
#include "ui_dialogset.h"

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
    // read config file
    m_diraddress = QCoreApplication::applicationDirPath();
    ui->lineedit_directoryaddress->setText(m_diraddress);
}

void DialogSet::initSignalSlots()
{
    connect(ui->btn_selectdirectory, &QPushButton::clicked, this, [this]() {
        QString selectdir = QFileDialog::getExistingDirectory(this, "选择一个目录", m_diraddress);
        if (!selectdir.isEmpty()) {
            this->m_diraddress = selectdir;
            this->ui->lineedit_directoryaddress->setText(selectdir);
        }
    });
    connect(ui->btn_confirm, &QPushButton::clicked, this, [this]() {
        // 如果路径合法：递归创建目录 & 写入配置文件
        // else: 提示路径不合法 & return
        this->close();
    });
    connect(ui->btn_cancel, &QPushButton::clicked, this, [this]() {
        this->close();
    });
}
