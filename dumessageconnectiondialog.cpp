#include "dumessageconnectiondialog.h"
#include "ui_dumessageconnectiondialog.h"

DuMessageConnectionDialog::DuMessageConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuMessageConnectionDialog)
{
    ui->setupUi(this);
}

DuMessageConnectionDialog::~DuMessageConnectionDialog()
{
    delete ui;
}

void DuMessageConnectionDialog::on_ok_clicked()
{
    mHostname=ui->hostname->text();
    mPort=ui->port->value();
    accept();
}


void DuMessageConnectionDialog::on_cancel_clicked()
{
    reject();
}

