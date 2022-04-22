#include "arduino.h"
#include <QDebug>

arduino::arduino(QObject *parent)
    :QObject {parent}
{
    _serial.setPortName("COM8");
     _serial.setBaudRate(QSerialPort::Baud9600);
      _serial.setDataBits(QSerialPort::Data8);
       _serial.setParity(QSerialPort::NoParity);
       _serial.setFlowControl(QSerialPort::NoFlowControl);

       connect(&_serial,&QSerialPort::readyRead,this,&arduino::newData);


}

arduino::~arduino(){
    closeConnect();
}
void arduino::openConnection()
{
    if(!_serial.open(QIODevice::ReadWrite))
        qDebug() <<"conx impossible";
    else
        qDebug() <<" conx ok";

}

void arduino::write(const char *messageToWrite)
{
    _serial.write(messageToWrite);
}

void arduino::closeConnect(){
    _serial.close();
}

bool arduino::isOpen()
{
    return _serial.isOpen();
}

bool arduino::isWritable()
{
    return  _serial.isWritable();
}


void arduino::newData(){
    emit gotNewData(_serial.readAll());
}
