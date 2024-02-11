#include "record.hpp"

#include "utils/config/config.hpp"

#include <QProcess>
#include <QApplication>

Record::Record(QObject *parent)
    : QObject{parent}
{
    process_ = new QProcess{};

    QString workdir = QApplication::applicationDirPath() + "/ORS/";
    process_->setWorkingDirectory(workdir);

    process_->setStandardErrorFile(workdir + "obs-standard-error.txt");
    process_->setStandardOutputFile(workdir + "obs-standard-output.txt");

    QString program = workdir + "ors-studio.exe";
    process_->setProgram(program);

    process_->start();
}

Record::~Record()
{
    stop();
    process_->write("quit");
    delete process_;
}

void Record::start()
{
    // std::string path = "filepath=" + config::fileaddress.toStdString();
    // process_->write(path.data());
    process_->write("start\n");
}

void Record::stop()
{
    process_->write("stop\n");
}
