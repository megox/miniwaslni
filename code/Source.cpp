#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;
unordered_map<string, vector<pair<string, int>>>adjlist;
unordered_map<string, bool>vis;
unordered_set<string>listt;
unordered_map<string, bool>road_of_city;
const int N = 1e9;

void read_file() {
    ifstream infile("test.txt");
    string a, b;
    int c;
    while (infile >> a >> b >> c) {
        adjlist[a].push_back(make_pair(b, c));
        if (a != "0") listt.insert(a);
        if (b != "0") listt.insert(b);
    }
    infile.close();
}

void write_in_fie() {
    ofstream fout;
    fout.open("test.txt", ios::out);
    unordered_set<string>::iterator i;
    for (i = listt.begin(); i != listt.end(); i++) {
        for (int j = 0; j < adjlist[*i].size(); j++) {
            fout << *i << ' ' << adjlist[*i][j].first << ' ' << adjlist[*i][j].second << "\n";
        }
    }
    fout.close();
}

void display_graph() {
    unordered_set<string>::iterator i;
    for (i = listt.begin(); i != listt.end(); i++) {
        cout << *i << ":";
        for (int j = 0; j < adjlist[*i].size(); j++) {
            cout << "(" << adjlist[*i][j].first << "," << adjlist[*i][j].second << "),";
        }
        cout << endl;
    }
}

void add_graph_directed(int edges) {
    string a, b;
    int c;
    for (int i = 0; i < edges; i++) {
        cin >> a >> b >> c;
        adjlist[a].push_back(make_pair(b, c));
        listt.insert(a);
        listt.insert(b);
    }
}

void add_graph_undirected(int edges) {
    string a, b;
    int c;
    for (int i = 0; i < edges; i++) {
        cin >> a >> b >> c;
        adjlist[a].push_back(make_pair(b, c));
        adjlist[b].push_back(make_pair(a, c));
        listt.insert(a);
        listt.insert(b);
    }
}

void add_edge_to_graph_directed() {
    string a, b;
    int c;
    cin >> a >> b >> c;
    adjlist[a].push_back(make_pair(b, c));
    listt.insert(a);
    listt.insert(b);
}

void add_edge_to_graph_undirected() {
    string a, b;
    int c;
    cin >> a >> b >> c;
    adjlist[a].push_back(make_pair(b, c));
    adjlist[b].push_back(make_pair(a, c));
    listt.insert(a);
    listt.insert(b);
}

void add_city_to_graph() {
    string a;
    cin >> a;
    adjlist[a].push_back(make_pair("0", 0));
    listt.insert(a);
}

void del_edge_directed(string city1, string city2)
{
    road_of_city.clear();
    unordered_set<string>::iterator i;
    for (i = listt.begin(); i != listt.end(); i++) {
        for (int j = 0; j < adjlist[*i].size(); j++) {
            if ((*i == city1 && adjlist[*i][j].first == city2)) {
                adjlist[*i].erase(adjlist[*i].begin() + j);
            }

        }
    }
    for (i = listt.begin(); i != listt.end(); i++) {
        if (!adjlist[*i].empty())road_of_city[*i] = true;
        for (int j = 0; j < adjlist[*i].size(); j++) {
            road_of_city[adjlist[*i][j].first] = true;
        }
    }
    for (i = listt.begin(); i != listt.end(); i++) {
        if (road_of_city[*i] == false)adjlist[*i].push_back({ "0",0 });
    }
}

