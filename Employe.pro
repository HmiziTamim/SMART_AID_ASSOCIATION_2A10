QT       += core gui sql network
QT       += core gui sql printsupport charts
QT       += core gui \
                      multimedia
QT       +=charts
QT       += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connection.cpp \
    dumessageconnectiondialog.cpp \
    employe.cpp \
    evenement.cpp \
    historique.cpp \
    main.cpp \
    mainwindow.cpp \
    patient.cpp \
    qrcode.cpp \
    smtp.cpp \
    stock.cpp \
    volontaire.cpp

HEADERS += \
    arduino.h \
    connection.h \
    dumessageconnectiondialog.h \
    employe.h \
    evenement.h \
    historique.h \
    mainwindow.h \
    patient.h \
    qrcode.h \
    smtp.h \
    stock.h \
    volontaire.h

FORMS += \
    dumessageconnectiondialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    images.qrc \
    qml.qrc \
    sound.qrc \
    sound.qrc

DISTFILES += \
    &&&&&&&&&.png \
    0f37677142166b7c7b4e2d2ca8961a4d.jpg \
    124200-red-and-orange-shiny-metallic-background.jpg \
    524079c5b4cafc69d4ecbdf18beb9ed2.jpg \
    84380.png \
    Atelier_Connexion.pro.user \
    Atelier_Connexion.pro.user.d567f1b.4.8-pre1 \
    Employe.pro.qtds \
    Employe.pro.user \
    Employe.pro.user.71f237f \
    README.md \
    aa.jpg \
    aaa.png \
    aaaaa.png \
    add.png \
    ae.png \
    ajout succe.mp3 \
    aze.png \
    bb.png \
    bbb.png \
    bbbb.png \
    carte.png \
    charts1.png \
    default-profile-icon-24.jpg \
    delete.png \
    eee.png \
    eee7.png \
    ent.png \
    fond-gris-peint_53876-94041.jpg \
    fond-hexagonal-fonce-degrade-couleur_79603-1410.jpg \
    free-search-icon-3076-thumb.png \
    image.jpg \
    inf.png \
    istockphoto-1132593892-612x612.jpg \
    istockphoto-1157432768-612x612.jpg \
    istockphoto-587220352-170667a.jpg \
    log.png \
    logo2.png \
    map.qml \
    q.png \
    refresh.PNG
