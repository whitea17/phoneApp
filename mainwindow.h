#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addressbookmodel.h"
#include "string"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAdd_Address_Booklet_triggered();

    void on_db1_clicked();
    void on_db2_clicked();
    void on_db3_clicked();
    void on_db4_clicked();
    void on_db5_clicked();
    void on_db6_clicked();
    void on_db7_clicked();
    void on_db8_clicked();
    void on_db9_clicked();

    void on_dbStar_clicked();

    void on_db0_clicked();

    void on_dbHash_clicked();

    void on_backspaceButton_clicked();

private:
    Ui::MainWindow *ui;
    AddressBookModel *AddressDBmodel;
    void AddNumToDisplay(QString num);
    void UpdateAddressModelView();
};
#endif // MAINWINDOW_H
