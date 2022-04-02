QT       += core gui
QT       += core gui
QT       += core gui sql
QT       += network
QT       += core gui charts
QT       += printsupport
QT       += core gui multimedia multimediawidgets
QT       +=svg
QT       += core gui  serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_CXXFLAGS += -std=gnu++11
SOURCES += \
    dumessageconnectiondialog.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    dumessageconnectiondialog.h \
    widget.h

FORMS += \
    dumessageconnectiondialog.ui \
    dumessengerconnectiondialog.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
