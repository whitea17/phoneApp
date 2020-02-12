#ifndef ADDRESSBOOKMODEL_H
#define ADDRESSBOOKMODEL_H


#include <QAbstractTableModel>
#include <vector>

class AddressBookModel: public QAbstractTableModel
{
public:
    AddressBookModel(QObject *parent);
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void openFile(QString filePath);
    QString getPhoneNumber(int index);

    void setFilterString(QString fStr);

private:
    std::vector<QString> firstNames;
    std::vector<QString> lastNames;
    std::vector<QString> phoneNumbers;

    std::vector<int> filteredIndex;

};
#endif // ADDRESSBOOKMODEL_H
