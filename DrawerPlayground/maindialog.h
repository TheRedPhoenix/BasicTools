#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QTabWidget>

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(QWidget *parent = 0);
    ~MainDialog();

private:

    QWidget * createWarningLabelWidget();
    QWidget * createErrorLabelWidget();
    QWidget * createHandWidget();

    QTabWidget * m_tabWidget;
};

#endif // MAINDIALOG_H
