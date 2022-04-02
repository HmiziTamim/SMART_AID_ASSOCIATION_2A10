/********************************************************************************
** Form generated from reading UI file 'dumessageconnectiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DUMESSAGECONNECTIONDIALOG_H
#define UI_DUMESSAGECONNECTIONDIALOG_H

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

class Ui_DuMessageConnectionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *hostname;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *port;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *ok;
    QPushButton *cancel;

    void setupUi(QDialog *DuMessageConnectionDialog)
    {
        if (DuMessageConnectionDialog->objectName().isEmpty())
            DuMessageConnectionDialog->setObjectName(QString::fromUtf8("DuMessageConnectionDialog"));
        DuMessageConnectionDialog->resize(799, 211);
        verticalLayout = new QVBoxLayout(DuMessageConnectionDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DuMessageConnectionDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        hostname = new QLineEdit(DuMessageConnectionDialog);
        hostname->setObjectName(QString::fromUtf8("hostname"));

        horizontalLayout->addWidget(hostname);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(DuMessageConnectionDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        port = new QSpinBox(DuMessageConnectionDialog);
        port->setObjectName(QString::fromUtf8("port"));
        port->setMaximum(9999999);

        horizontalLayout_2->addWidget(port);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(258, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        ok = new QPushButton(DuMessageConnectionDialog);
        ok->setObjectName(QString::fromUtf8("ok"));

        horizontalLayout_3->addWidget(ok);

        cancel = new QPushButton(DuMessageConnectionDialog);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        horizontalLayout_3->addWidget(cancel);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(DuMessageConnectionDialog);

        QMetaObject::connectSlotsByName(DuMessageConnectionDialog);
    } // setupUi

    void retranslateUi(QDialog *DuMessageConnectionDialog)
    {
        DuMessageConnectionDialog->setWindowTitle(QCoreApplication::translate("DuMessageConnectionDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DuMessageConnectionDialog", "Hostname", nullptr));
        label_2->setText(QCoreApplication::translate("DuMessageConnectionDialog", "Port", nullptr));
        ok->setText(QCoreApplication::translate("DuMessageConnectionDialog", "Accept", nullptr));
        cancel->setText(QCoreApplication::translate("DuMessageConnectionDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DuMessageConnectionDialog: public Ui_DuMessageConnectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DUMESSAGECONNECTIONDIALOG_H
