#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>
#include <algorithm>
using namespace std;

const int INF = INT_MAX;

// Buildings
vector<string> BUILDINGS = {
    "Main Gate","Ganga Building","Saraswati Building","Shriraj Canteen",
    "Agastya KRC","Dnyaneshwara Block","Vivekanand Auditorium",
    "Encave Cafeteria-1","Vashistha Block","East Gate",
    "Sports Complex","Aaryabhata Block","Encave Cafeteria-2",
    "Chanakya Block","Admission Center","Mullik Gate"
};

int V = (int)BUILDINGS.size();

// ─────────────────────────────────────────────
// PRINT BUILDINGS (OPTION 1)
// ─────────────────────────────────────────────
void printBuildings() {
    cout << "\nLIST OF BUILDINGS (Index Mapping):\n";
    for (int i = 0; i < V; i++) {
        cout << "[" << i << "] " << BUILDINGS[i] << endl;
    }
}

// ─────────────────────────────────────────────
// GRAPH CLASS
// ─────────────────────────────────────────────
class CampusGraph {
    vector<vector<pair<int,int>>> adj;

public:
    CampusGraph(int n) {
        adj.resize(n);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    // =========================
    // ADJACENCY LIST
    // =========================
    void printAdjList() {
        cout << "\nADJACENCY LIST:\n";
        for (int i = 0; i < V; i++) {
            cout << "[" << i << "] " << BUILDINGS[i] << " -> ";
            for (int j = 0; j < (int)adj[i].size(); j++) {
                cout << BUILDINGS[adj[i][j].first]
                     << "(" << adj[i][j].second << "m) ";
            }
            cout << "\n";
        }
    }

    // =========================
    // ADJACENCY MATRIX
    // =========================
    void printAdjMatrix() {
        vector<vector<int>> mat(V, vector<int>(V, INF));

        for (int i = 0; i < V; i++) mat[i][i] = 0;

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < (int)adj[i].size(); j++) {
                int v = adj[i][j].first;
                int w = adj[i][j].second;
                mat[i][v] = w;
            }
        }

        cout << "\nADJACENCY MATRIX:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (mat[i][j] == INF)
                    cout << "INF\t";
                else
                    cout << mat[i][j] << "\t";
            }
            cout << "\n";
        }
    }

    // =========================
    // DIJKSTRA WITH PATH
    // =========================
    void printDijkstra(int src, int dest) {
        vector<int> dist(V, INF), parent(V, -1);

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[src] = 0;
        pq.push(make_pair(0, src));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (int i = 0; i < (int)adj[u].size(); i++) {
                int v = adj[u][i].first;
                int w = adj[u][i].second;

                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        cout << "\nSOURCE      : " << BUILDINGS[src] << endl;
        cout << "DESTINATION : " << BUILDINGS[dest] << endl;

        if (dist[dest] == INF) {
            cout << "No path exists.\n";
            return;
        }

        cout << "DISTANCE    : " << dist[dest] << " m\n";
        cout << "PATH        : ";

        vector<int> path;
        int current = dest;

        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }

        reverse(path.begin(), path.end());

        for (int i = 0; i < (int)path.size(); i++) {
            cout << BUILDINGS[path[i]];
            if (i != (int)path.size() - 1)
                cout << " -> ";
        }

        cout << endl;
    }

    // =========================
    // PRIM MST
    // =========================
    void printPrimMST() {
        vector<int> key(V, INF), parent(V, -1);
        vector<bool> inMST(V, false);

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        key[0] = 0;
        pq.push(make_pair(0, 0));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;

            for (int i = 0; i < (int)adj[u].size(); i++) {
                int v = adj[u][i].first;
                int w = adj[u][i].second;

                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                    pq.push(make_pair(key[v], v));
                }
            }
        }

        cout << "\nPRIM'S MINIMUM SPANNING TREE:\n";
        int total = 0;

        for (int i = 1; i < V; i++) {
            cout << BUILDINGS[parent[i]] << " - "
                 << BUILDINGS[i] << " = "
                 << key[i] << " m\n";
            total += key[i];
        }

        cout << "Total Cost = " << total << " m\n";
    }
};

