#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <iostream>

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
