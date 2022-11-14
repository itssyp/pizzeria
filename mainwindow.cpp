#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include "QFileDialog"
#include "QErrorMessage"

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
    if (ui->lineEdit->text()=="") {
       QErrorMessage *msg= new QErrorMessage;
       msg->showMessage("Baz");

       return;
    }
    QStringListModel *model = new QStringListModel();
    cimkektul[ui->lineEdit->text()]=ui->checkBox->isChecked();
    cimkek<<ui->lineEdit->text();
    model->setStringList(cimkek);
    ui->listView->setModel(model);
    ui->lineEdit->clear();
    model = new QStringListModel();
    QStringList tmp=cimkek;
    tmp << "Minden";
    model->setStringList(tmp);
    ui->comboBox->setModel(model);
}


void MainWindow::on_pushButton_2_clicked()
{
    if (ui->lineEdit_2->text()=="" || ui->lineEdit_3->text()=="") {
        QErrorMessage *msg= new QErrorMessage;
        msg->showMessage("Baz");
        return;
    }
    QStringListModel *model = new QStringListModel();
    feltetek<<ui->lineEdit_2->text();
    feltetekar[ui->lineEdit_2->text()]=int(ui->lineEdit_3->text().toInt());
    model->setStringList(convert(feltetek));
    ui->listView_2->setModel(model);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    model = new QStringListModel();
    model->setStringList(prices());
    ui->listView_7->setModel(model);

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
    if (ui->lineEdit_4->text()=="") {
        QErrorMessage *msg= new QErrorMessage;
        msg->showMessage("Baz");
        return;
    }
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
                }else if (pizzatmp.find(*it3)!=pizzatmp.end()){
                    pizzatmp2<<*it3;
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

void MainWindow::on_actionMentes_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Mentes"), "/users/sheep/Documents/Qt/Pizzeria", tr("*.txt"));
    QFile f(fileName);
    if(f.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&f);
    out << ui->lineEdit_5->text() << "\n" << ui->lineEdit_6->text() << "\n"
        << ui->lineEdit_7->text() << "\n" << ui->lineEdit_8->text() << "\n";
    for (auto i:cimkek) out << i << ";";
    out << "\n";
    for (auto i:feltetek) out << i << ";";
    out << "\n";
    for (auto i:pizzak) out << i << ";";
    out << "\n";
    for (auto it=cimkektul.begin();it!=cimkektul.end();it++) {
        out << it.key() << ":" << it.value() << ";";
    }
    out << "\n";
    for (auto it=feltetektul.begin();it!=feltetektul.end();it++) {
        out << it.key() << ":";
        for (auto it2=it.value().begin();it2!=it.value().end();it2++){
            out << *it2 << ",";
        }
        out << ";";
    }
    out << "\n";
    for (auto it=feltetekar.begin();it!=feltetekar.end();it++) {
        out << it.key() << ":" << it.value() << ";";
    }
    out << "\n";
    for (auto it=pizzaktul.begin();it!=pizzaktul.end();it++) {
        out << it.key() << ":";
        for (auto it2=it.value().begin();it2!=it.value().end();it2++){
            out << *it2 << ",";
        }
        out << ";";
    }
    out << "\n";
    for (auto it=pizzacimkek.begin();it!=pizzacimkek.end();it++) {
        out << it.key() << ":";
        for (auto it2=it.value().begin();it2!=it.value().end();it2++){
            out << *it2 << ",";
        }
        out << ";";
    }
    out << "\n";

    }
}


