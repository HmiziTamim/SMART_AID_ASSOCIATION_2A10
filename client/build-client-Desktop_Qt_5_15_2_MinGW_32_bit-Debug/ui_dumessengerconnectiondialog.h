/********************************************************************************
** Form generated from reading UI file 'dumessengerconnectiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DUMESSENGERCONNECTIONDIALOG_H
#define UI_DUMESSENGERCONNECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *port;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *hostname;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *ok;
    QPushButton *cancel;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(744, 161);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        port = new QSpinBox(Dialog);
        port->setObjectName(QString::fromUtf8("port"));

        horizontalLayout_2->addWidget(port);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        hostname = new QLineEdit(Dialog);
        hostname->setObjectName(QString::fromUtf8("hostname"));

        horizontalLayout->addWidget(hostname);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(358, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        ok = new QPushButton(Dialog);
        ok->setObjectName(QString::fromUtf8("ok"));

        horizontalLayout_3->addWidget(ok);

        cancel = new QPushButton(Dialog);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        horizontalLayout_3->addWidget(cancel);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "port", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Hostname", nullptr));
        ok->setText(QCoreApplication::translate("Dialog", "Accept", nullptr));
        cancel->setText(QCoreApplication::translate("Dialog", "cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DUMESSENGERCONNECTIONDIALOG_H
