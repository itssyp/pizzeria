#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "QSet"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_listView_4_clicked(const QModelIndex &index);

    void on_listView_2_clicked(const QModelIndex &index);

    void pizzacheck();

    void on_actionMentes_triggered();

    void on_actionMegnyitas_triggered();

    void on_comboBox_activated(int index);

    QStringList prices();

    int pizzaar(QString pizza);

    QStringList convert (QSet<QString> st);

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    QStringList cimkek;
    QSet<QString> feltetek;
    QStringList pizzak;
    QMap<QString,bool> cimkektul;
    QMap<QString,QStringList> feltetektul;
    QMap<QString,int> feltetekar;
    QMap<QString,QStringList> pizzaktul;
    QMap<QString,QSet<QString>> pizzacimkek;
};
#endif // MAINWINDOW_H
