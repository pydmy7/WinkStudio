#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginDialog;
}
QT_END_NAMESPACE

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void on_btn_login_clicked();
    void on_btn_signup_clicked();
    void on_btn_close_clicked();
    void on_btn_accept_clicked();
    void on_lineedit_username_textChanged(const QString &text);
    void on_lineedit_password_textChanged(const QString &text);

private:
    Ui::LoginDialog *ui;

    QPoint dragstartpos;

    void initMembers();
    void initSignalSlots();

    QString encrypt(const QString& str);
};

#endif // LOGINDIALOG_H
