#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql>
#include <QStandardItemModel>
class Connection
{
public:
    Connection();
    QSqlDatabase db;
    QStandardItemModel *model;
    QStandardItemModel* GetDatas();
    void addData(int no,QString Ad,QString Soyad,QString Tel);
    int getMaxNumber();
    void updateData(int no,QString Ad,QString Soyad,QString Tel);
    void deleteData(int No);
};

#endif // CONNECTION_H
