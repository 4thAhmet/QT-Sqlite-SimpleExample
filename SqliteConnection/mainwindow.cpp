#include "mainwindow.h"
#include "ui_mainwindow.h"
int maxNo = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setEnabled(false);
    refreshTable();
}
void MainWindow::refreshTable()
{
    m = con->GetDatas();
    ui->tableView->setModel(m);
    maxNo=con->getMaxNumber()+1;
    ui->lineEdit->setText(QString::number(maxNo));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    int no = ui->lineEdit->text().toInt();
    QString ad = ui->lineEdit_2->text();
    QString soyad = ui->lineEdit_3->text();
    QString tel = ui->lineEdit_4->text();
    con->addData(maxNo,ad,soyad,tel);
    refreshTable();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    refreshTable();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    int selectedRow = selected.first().row();
    QModelIndex ind = m->index(selectedRow,0);
    qDebug() << "Seçilen no: " << m->data(ind).toInt();
    ui->lineEdit->setText(m->data(ind).toString());
    ind = m->index(selectedRow,1);
    ui->lineEdit_2->setText(m->data(ind).toString());
    ind =m->index(selectedRow,2);
    ui->lineEdit_3->setText(m->data(ind).toString());
    ind = m->index(selectedRow,3);
    ui->lineEdit_4->setText(m->data(ind).toString());

}

void MainWindow::on_pushButton_clicked()
{
    con->updateData(ui->lineEdit->text().toInt(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text());
    refreshTable();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    int selectedrow = selected.first().row();
    QModelIndex index =m->index(selectedrow,0);
    con->deleteData(m->data(index).toInt());
    refreshTable();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

void MainWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
    QString read = ui->lineEdit_4->text();
    read = read.trimmed();
    bool ok;
    double value = read.toDouble(&ok);
    if (!ok){
        qDebug() << "Girilen Değer Sayı Değil!";
        ui->lineEdit_4->setText(read.mid(0,read.count()-1));
    }
    else
    {
        if (read.count()>10)
        {
            qDebug() << "Telefon Nuamrası 10 Haneden Fazla Olamaz!";
            ui->lineEdit_4->setText(read.mid(0,read.count()-1));
        }
        else
            ui->lineEdit_4->setText(read);
    }
}
