#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    read_file();
}


MainWindow::~MainWindow()
{
    delete ui;
    write_in_file();
}

bool MainWindow ::bfs(string city1, string city2) {
    vis.clear();
    queue <string> q;
    bool check = 0;
    q.push(city1);
    vis[city1] = true;

    while (!q.empty()) {
        string node = q.front();
        q.pop();

        for (int j = 0; j < adjlist[node].size(); j++) {
            if (!vis[adjlist[node][j].first]) {
                if (adjlist[node][j].first == city2)check = 1;
                q.push(adjlist[node][j].first);
                vis[adjlist[node][j].first] = true;
            }
        }
    }
    return check;
}
void MainWindow :: dfs(string node) {
    vis[node] = true;
    trv_dfs.push_back(node);
    for (int j = 0; j < adjlist[node].size(); j++) {
        if (!vis[adjlist[node][j].first])
            dfs(adjlist[node][j].first);
    }
}
void MainWindow :: write_in_file(){
    ofstream fout;
    fout.open("C:/Users/momoa/OneDrive/Desktop/pro/test.txt", ios::out);
    unordered_set<string>::iterator i;
    for (i = list.begin(); i != list.end(); i++) {
        for (int j = 0; j < adjlist[*i].size(); j++) {
                fout << *i << ' ' << adjlist[*i][j].first << ' ' << adjlist[*i][j].second << "\n";
        }
    }
    fout.close();
}
void MainWindow :: read_file(){
    ifstream infile("C:/Users/momoa/OneDrive/Desktop/pro/test.txt");
    string a, b;
    int c;
    while (infile >> a >> b >> c) {
        adjlist[a].push_back(make_pair(b, c));
        if (a != "0") list.insert(a);
        if (b != "0") list.insert(b);
        isexist[a]=true;
        isexist[b]=true;
    }
    infile.close();
}
////////////////////////////////////////////////////////
//main window puttons
void MainWindow::on_addgraph_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_find_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_update_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_deletegraph_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_exit1_clicked()
{
    this->close();
}
void MainWindow::on_display_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}

void MainWindow::on_travrsegraph_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}
/////////////////////////////////////////////////////////
//page2(add)
void MainWindow::on_exit2_clicked()
{
    this->close();
}
void MainWindow::on_back2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_add_g_clicked()
{
    if(ui->checkBox->isChecked()){

        string text = ui->textEdit->toPlainText().toStdString();
        string s;
        vector<string>edge;

        for (int i = 0; i < text.size(); i++) {
            if (text[i] == ' ' || text[i] == '\xa') {
                edge.push_back(s);
                s.clear();
            }
            else  s+=text[i];
            if (edge.size() % 3 == 0 && edge.size() > 0) {
                int x = stoi(edge[2]);
                qDebug()<<edge[0]<<' '<<edge[1]<<' '<<x<<"\n";
                adjlist[edge[0]].push_back({ edge[1],x });
                list.insert(edge[0]);
                list.insert(edge[1]);
                isexist[edge[0]]=true;
                isexist[edge[1]]=true;
                edge.clear();
            }
        }
       QMessageBox::about(this, "", "Directed Graph added SUCCESSFULLY!");

    }
    else{

       string text = ui->textEdit->toPlainText().toStdString();
       string s;
       vector<string>edge;

       for (int i = 0; i < text.size(); i++) {
            if (text[i] == ' ' || text[i] == '\xa') {
                edge.push_back(s);
                s.clear();
            }
            else  s+=text[i];
            if (edge.size() % 3 == 0 && edge.size() > 0) {
                int x = stoi(edge[2]);
                qDebug()<<edge[0]<<' '<<edge[1]<<' '<<x<<"\n";
                adjlist[edge[0]].push_back({ edge[1],x });
                adjlist[edge[1]].push_back({ edge[0],x });
                list.insert(edge[0]);
                list.insert(edge[1]);
                isexist[edge[0]]=true;
                isexist[edge[1]]=true;
                edge.clear();
            }
       }
       QMessageBox::about(this, "", "undirected Graph added SUCCESSFULLY!");
    }
}
/////////////////////////////////////////////////////////
//page3(update)
void MainWindow::on_exit3_clicked()
{
    this->close();

}

