#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ScreenRecoderWidget;
class AudioPlayerWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ScreenRecoderWidget* m_screenrecoderwidget;
    AudioPlayerWidget* m_audioplayerwidget;

    void initMembers();
    void initSignalSlots();

private slots:
    void switchDarkTheme();
    void switchLightTheme();
};
#endif // MAINWINDOW_H