void del_edge_undirected(string city1, string city2)
{
    road_of_city.clear();
    unordered_set<string>::iterator i;
    for (i = listt.begin(); i != listt.end(); i++) {
        for (int j = 0; j < adjlist[*i].size(); j++) {
            if ((*i == city1 && adjlist[*i][j].first == city2) || (*i == city2 && adjlist[*i][j].first == city1)) {
                adjlist[*i].erase(adjlist[*i].begin() + j);
            }

        }
    }
    for (i = listt.begin(); i != listt.end(); i++) {
        if (!adjlist[*i].empty())road_of_city[*i] = true;
        for (int j = 0; j < adjlist[*i].size(); j++) {
            road_of_city[adjlist[*i][j].first] = true;
        }
    }
    for (i = listt.begin(); i != listt.end(); i++) {
        if (road_of_city[*i] == false)adjlist[*i].push_back({ "0",0 });
    }
}

void del_city(string city)
{
    road_of_city.clear();
    unordered_set<string>::iterator i;
    for (i = listt.begin(); i != listt.end(); i++) {
        if (*i == city) adjlist[*i].clear();
        else {
            for (int j = 0; j < adjlist[*i].size(); j++) {
                if (adjlist[*i][j].first == city) {
                    adjlist[*i].erase(adjlist[*i].begin() + j);
                }

            }
        }
    }
    listt.erase(city);
    for (i = listt.begin(); i != listt.end(); i++) {
        if (!adjlist[*i].empty())road_of_city[*i] = true;
        for (int j = 0; j < adjlist[*i].size(); j++) {
            road_of_city[adjlist[*i][j].first] = true;
        }
    }
    for (i = listt.begin(); i != listt.end(); i++) {
        if (road_of_city[*i] == false)adjlist[*i].push_back({ "0",0 });
    }
}

void dfs(string node) {
    vis[node] = true;
    cout << node << ' ';

    for (int j = 0; j < adjlist[node].size(); j++) {
        if (!vis[adjlist[node][j].first])
            dfs(adjlist[node][j].first);
    }
    cout << endl;
}

void travers_dfs(string node) {
    unordered_set<string>::iterator i;
    for (i = listt.begin(); i != listt.end(); i++) {
        if (!vis[*i])dfs(*i);
    }
    vis.clear();
}

bool check_bfs(string city1, string city2) {
    vis.clear();
    queue<string> q;
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

void travers_bfs() {
    vis.clear();
    queue<string> q;
    unordered_set<string>::iterator i;
    for (i = listt.begin(); i != listt.end(); i++) {
        if (!vis[*i]) {
            q.push(*i);
            cout << *i << endl;
            vis[*i] = true;
            while (!q.empty()) {
                string node = q.front();
                q.pop();
                for (auto e : adjlist[node]) {
                    string child = e.first;
                    if (!vis[child]) {
                        q.push(child);
                        if (child != "0")cout << child << endl;
                        vis[child] = true;
                    }
                }
            }
        }
    }
}

void dijkstra(string city1, string city2) {
    if (check_bfs(city1, city2) == 0)cout << "there is no road" << "\n";
    else {
        unordered_map<string, int>dist;
        unordered_set<string>::iterator i;
        for (i = listt.begin(); i != listt.end(); i++)dist[*i] = N;
        unordered_map<string, string> pre;
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
        stack<string>display_paths;
        display_paths.push(city2);
        cout << city2 << ": " << dist[city2] << ' ' << pre[city2] << endl;
        while (true) {
            if (pre[city2] != city1)
                display_paths.push(pre[city2]);
            else break;
            city2 = pre[city2];
        }
        display_paths.push(city1);
        while (!display_paths.empty()) {
            cout << display_paths.top() << ' ';
            display_paths.pop();
        }
    }
}

void find_the_shortest_path() {
    string city1, city2;
    cin >> city1 >> city2;
    dijkstra(city1, city2);
}

void check_if_there_is_a_path_between_two_cities() {
    string city1, city2;
    cin >> city1 >> city2;
    if (check_bfs(city1, city2))cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main() {
    read_file();
    //display_graph();
    //travers_bfs();
    //find_the_shortest_path();
    //add_graph(3, 2);
    //add_city_to_graph();
    //del_city("aa");
    //del_edge("bb","cc");
    //add_edge_to_graph();
    write_in_fie();

}