void MainWindow::on_back3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_addedge_clicked()
{

    if(ui->checkBox_2->isChecked()){
       string a = ui->a->text().toStdString();
       string b = ui->b->text().toStdString();
       string c = ui->c->text().toStdString();
       int x = stoi(c);
       adjlist[a].push_back({b,x});
       list.insert(a);
       list.insert(b);
       isexist[a] = true;
       isexist[b] = true;
       QMessageBox::about(this, "", "Directed edge added SUCCESSFULLY!");
    }
    else{
       string a = ui->a->text().toStdString();
       string b = ui->b->text().toStdString();
       string c = ui->c->text().toStdString();
       int x = stoi(c);
       adjlist[a].push_back({b,x});
       adjlist[b].push_back({a,x});
       list.insert(a);
       list.insert(b);
       isexist[a] = true;
       isexist[b] = true;
       QMessageBox::about(this, "", "Undirected edge added SUCCESSFULLY!");
    }
}
void MainWindow::on_addcity_clicked()
{
    string a = ui->c_2->text().toStdString();
    if(!adjlist[a].empty()){
        QMessageBox::warning(this, "Warning", "This city is already exist in your graph!");
    }
    else{
       adjlist[a].push_back({"0",0});
       list.insert(a);
       isexist[a] = true;
       QMessageBox::about(this, "", "City added SUCCESSFULLY!");
    }
}
/////////////////////////////////////////////////////////
//page4(delete)

void MainWindow::on_exit4_clicked()
{
    this->close();
}

void MainWindow::on_back4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_delete1_clicked()
{
    string city = ui->delete_1_input->text().toStdString();

    if(!isexist[city]){
       QMessageBox::warning(this, "Warning", "This city dosen't exist in your graph!");
    }
    else{
       road_of_city.clear();
       unordered_set<string>::iterator i;
       for (i = list.begin(); i != list.end(); i++) {
            for (int j = 0; j < adjlist[*i].size(); j++) {
                if (*i == city || adjlist[*i][j].first == city) {
                    adjlist[*i].erase(adjlist[*i].begin() + j);
                }
            }
       }
       list.erase(city);
       isexist[city] = false;
       for (i = list.begin(); i != list.end(); i++) {
            if(!adjlist[*i].empty())road_of_city[*i]=true;
            for (int j = 0; j < adjlist[*i].size(); j++) {
                road_of_city[adjlist[*i][j].first]=true;
            }
       }
       for (i = list.begin(); i != list.end(); i++) {
            if(road_of_city[*i]==false)adjlist[*i].push_back({"0",0});
        }

       QMessageBox::about(this, "", "City Deleted SUCCESSFULLY!");
    }
}

void MainWindow::on_delete2_clicked()
{

    if(ui->checkBoxdel->isChecked()){
        road_of_city.clear();
       bool check = false;
       string city1 = ui->delete_2_1_input->text().toStdString();
       string city2 = ui->delete_2_2_input->text().toStdString();
       unordered_set<string>::iterator i;
       for (i = list.begin(); i != list.end(); i++) {
            for (int j = 0; j < adjlist[*i].size(); j++) {
                if ((*i == city1 && adjlist[*i][j].first == city2)) {
                    check = true;
                    adjlist[*i].erase(adjlist[*i].begin() + j);
                }

            }
       }
       for (i = list.begin(); i != list.end(); i++) {
            if(!adjlist[*i].empty())road_of_city[*i]=true;
            for (int j = 0; j < adjlist[*i].size(); j++) {
                road_of_city[adjlist[*i][j].first]=true;
            }
       }
       for (i = list.begin(); i != list.end(); i++) {
            if(road_of_city[*i]==false)adjlist[*i].push_back({"0",0});
       }
       if(check){
            QMessageBox::about(this, "", "Road deleted SUCCESSFULLY!");
       }
       else{
            QMessageBox::warning(this, "Warning", "This road is dosn't exist in your graph!");
       }
    }
    else{
        road_of_city.clear();
       bool check = false;
       string city1 = ui->delete_2_1_input->text().toStdString();
       string city2 = ui->delete_2_2_input->text().toStdString();
       unordered_set<string>::iterator i;
       for (i = list.begin(); i != list.end(); i++) {
            for (int j = 0; j < adjlist[*i].size(); j++) {
                if ((*i == city1 && adjlist[*i][j].first == city2)||(*i == city2 && adjlist[*i][j].first == city1)) {
                    check = true;
                    adjlist[*i].erase(adjlist[*i].begin() + j);
                }

            }
       }
       for (i = list.begin(); i != list.end(); i++) {
            if(!adjlist[*i].empty())road_of_city[*i]=true;
            for (int j = 0; j < adjlist[*i].size(); j++) {
                road_of_city[adjlist[*i][j].first]=true;
            }
       }
       for (i = list.begin(); i != list.end(); i++) {
            if(road_of_city[*i]==false)adjlist[*i].push_back({"0",0});
       }
       if(check){
            QMessageBox::about(this, "", "Road deleted SUCCESSFULLY!");
       }
       else{
            QMessageBox::warning(this, "Warning", "This road is dosn't exist in your graph!");
       }

    }

}

