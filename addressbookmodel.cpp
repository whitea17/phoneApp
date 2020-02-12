#include "addressbookmodel.h"

#include <QFile>
#include <QMessageBox>
#include <iostream>
#include <QTextStream>
#include <stdio.h>

AddressBookModel::AddressBookModel(QObject *parent)
    :QAbstractTableModel (parent)
{

}

int AddressBookModel::rowCount(const QModelIndex &parent) const
{
    return filteredIndex.size();
}

int AddressBookModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant AddressBookModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {

        // stops program from crashing
        if(index.row() >= firstNames.size()-1){
            return QVariant();
        }

        switch(index.column()) {
        case 0:
            return firstNames.at(filteredIndex[index.row()]);
        case 1:
            return lastNames.at(filteredIndex[index.row()]);
        case 2:
            return phoneNumbers.at(filteredIndex[index.row()]);
        }

    }

    return QVariant();
}

void AddressBookModel::openFile(QString filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
        return;
    }

    QTextStream in(&file);

    firstNames.clear();
    lastNames.clear();
    phoneNumbers.clear();

    for(int i = 0; !in.atEnd(); i++) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (i == 0) continue;

//        for(int j = 0; j < fields.length(); j++) {
//            std::cout << "[" << j << "]" << fields[j].toStdString();
//        }
//        std::cout << std::endl;

        firstNames.push_back(fields[0]);
        lastNames.push_back(fields[1]);
        phoneNumbers.push_back(fields[7]);
        nameInNumbers.push_back(nameToNum(fields[0]+fields[1]));

        filteredIndex.push_back(i);
    }

    file.close();

    emit layoutChanged();
}

QString AddressBookModel::getPhoneNumber(int index)
{
    return phoneNumbers.at(filteredIndex[index]);
}

void AddressBookModel::setFilterString(QString fStr)
{
    filteredIndex.clear(); // empty filtered list and start over

    // check if phone numbers fit with the filter string.
    for (int i = 0; i < phoneNumbers.size(); i++) {
        if (phoneNumbers[i].remove("-").startsWith(fStr) || nameInNumbers[i].contains(fStr) ) {
            filteredIndex.push_back(i);

        }
    }

    emit layoutChanged();
}

QString AddressBookModel::nameToNum(QString name){
    QString num = "";
    std::string sName = name.toStdString();
    std::string two = "abc";
    std::string three = "def";
    std::string four = "ghi";
    std::string five = "jkl";
    std::string six = "mno";
    std::string seven = "pqrs";
    std::string eight = "tuv";
    std::string nine = "wxyz";

    for(size_t i = 0; i < sName.size(); i++){
        if(two.find(tolower(sName.at(i))) != std::string::npos){
            num += "2";
        }else if(three.find(tolower(sName.at(i))) != std::string::npos){
            num += "3";
        }else if(four.find(tolower(sName.at(i))) != std::string::npos){
            num += "4";
        }else if(five.find(tolower(sName.at(i))) != std::string::npos){
            num += "5";
        }else if(six.find(tolower(sName.at(i))) != std::string::npos){
            num += "6";
        }else if(seven.find(tolower(sName.at(i))) != std::string::npos){
            num += "7";
        }else if(eight.find(tolower(sName.at(i))) != std::string::npos){
            num += "8";
        }else if(nine.find(tolower(sName.at(i))) != std::string::npos){
            num += "9";
        }
    }

    return num;
}
