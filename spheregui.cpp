#include "spheregui.h"
#include "ui_spheregui.h"

SphereGui::SphereGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SphereGui)
{
    ui->setupUi(this);
    bot = new SphereBot(this);

    connect(ui->menuSerialport, SIGNAL(triggered(QAction*)), this, SLOT(serialSelected(QAction*)));

    action_disconnect = new QAction("Disconnect", this);
    connect(action_disconnect,SIGNAL(triggered()), this, SLOT(disconnectSerial()));


    this->ui->menuSerialport->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        this->ui->menuSerialport->addAction(info.portName());
    }

    connect(ui->servoSlider, SIGNAL(valueChanged(int)), bot, SLOT(setServo(int)));
    connect(ui->eggPitch, SIGNAL(valueChanged(int)), bot, SLOT(setPitch(int)));
    connect(ui->eggRoll, SIGNAL(valueChanged(int)), bot, SLOT(setRoll(int)));

    connect(bot, SIGNAL(printPause(QString)), this, SLOT(showPrintMessage(QString)));
    connect(this, SIGNAL(continuePrinting()), bot, SLOT(continuePrinting()));
}

SphereGui::~SphereGui()
{
    bot->disconnectSerial();
    delete ui;
}


void SphereGui::showPrintMessage(QString msg){
    int res = QMessageBox::question(this, "General message", msg, QMessageBox::Ok, QMessageBox::Abort);
        if (res==QMessageBox::Abort){
            bot->cancelPrint();
            return;
        }
        emit continuePrinting();
}

void SphereGui::serialSelected(QAction *action){
    bot->connectSerial(action->text());
    ui->menuSerialport->clear();
    ui->menuSerialport->addAction(action_disconnect);

    ui->btn_sendFile->setEnabled(true);
}

void SphereGui::disconnectSerial(){
    bot->disconnectSerial();

    this->ui->menuSerialport->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        this->ui->menuSerialport->addAction(info.portName());
    }
}


void SphereGui::on_btn_sendFile_clicked()
{
    if (bot->state!=Spherebot::SB_Connected)
        return;

    QFileDialog filedialog(this);
    filedialog.setNameFilter(tr("GCODE (*.gcode);;All Files (*.*)"));
    filedialog.setDirectory(QDir::home());

    QStringList fileNames;
    if (filedialog.exec())
        fileNames = filedialog.selectedFiles();
    if (fileNames.length()!=1)
        return;

    ui->btn_sendFile->setEnabled(false);
    ui->btn_cancel->setEnabled(true);
    bot->sendFile(fileNames[0]);

}

void SphereGui::on_btn_cancel_clicked()
{
    ui->btn_sendFile->setEnabled(true);
    ui->btn_cancel->setEnabled(false);
    bot->cancelPrint();
}