void MainWindow::on_actionMegnyitas_triggered()
{
    cimkek.clear();
    feltetek.clear();
    pizzak.clear();
    cimkektul.clear();
    feltetektul.clear();
    feltetekar.clear();
    pizzaktul.clear();
    pizzacimkek.clear();
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Megnyitas"), "/users/sheep/Documents/Qt/Pizzeria", tr("*.txt"));
    QFile f(fileName);
    if(f.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&f);
    ui->lineEdit_5->setText(in.readLine());
    ui->lineEdit_6->setText(in.readLine());
    ui->lineEdit_7->setText(in.readLine());
    ui->lineEdit_8->setText(in.readLine());
    std::stringstream ss(in.readLine().toStdString());
    std::string s;
    char c;
    while (std::getline(ss,s,';')) cimkek << QString::fromLocal8Bit(s.c_str());
    ss.str("");
    ss.clear();
    ss << in.readLine().toStdString();
    while (std::getline(ss,s,';')) feltetek << QString::fromLocal8Bit(s.c_str());
    ss.str("");
    ss.clear();
    ss << in.readLine().toStdString();
    while (std::getline(ss,s,';')) pizzak << QString::fromLocal8Bit(s.c_str());
    ss.str("");
    ss.clear();
    ss << in.readLine().toStdString();
    while (std::getline(ss,s,':')){
        bool b;
        ss >> b;
        cimkektul[QString::fromLocal8Bit(s.c_str())]=b;
        ss >> c;
    }
    ss.str("");
    ss.clear();
    ss << in.readLine().toStdString();
    while (std::getline(ss,s,';')){
        std::stringstream ss2(s);
        std::string tmp;
        std::getline(ss2,tmp,':');
        while (std::getline(ss2,s,',')){
             feltetektul[QString::fromLocal8Bit(tmp.c_str())]<<QString::fromLocal8Bit(s.c_str());
        }
    }
    ss.str("");
    ss.clear();
    ss << in.readLine().toStdString();
    while (std::getline(ss,s,':')){
        int a;
        ss >> a;
        feltetekar[QString::fromLocal8Bit(s.c_str())]=a;
        ss >> c;
        qInfo() << QString::fromLocal8Bit(s.c_str()) << " " << a;
    }
    ss.str("");
    ss.clear();
    ss << in.readLine().toStdString();
    while (std::getline(ss,s,';')){
        std::stringstream ss2(s);
        std::string tmp;
        std::getline(ss2,tmp,':');
        while (std::getline(ss2,s,',')){
             pizzaktul[QString::fromLocal8Bit(tmp.c_str())]<<QString::fromLocal8Bit(s.c_str());
        }
    }
    ss.str("");
    ss.clear();
    ss << in.readLine().toStdString();
    while (std::getline(ss,s,';')){
        std::stringstream ss2(s);
        std::string tmp;
        std::getline(ss2,tmp,':');
        while (std::getline(ss2,s,',')){
             pizzacimkek[QString::fromLocal8Bit(tmp.c_str())]<<QString::fromLocal8Bit(s.c_str());
        }
    }
    }
    QStringListModel *model = new QStringListModel();
    model->setStringList(cimkek);
    ui->listView->setModel(model);
    model = new QStringListModel();
    model->setStringList(convert(feltetek));
    ui->listView_2->setModel(model);
    model = new QStringListModel();
    model->setStringList(pizzak);
    ui->listView_4->setModel(model);
    model = new QStringListModel();
    QStringList tmp=cimkek;
    tmp << "Minden";
    model->setStringList(tmp);
    ui->comboBox->setModel(model);
    model = new QStringListModel();
    model->setStringList(prices());
    ui->listView_7->setModel(model);
}


void MainWindow::on_comboBox_activated(int index)
{
    QStringListModel *model = new QStringListModel();
    QStringList tmp;
    QStringList tmp3;
    if (ui->comboBox->currentText()=="Minden"){
        tmp=convert(feltetek);
        model->setStringList(tmp);
        ui->listView_2->setModel(model);
        for (auto it=feltetek.begin();it!= feltetek.end();it++){
            tmp3 << QString::number(feltetekar[*it]);
        }
        model = new QStringListModel();
        model->setStringList(tmp3);
        ui->listView_7->setModel(model);
        return;
    } else
    for (auto i: feltetek){
        QSet<QString> tmp2;
        for (auto j: feltetektul[i]){
            tmp2<<j;
        }
        if (tmp2.find(ui->comboBox->currentText())!=tmp2.end()){
            tmp << i;
            tmp3 << QString::number(feltetekar[i]);
        }
    }
    model->setStringList(tmp);
    ui->listView_2->setModel(model);
    model = new QStringListModel();
    model->setStringList(tmp3);
    ui->listView_7->setModel(model);

}

QStringList MainWindow::prices(){
    QStringList price;
    for(auto it=feltetek.begin();it!=feltetek.end();it++){
        price<< QString::number(feltetekar[*it]);
    }
    return price;
}

int MainWindow::pizzaar(QString pizza){
    int sum=ui->lineEdit_7->text().toInt();
    QSet<QString> tmp;
    for (auto i:pizzaktul[pizza]){
        tmp << i;
    }
    for (auto it=feltetekar.begin();it!= feltetekar.end(); it++){
        if (tmp.find(it.key())!=tmp.end()) sum+=feltetekar[it.key()];
        qInfo()<< it.key() << ": " << it.value() << "\n";
    }
    qInfo () << sum;
    return sum;
}

QStringList MainWindow::convert(QSet<QString> st){
    QStringList tmp;
    for (auto i:st) tmp << i;
    return tmp;
}

void MainWindow::on_pushButton_6_clicked()
{
    QFile f("index.html");
    qInfo("hi");
    if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
       QTextStream out(&f);
       out << "<!DOCTYPE html\n"
           << "<html>\n"
           << "<body>\n"
           << "<h1>"
           << ui->lineEdit_5->text()
           << "</h1>\n"
           << "<p>"
           << "Nyitvatartas: "
           << ui->lineEdit_6->text()
           << "</p>"
           << "<p>"
           << "Szallitasi koltseg: "
           << ui->lineEdit_7->text()+"jmf"
           << "</p>"
           << "<p>"
           << "<bold>"
           << "Etlap:\n<br>"
           << "</bold>";
       for (auto it=pizzaktul.begin();it!=pizzaktul.end();it++){
           out << it.key() +":\n <br>";
           for (auto it2=it.value().begin(); it2!=it.value().end();it2++){
               out << *it2 << " - " << feltetekar[*it2] << "jmf \n <br>";
           }
           out << "Ar: " << pizzaar(it.key());
           out << "\n <br>";
           for (auto it2=pizzacimkek[it.key()].begin(); it2!=pizzacimkek[it.key()].end();it2++){
               out << *it2 << ", ";
           }
           out << "\n <br><br>";
       }

       out << "</p>"

           << "</body>"
           << "</html>";
    }
}