/////////////////////////////////////////////////////////
//page5(display)
void MainWindow::on_exit5_clicked()
{
    this->close();
}

void MainWindow::on_back5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_display_2_clicked()
{
    write_in_file();
    QFile file("C:/Users/momoa/OneDrive/Desktop/pro/test.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        ui->dis->setText(in.readAll());
        file.close();
    }
}

/////////////////////////////////////////////////////////
//page6(check road)
void MainWindow::on_exit6_clicked()
{
    this->close();
}

void MainWindow::on_back6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_checkroad_clicked()
{

    string city1 = ui->check_input_1->toPlainText().toStdString();
    string city2 = ui->check_input_2->toPlainText().toStdString();

    if (bfs(city1, city2)){
        vis.clear();
        map<string, int>dist;
        unordered_set<string>::iterator i;
        for (i = list.begin(); i != list.end(); i++)dist[*i] = N;
        map<string, string> pre;
        priority_queue<pair<int, string>>nexttovisit;
        dist[city1] = 0;
        pre[city1] = city1;
        nexttovisit.push({ 0,city1 });
        while (!nexttovisit.empty()) {

            string u = nexttovisit.top().second;
            nexttovisit.pop();
            if (vis[u])
                continue;
            vis[u] = 1;
            for (auto e : adjlist[u]) {
                string v = e.first;
                int c = e.second;
                if (dist[u] + c < dist[v]) {
                    dist[v] = dist[u] + c;
                    pre[v] = u;
                    nexttovisit.push({ -dist[v],v });
                }
            }
        }
        stack<string>display_path;
        display_path.push(city2);
        ofstream fout;
        fout.open("C:/Users/momoa/OneDrive/Desktop/pro/test_2.txt", ios::out);
        fout << "The distance from "<<city1<<" to "<<city2 <<" is : " << dist[city2] << ' ' << endl;
        while (true) {
            if (pre[city2] != city1)display_path.push(pre[city2]);
            else break;
            city2 = pre[city2];
        }
        display_path.push(city1);
        fout << "The path is : ";
        while (!display_path.empty()) {
            fout << display_path.top()<<"  ";
            display_path.pop();
        }
        fout.close();


        QFile file("C:/Users/momoa/OneDrive/Desktop/pro/test_2.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->shortestpathdisplay->setText(in.readAll());
            file.close();
        }
    }
    else{
        QMessageBox::warning(this, "Warning", "There is no road between this two cities!");
    }



}


/////////////////////////////////////////////////////////
//page7(travrse)
void MainWindow::on_exit7_clicked()
{
    this->close();
}
void MainWindow::on_back7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_travrseputton_clicked()
{
    write_in_file();
    vis.clear();
    ofstream fout;
    fout.open("C:/Users/momoa/OneDrive/Desktop/pro/test_bfs.txt", ios::out);
    queue<string> q;
    unordered_set<string>::iterator i;
    for(i =list.begin();i!=list.end();i++){
        if(!vis[*i]){
            q.push(*i);
            fout << *i <<endl;
            vis[*i] = true;
            while (!q.empty()) {
                string node = q.front();
                q.pop();
                for (auto e : adjlist[node]) {
                    string child = e.first;
                    if (!vis[child]) {
                        q.push(child);
                        if(child!="0")fout << child << endl;
                        vis[child] = true;
                    }
                }
            }
        }
    }
    fout.close();
    vis.clear();
    trv_dfs.clear();
    ofstream foutt;
    foutt.open("C:/Users/momoa/OneDrive/Desktop/pro/test_dfs.txt", ios::out);
    for(i =list.begin();i!=list.end();i++){
        if(!vis[*i])dfs(*i);
    }
    for(int j=0;j<trv_dfs.size();j++) {if(trv_dfs[j]!="0")foutt<<trv_dfs[j]<<endl;}
    foutt.close();



    QFile file("C:/Users/momoa/OneDrive/Desktop/pro/test_bfs.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        ui->disbfs->setText(in.readAll());
        file.close();
    }


    QFile file2("C:/Users/momoa/OneDrive/Desktop/pro/test_dfs.txt");
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file2);
        ui->disdfs->setText(in.readAll());
        file2.close();
    }

}




