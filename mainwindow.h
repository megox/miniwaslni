#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <stack>
#include <set>
#include <fstream>
#include<QStackedWidget>
#include <QMainWindow>
#include <vector>
#include <unordered_set>
#include<string>
#include<iostream>
#include<QPixmap>
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include <stack>
#include <queue>
#include <fstream>
#include <QDebug>
#include <QLabel>


using namespace std;



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool bfs(string city1, string city2);
    void dfs(string node);
    void write_in_file();
    void read_file();
    ~MainWindow();

    unordered_map<string, vector<pair<string, int>>>adjlist;
    unordered_set<string>list;
    unordered_map<string,bool>isexist;
    unordered_map<string, bool>vis;
    vector<string>trv_dfs;
    unordered_map<string,bool>road_of_city;
    const int N = 1e9;

private slots:
    void on_addgraph_clicked();

    void on_update_clicked();

    void on_exit1_clicked();


    void on_exit2_clicked();
    void on_back2_clicked();

    void on_exit3_clicked();
    void on_back3_clicked();


    void on_exit4_clicked();
    void on_back4_clicked();


    void on_deletegraph_clicked();

    void on_add_g_clicked();


    void on_addedge_clicked();


    void on_addcity_clicked();

    void on_delete1_clicked();

    void on_delete2_clicked();

    void on_display_2_clicked();

    void on_exit5_clicked();

    void on_back5_clicked();

    void on_display_clicked();

    void on_exit6_clicked();

    void on_checkroad_clicked();

    void on_back6_clicked();

    void on_find_clicked();

    void on_exit7_clicked();


    void on_travrseputton_clicked();

    void on_back7_clicked();

    void on_travrsegraph_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
