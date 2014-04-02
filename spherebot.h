#ifndef SPHEREBOT_H
#define SPHEREBOT_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QStringList>
#include <QDebug>
namespace Spherebot {
    enum Printstate{SB_Disconnected, SB_Connected, SB_Printing, SB_Idle, SB_WaitUserOk, SB_WaitPrinterOk};
}

class SphereBot : public QObject
{
    Q_OBJECT
public:
    explicit SphereBot(QObject *parent = 0);
    bool connectSerial(QString port);
    void disconnectSerial();

    void disableSteppers();
    void sendFile(QString path);
    void cancelPrint();

    Spherebot::Printstate state;

public slots:
    void continuePrinting();

    void setServo(int value);
    void setPitch(int value);
    void setRoll(int value);

private slots:
    void gotOkFromPrinter();
    void readData();

private:
    void sendCommand(QString cmd);
    void sendNextLine();

    QSerialPort *serial;
    QString buffer;
    QFile *file;
    QTextStream *fileStream;

signals:
    void printPause(QString message);
    void printDone();
};

#endif // SPHEREBOT_H
