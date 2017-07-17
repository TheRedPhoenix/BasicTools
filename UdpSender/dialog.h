#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "udpsender.h"
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();


private:

    UdpSender * m_sender;
};

#endif // DIALOG_H
