#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if (ui->lineEdit->text()=="") return;
    QStringListModel *model = new QStringListModel();
    cimkektul[ui->lineEdit->text()]=ui->checkBox->isChecked();
    cimkek<<ui->lineEdit->text();
    model->setStringList(cimkek);
    ui->listView->setModel(model);
    ui->lineEdit->clear();
}


void MainWindow::on_pushButton_2_clicked()
{
    if (ui->lineEdit_2->text()=="" || ui->lineEdit_3->text()=="") return;
    QStringListModel *model = new QStringListModel();
    feltetek<<ui->lineEdit_2->text();
    feltetekar[ui->lineEdit_2->text()]=int(ui->lineEdit_3->text().toInt());
    model->setStringList(feltetek);
    ui->listView_2->setModel(model);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

}


void MainWindow::on_pushButton_3_clicked()
{
    QModelIndex index = ui->listView_2->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();

    QModelIndex index2 = ui->listView->currentIndex();
    QString itemText2 = index2.data(Qt::DisplayRole).toString();
    feltetektul[itemText]<< itemText2;
}


void MainWindow::on_pushButton_4_clicked()
{
    if (ui->lineEdit_4->text()=="") return;
    QStringListModel *model = new QStringListModel();
    pizzak<<ui->lineEdit_4->text();
    model->setStringList(pizzak);
    ui->listView_4->setModel(model);
    ui->lineEdit_4->clear();
}


void MainWindow::on_pushButton_5_clicked()
{
    QModelIndex index = ui->listView_4->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();

    QModelIndex index2 = ui->listView_2->currentIndex();
    QString itemText2 = index2.data(Qt::DisplayRole).toString();
    pizzaktul[itemText]<< itemText2;
}


void MainWindow::on_listView_4_clicked(const QModelIndex &index)
{
    QStringListModel *model = new QStringListModel();
    QString pizza = index.data(Qt::DisplayRole).toString();
    model->setStringList(pizzaktul[pizza]);
    ui->listView_5->setModel(model);

    pizzacheck();
    model = new QStringListModel();
    QStringList tmp;
    for (auto i:pizzacimkek[pizza]){
        tmp<<i;
    }
    model->setStringList(tmp);
    ui->listView_6->setModel(model);
}


void MainWindow::on_listView_2_clicked(const QModelIndex &index)
{
    QStringListModel *model = new QStringListModel();
    QString feltet = index.data(Qt::DisplayRole).toString();
    model->setStringList(feltetektul[feltet]);
    ui->listView_3->setModel(model);
}

void MainWindow::pizzacheck()
{
    pizzacimkek.clear();
    for(auto it=pizzaktul.begin();it!=pizzaktul.end();it++){
        QSet<QString> pizzatmp;
        QSet<QString> pizzatmp2;
        for(auto it2=it.value().begin();it2!=it.value().end();it2++){
            for(auto it3=feltetektul[*it2].begin();it3!=feltetektul[*it2].end();it3++){

                if (cimkektul[*it3]){
                    pizzacimkek[it.key()]<<*it3;
                }else if (it2==it.value().begin()){
                    pizzatmp<<*it3;
                    qInfo()<<"chip" << *it3;
                }else if (pizzatmp.find(*it3)!=pizzatmp.end()){
                    pizzatmp2<<*it3;
                    qInfo("chop");
                }
            }
            if (it2!=it.value().begin()){
                pizzatmp=pizzatmp2;
                pizzatmp2.clear();
            }
        }
        for(auto &i: pizzatmp)
            pizzacimkek[it.key()]<<i;
    }
}