// ─────────────────────────────────────────────
// BUILD GRAPH
// ─────────────────────────────────────────────
CampusGraph buildGraph() {
    CampusGraph g(V);

    g.addEdge(0,1,90);
    g.addEdge(0,2,110);
    g.addEdge(1,2,70);
    g.addEdge(2,3,100);
    g.addEdge(3,4,130);
    g.addEdge(1,5,280);
    g.addEdge(4,5,150);
    g.addEdge(5,6,110);
    g.addEdge(5,7,140);
    g.addEdge(6,7,80);
    g.addEdge(7,8,200);
    g.addEdge(8,9,150);
    g.addEdge(9,10,110);
    g.addEdge(10,11,200);
    g.addEdge(8,11,160);
    g.addEdge(7,12,180);
    g.addEdge(11,12,80);
    g.addEdge(11,13,100);
    g.addEdge(12,13,80);
    g.addEdge(13,14,200);
    g.addEdge(9,14,250);
    g.addEdge(14,15,100);

    return g;
}

// ─────────────────────────────────────────────
// INPUT FUNCTION
// ─────────────────────────────────────────────
int pickBuilding() {
    int x;
    cout << "Enter number (0-" << V-1 << "): ";
    cin >> x;

    while (cin.fail() || x < 0 || x >= V) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid! Enter a number between 0 and " << V-1 << ": ";
        cin >> x;
    }

    return x;
}

// ─────────────────────────────────────────────
// SHORTEST PATH BY NAME INPUT
// ─────────────────────────────────────────────
void shortestPathByName(CampusGraph& g) {
    string srcName, destName;
    cin.ignore();

    cout << "\nEnter SOURCE building name: ";
    getline(cin, srcName);

    cout << "Enter DESTINATION building name: ";
    getline(cin, destName);

    // Case-insensitive search
    int srcIdx = -1, destIdx = -1;

    for (int i = 0; i < V; i++) {
        string b = BUILDINGS[i];
        string s = srcName;
        string d = destName;

        transform(b.begin(), b.end(), b.begin(), ::tolower);
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        transform(d.begin(), d.end(), d.begin(), ::tolower);

        if (b == s) srcIdx = i;

        b = BUILDINGS[i];
        transform(b.begin(), b.end(), b.begin(), ::tolower);
        if (b == d) destIdx = i;
    }

    if (srcIdx == -1) {
        cout << "Source building \"" << srcName << "\" not found.\n";
        return;
    }
    if (destIdx == -1) {
        cout << "Destination building \"" << destName << "\" not found.\n";
        return;
    }

    g.printDijkstra(srcIdx, destIdx);
}

// ─────────────────────────────────────────────
// MENU
// ─────────────────────────────────────────────
void menu(CampusGraph& g) {
    int ch;
    do {
        cout << "\n=============================\n";
        cout << "       CAMPUS NAVIGATOR\n";
        cout << "=============================\n";
        cout << "1. Adjacency List\n";
        cout << "2. Adjacency Matrix\n";
        cout << "3. Shortest Path (by index)\n";
        cout << "4. Shortest Path (by name)\n";
        cout << "5. Prim MST\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> ch;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            ch = -1;
        }

        switch(ch) {
            case 1:
                g.printAdjList();
                break;
            case 2:
                g.printAdjMatrix();
                break;
            case 3: {
                printBuildings();
                cout << "\nSelect SOURCE:\n";
                int s = pickBuilding();
                cout << "\nSelect DESTINATION:\n";
                int d = pickBuilding();
                g.printDijkstra(s, d);
                break;
            }
            case 4:
                printBuildings();
                shortestPathByName(g);
                break;
            case 5:
                g.printPrimMST();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (ch != 0);
}

// ─────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────
int main() {
    CampusGraph g = buildGraph();

    cout << "=============================\n";
    cout << "   CAMPUS NAVIGATION SYSTEM\n";
    cout << "=============================\n";

    printBuildings();
    menu(g);

    return 0;
}