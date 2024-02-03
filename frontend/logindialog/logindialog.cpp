#include "logindialog.hpp"
#include "ui_logindialog.h"

#include "network/socketthread.hpp"
#include "utility/dataformat/dataformat.hpp"

#include <QCryptographicHash>
#include <QMouseEvent>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    initMembers();
    initSignalSlots();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragstartpos = event->pos();
        event->accept();
    }
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint deltapos = event->pos() - dragstartpos;
        QWidget::move(this->pos() + deltapos);
        event->accept();
    }
}

void LoginDialog::on_btn_login_clicked()
{
    QString username = ui->lineedit_username->text();
    // QString password = encrypt(ui->lineedit_password->text());
    QString password = ui->lineedit_password->text();
    QVariant var;
    var.setValue(DataFormat::LoginClient{username, password});
    SocketThread* socketthread = new SocketThread{var};
    connect(socketthread, &QThread::finished, socketthread, &QThread::deleteLater);
    connect(socketthread, &SocketThread::loginResult, this, [this](bool flag) {
        if (flag) {
            this->accept();
        } else {
            QMessageBox::information(this, "登录失败", "用户名不存在或密码错误.");
        }
    });
    socketthread->start();
}

void LoginDialog::on_btn_signup_clicked()
{
    QString username = ui->lineedit_username->text();
    // QString password = encrypt(ui->lineedit_password->text());
    QString password = ui->lineedit_password->text();
    QVariant var;
    var.setValue(DataFormat::SignupClient{username, password});
    SocketThread* socketthread = new SocketThread{var};
    connect(socketthread, &QThread::finished, socketthread, &QThread::deleteLater);
    connect(socketthread, &SocketThread::signupResult, this, [this](bool flag) {
        if (flag) {
            QMessageBox::information(this, "注册成功", "快去登录吧!");
        } else {
            QMessageBox::information(this, "注册失败", "用户名已存在.");
        }
    });
    socketthread->start();
}

void LoginDialog::initMembers()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::SplashScreen | Qt::WindowStaysOnTopHint);
}

void LoginDialog::initSignalSlots()
{
    connect(ui->lineedit_password, &TLineEdit::getFocus, this, [this]() {
        ui->label_22->setPixmap(QPixmap{":/images/22close.png"});
        ui->label_33->setPixmap(QPixmap{":/images/33close.png"});
    });
    connect(ui->lineedit_password, &TLineEdit::loseFocus, this, [this]() {
        ui->label_22->setPixmap(QPixmap{":/images/22open.png"});
        ui->label_33->setPixmap(QPixmap{":/images/33open.png"});
    });
}

QString LoginDialog:: encrypt(const QString &str)
{
    QCryptographicHash hash{QCryptographicHash::Md5};
    hash.addData(str.toLocal8Bit());
    QString md5 = hash.result().toHex();
    return  md5;
}

void LoginDialog::on_btn_close_clicked()
{
    this->close();
}

void LoginDialog::on_btn_accept_clicked()
{
    this->accept();
}

void LoginDialog::on_lineedit_username_textChanged(const QString &text)
{
    if (text.size() >= 2 && ui->lineedit_password->text().size() >= 5) {
        ui->btn_login->setEnabled(true);
        ui->btn_signup->setEnabled(true);
    } else {
        ui->btn_login->setEnabled(false);
        ui->btn_signup->setEnabled(false);
    }
}

void LoginDialog::on_lineedit_password_textChanged(const QString &text)
{
    if (ui->lineedit_username->text().size() >= 2 && text.size() >= 5) {
        ui->btn_login->setEnabled(true);
        ui->btn_signup->setEnabled(true);
    } else {
        ui->btn_login->setEnabled(false);
        ui->btn_signup->setEnabled(false);
    }
}
