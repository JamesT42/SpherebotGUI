#include "spherebot.h"

SphereBot::SphereBot(QObject *parent) :
    QObject(parent)
{
    serial = new QSerialPort(this);
    state = Spherebot::SB_Disconnected;

    connect(serial, SIGNAL(readyRead()),this, SLOT(readData()));

}

bool SphereBot::connectSerial(QString port){
    if (state!=Spherebot::SB_Disconnected)
        serial->close();

    serial->setPortName(port);
    if (!serial->open(QIODevice::ReadWrite)){
        qDebug()<<"SB: Could not open serialport";
        qDebug()<<"\t"<<serial->errorString();
        return false;
    }

    serial->setBaudRate(256000);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);


    if (serial->isOpen()){
        state=Spherebot::SB_Connected;
        qDebug()<<"SB: Connected Serial   "<<state;
        return true;
    } else {

        state=Spherebot::SB_Disconnected;
        qDebug()<<"SB: Could not open serialport";
        qDebug()<<"\t"<<serial->errorString();
        return false;
    }

}

void SphereBot::disconnectSerial(){
    if (state==Spherebot::SB_Disconnected) {
        return;
    }
    serial->close();
    state=Spherebot::SB_Disconnected;
    qDebug()<<"SB: Disonnected Serial";

}

void SphereBot::sendFile(QString path){
    file = new QFile(path);
    file->open(QIODevice::ReadOnly);

    fileStream = new QTextStream(file);
    state=Spherebot::SB_Printing;

    sendNextLine();

}

void SphereBot::cancelPrint(){
    state=Spherebot::SB_Connected;
    file->close();

}

void SphereBot::continuePrinting(){
     if (state!=Spherebot::SB_WaitUserOk)
        return;

    state=Spherebot::SB_Printing;
    sendNextLine();
}

void SphereBot::setServo(int value){
    if (state!=Spherebot::SB_Connected)
        return;
    QString tmp = ("M300 S" + QString::number((double)value));
    sendCommand(tmp);

}
void SphereBot::setRoll(int value){
    if (state!=Spherebot::SB_Connected)
        return;
    QString tmp = ("G1 X" + QString::number((double)value));
    sendCommand(tmp);

}
void SphereBot::setPitch(int value){
    if (state!=Spherebot::SB_Connected)
        return;
    QString tmp = ("G1 Y" + QString::number((double)value));
    sendCommand(tmp);

}

void SphereBot::gotOkFromPrinter(){
    if (state!=Spherebot::SB_WaitPrinterOk)
        return;
    state=Spherebot::SB_Printing;

    sendNextLine();
}

void SphereBot::readData(){
    QByteArray data = serial->readAll();
    buffer.append(data);
    if (buffer.endsWith("ok:\n")){
        buffer.clear();
        gotOkFromPrinter();
    }
}

void SphereBot::sendCommand(QString cmd){
    if (state==Spherebot::SB_Connected){
        cmd.remove(QRegExp("\\\((.*)\\)"));
        cmd.append("\n");
        serial->write(cmd.toUtf8());
    }
}

void SphereBot::sendNextLine(){
    if(state!=Spherebot::SB_Printing)
        return;

    if(fileStream->atEnd()){
        state=Spherebot::SB_Idle;
        file->close();
        fileStream->reset();
        emit printDone();
        return;
    }

    QString line=fileStream->readLine();

    QString stripped = QString(line);
    stripped.remove(QRegExp("\\\((.*)\\)"));
    if (stripped.length()>1){
        if (stripped.startsWith("M01")){
            state=Spherebot::SB_WaitUserOk;
            emit printPause(line);
            return;
        } else {
            state=Spherebot::SB_WaitPrinterOk;
            serial->write(stripped.append("\n").toUtf8());
            return;
        }
    }
    sendNextLine();
}





