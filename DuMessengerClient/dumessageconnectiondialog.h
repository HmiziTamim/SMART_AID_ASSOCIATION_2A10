#ifndef DUMESSAGECONNECTIONDIALOG_H
#define DUMESSAGECONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class DuMessageConnectionDialog;
}

class DuMessageConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DuMessageConnectionDialog(QWidget *parent = nullptr);
    ~DuMessageConnectionDialog();
    QString hostname() const;
    quint16 port() const;
private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::DuMessageConnectionDialog *ui;
    QString mHostname;
    quint16 mPort;
};
inline QString DuMessageConnectionDialog:: hostname()const
{
    return mHostname;
}
inline quint16 DuMessageConnectionDialog::port()const
{
    return mPort;
}
#endif // DUMESSAGECONNECTIONDIALOG_H
