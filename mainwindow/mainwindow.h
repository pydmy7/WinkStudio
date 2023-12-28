#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
class QTimer;
class QLCDNumber;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    int m_totseconds;
    QTimer* m_timer;
    QLCDNumber* m_lcdnumber;

    void initMembers();
    void initSignalSlots();
    void initConfig();

private slots:
    void switchDarkTheme();
    void switchLightTheme();
};
#endif // MAINWINDOW_H
