#include "connection.h"
#include <QtSql>
#include <QFile>

Connection::Connection()
{
    QFile dosya("Test.db");
    if (dosya.exists())
    {
        qDebug("Dosya Var");
    }
    else {
        qDebug("Dosya yok");
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Test.db");
}


QStandardItemModel* Connection::GetDatas()
{
    model = new QStandardItemModel();
    if (!db.isOpen())
    {
        db.open();
    }
    QSqlQuery query("Select * from t_Test" ); // tablename yerine kendi tablonuzun adını yazın
    model->clear();
    model->setHorizontalHeaderLabels({"No","Ad","Soyad","Tel"});
    int row = 0;
    while (query.next()){
        model->insertRow(row);
        model->setData(model->index(row,0), query.value(0));
        model->setData(model->index(row,1), query.value(1));
        model->setData(model->index(row,2), query.value(2));
        model->setData(model->index(row,3), query.value(3));
        row++;
    }
    db.close();
    return model;
}

void Connection::addData(int no,QString Ad,QString Soyad,QString Tel){
    if(!db.isOpen())
        db.open();
    QSqlQuery query;
    query.prepare("insert into t_Test values (:value1, :value2, :value3, :value4)");
    query.bindValue(":value1",no);
    query.bindValue(":value2",Ad);
    query.bindValue(":value3",Soyad);
    query.bindValue(":value4",Tel);
    if(!query.exec())
        qDebug() << "veri eklenemedi\t" << query.lastError();
    else
        qDebug() << "Veri Başarılı Eklendi! \n";
    db.close();
}
int Connection::getMaxNumber(){
    if(!db.isOpen())
        db.open();
    QSqlQuery query;
    int sonuc = 0;
    query.prepare("Select max(no) from t_Test");
    if(query.exec() && query.next())
    {
        sonuc = query.value(0).toInt();
        qDebug() << "Sonuc: " << sonuc;
    }
    db.close();
    return sonuc;
}

void Connection::updateData(int No, QString Ad,QString Soyad, QString Tel)
{
    if(!db.isOpen())
        db.open();
    QSqlQuery query;
    query.prepare("update t_Test SET Ad=:value1, Soyad=:value2, Tel=:value3 Where No=:value4 ");
    query.bindValue(":value1",Ad);
    query.bindValue(":value2",Soyad);
    query.bindValue(":value3",Tel);
    query.bindValue(":value4",No);
    if(!query.exec())
        qDebug() << " Kullanıcı Güncellenemedi.\n";
    else
        qDebug() << No << " Numaralı Kullanıcı Güncellendi.\n";
    db.close();
}
void Connection::deleteData(int No){
    if(!db.isOpen())
        db.open();
    QSqlQuery query;
    query.prepare("Delete from t_Test where No=:value1");
    query.bindValue(":value1",No);
    if(!query.exec())
        qDebug() << "Kullanıcı Silinemedi! \n";
    else
        qDebug() << No << " Numaralı Kullanıcı Silindi!\n";
    db.close();
}
