#ifndef SPHEREGUI_H
#define SPHEREGUI_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPortInfo>
#include <QFileDialog>
#include <QMessageBox>

#include "spherebot.h"

namespace Ui {
class SphereGui;
}

class SphereGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit SphereGui(QWidget *parent = 0);
    ~SphereGui();

public slots:
    void showPrintMessage(QString msg);

signals:
    void continuePrinting();

private slots:
    void serialSelected(QAction *action);
    void disconnectSerial();

    void on_btn_sendFile_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::SphereGui *ui;
    SphereBot *bot;

    QAction *action_disconnect;
};

#endif // SPHEREGUI_H
