#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <iostream>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    AddressDBmodel(new AddressBookModel(this))

{
    ui->setupUi(this);
    ui->addressBookView->setModel(AddressDBmodel);

    // Adds dashes and limits phone number to 10 digits
    ui -> dialerNumber -> setValidator( new QIntValidator(0, 9, this) );
    ui -> dialerNumber -> setInputMask("");
    ui -> dialerNumber -> setInputMask("999-999-9999");
    ui -> dialerNumber -> setMaxLength(10);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAdd_Address_Booklet_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("Address Book (*.csv);;All Files (*)"));

    //std::cout << fileName.toStdString() << std::endl;

    AddressDBmodel->openFile(fileName);
}

void MainWindow::UpdateAddressModelView(){
    QString numToSearch = ui->dialerNumber->text().remove("-");;
    AddressDBmodel->setFilterString(numToSearch);
    std::cout << numToSearch.toStdString() << std::endl;
}

void MainWindow::AddNumToDisplay(QString num){
    ui->dialerNumber->insert(num);
    UpdateAddressModelView();
}

void MainWindow::on_db1_clicked()
{
    AddNumToDisplay(ui ->db1->text());
}

void MainWindow::on_db2_clicked()
{
    AddNumToDisplay(ui ->db2->text());
}

void MainWindow::on_db3_clicked()
{
    AddNumToDisplay(ui ->db3->text());
}

void MainWindow::on_db4_clicked()
{
    AddNumToDisplay(ui ->db4->text());
}

void MainWindow::on_db5_clicked()
{
    AddNumToDisplay(ui ->db5->text());
}

void MainWindow::on_db6_clicked()
{
    AddNumToDisplay(ui ->db6->text());
}

void MainWindow::on_db7_clicked()
{
    AddNumToDisplay(ui ->db7->text());
}

void MainWindow::on_db8_clicked()
{
    AddNumToDisplay(ui ->db8->text());
}

void MainWindow::on_db9_clicked()
{
    AddNumToDisplay(ui ->db9->text());
}

void MainWindow::on_dbStar_clicked()
{
    AddNumToDisplay(ui ->dbStar->text());
}

void MainWindow::on_db0_clicked()
{
    AddNumToDisplay(ui ->db0->text());

}

void MainWindow::on_dbHash_clicked()
{
    AddNumToDisplay(ui ->dbHash->text());
}

void MainWindow::on_backspaceButton_clicked()
{
    ui -> dialerNumber ->backspace();
    UpdateAddressModelView();

}

void MainWindow::on_addressBookView_clicked(const QModelIndex &index)
{
    int row = index.row();
    QString phoneNum = AddressDBmodel->getPhoneNumber(row);
    ui->dialerNumber->setText(phoneNum);
}

void MainWindow::on_callButton_clicked()
{
    if(ui->dialerNumber->text().remove("-").size() == 10){
            QString msg = "Calling now...";
            QMessageBox processed_msg;
            processed_msg.setText(msg);
            processed_msg.exec();

    }
}
