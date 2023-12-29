#include "frontend/mainwindow/mainwindow.hpp"

#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>

inline void init() {
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
#elif (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    QCoreApplication::setOrganizationName("pydmy7");
    QCoreApplication::setOrganizationDomain("https://github.com/pydmy7");
    QCoreApplication::setApplicationName("WinkStudio");
    QCoreApplication::setApplicationVersion("1.0(64bit)");
}

int main(int argc, char *argv[])
{
    init();

    QApplication app(argc, argv);

    QSharedMemory shared("WinkStudio");
    if (shared.attach()) {
        QMessageBox::warning(nullptr, "来自wink小助手的提示", "软件正在运行，请勿重复启动软件哦。");
        return 0;
    }
    shared.create(1);

    MainWindow mw;
    mw.show();

    return app.exec();
}
