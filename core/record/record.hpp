#ifndef RECORD_HPP
#define RECORD_HPP

#include <QObject>

QT_BEGIN_NAMESPACE
class QProcess;
QT_END_NAMESPACE

class Record : public QObject
{
    Q_OBJECT
public:
    explicit Record(QObject *parent = nullptr);
    ~Record();

    void start();
    void stop();

private:
    QProcess* process_;
};

#endif // RECORD_HPP
