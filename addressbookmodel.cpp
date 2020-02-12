#include "addressbookmodel.h"

#include <QFile>
#include <QMessageBox>
#include <iostream>
#include <QTextStream>

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
        if (phoneNumbers[i].startsWith(fStr)) {
            filteredIndex.push_back(i);

        }
    }

    emit layoutChanged();
}
