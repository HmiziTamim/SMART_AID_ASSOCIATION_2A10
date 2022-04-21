#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QObject>


class arduino : public QObject
{
    Q_OBJECT
public:     //méthodes de la classe Arduino
    explicit arduino(QObject *parent =nullptr);
    ~arduino();

    void openConnection();
    void closeConnect();
    void write(const char* messageToWrite);
    bool isOpen();
    bool isWritable();



private slots:
    void newData();
signals:
    void gotNewData (QByteArray data);
private:
    QSerialPort _serial;

};



#endif // ARDUINO_H
