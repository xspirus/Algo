/**
 * Credits: https://www.hackerrank.com/topics/lowest-common-ancestor
 *          https://www.youtube.com/watch?v=ctZ7fjMbPWE
 */

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>
#include <algorithm>
#include <cmath>

#define BSIZE 1<<15

char buffer[BSIZE];
int bpos = 0, bsize = 0;

using namespace std;

int read_int() {

    int d = 0, x = 0;
    char c;

    while (1)  {

        if (bpos >= bsize) {

            bpos = 0;
            if (feof(stdin)) return x;
            bsize = fread(buffer, 1, BSIZE, stdin);

        }

        c = buffer[bpos++];
        if (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            d = 1;
        } else if (d == 1)
            return x;

    }

    return -1;

}

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

/**************************************************************/

/**
 * Class to be used for storing
 * the neighbors of a vertex
 */
class Destination {

private:

    int id;
    int distance;

public:

    Destination(int id, int distance);

    int getId();
    int getDistance();

};

Destination::Destination(int id, int distance) {
    this->id = id;
    this->distance = distance;
}

int Destination::getId() {
    return this->id;
}

int Destination::getDistance() {
    return this->distance;
}

typedef list<Destination>::iterator destIt;

/**************************************************************/

class MST {

private:

    int size;
    int root;
    vector< list < Destination > > edge;
    vector<int> level;
    vector<int> parent;
    vector<int> weight;
    int **ancestor;

public:

    MST(int size);

    void addEdge(int i, int j, int d);
    void putParent(int v, int p);
    void putLevel(int v, int l);
    void putWeight(int v, int w);
    void preProccess();
    void print();

    int getSize();
    int lca(int u, int v);
    int bottleneck(int u, int v, int lca);
    list<Destination> getEdges(int i);

};

MST::MST(int size) {
    this->size = size;
    this->root = 1;
    this->ancestor = new int*[this->size + 1];
    for (int i = 0; i <= this->size; i++) {
        this->ancestor[i] = new int[(int)ceil(log2(this->size))];
        for (int j = 0; (1 << j) < this->size; j++) {
            this->ancestor[i][j] = -1;
        }
    }
    for (int i = 0; i <= this->size; i++) {
        list<Destination> l;
        edge.push_back(l);
        level.push_back(0);
        parent.push_back(-1);
        weight.push_back(-1);
    }
}

void MST::preProccess() {

    for (int i = 1; i <= this->size; i++) {
        this->ancestor[i][0] = this->parent[i];
    }

    for (int j = 1; (1 << j) < this->size; j++) {
        for (int i = 1; i <= this->size; i++) {
            if (this->ancestor[i][j - 1] != -1) {
                this->ancestor[i][j] = this->ancestor[this->ancestor[i][j - 1]][j - 1];
            }
        }
    }

}

void MST::addEdge(int i, int j, int d) {

    Destination to(j, d);
    //Destination from(i, d);

    edge[i].push_back(to);
    //edge[j].push_back(from);

}

void MST::putParent(int v, int p) {
    parent[v] = p;
}

void MST::putLevel(int v, int l) {
    level[v] = l;
}

void MST::putWeight(int v, int w) {
    weight[v] = w;
}

void MST::print() {

    for (int i = 1; i <= this->size; i++) {
        cout << "Vertex " << i << " edges..." << endl;
        for (destIt it = edge[i].begin(); it != edge[i].end(); ++it) {
            cout << i << " -> " << it->getId() << " with distance " << it->getDistance() << endl;
        }
        cout << endl;
    }

    cout << "***Parents***" << endl;
    for (int i = 1; i <= this->size; i++) {
        cout << "parent[" << i << "] = " << this->parent[i] << endl;
    }
    cout << endl;

    cout << "***Levels***" << endl;
    for (int i = 1; i <= this->size; i++) {
        cout << "level[" << i << "] = " << this->level[i] << endl;
    }
    cout << endl;

}

int MST::getSize() {
    return this->size;
}

int MST::lca(int u, int v) {

    if (this->level[u] < this->level[v]) {
        swap(u, v);
    }

    int dist = level[u] - level[v];
    while (dist > 0) {
        int raise_by = log2(dist);
        u = this->ancestor[u][raise_by];
        dist -= (1<<raise_by);
    }

    if (u == v) {
        return u;
    }

    for (int j = (int)log2(this->size); j >= 0; j--) {
        if (this->ancestor[u][j] != -1 && this->ancestor[u][j] != this->ancestor[v][j]) {
            u = this->ancestor[u][j];
            v = this->ancestor[v][j];
        }
    }

    return this->parent[u];

}

int MST::bottleneck(int u, int v, int lca) {

    int max = 0;

    while (u != lca) {
        if (weight[u] > max)
            max = weight[u];
        u = parent[u];
    }

    while (v != lca) {
        if (weight[v] > max)
            max = weight[v];
        v = parent[v];
    }

    return max;

}

list<Destination> MST::getEdges(int i) {
    return edge[i];
}



/**************************************************************/

struct Node {

    int id, weight;

    Node();
    Node(int id, int weight);

};

Node::Node() {
    id = 0;
    weight = 0;
}

Node::Node(int id, int weight) {
    this->id = id;
    this->weight = weight;
}

/**************************************************************/

struct CompareStruct {

    bool operator () (const Node *lhs, const Node *rhs) const {
        return (lhs->weight > rhs->weight);
    }

};

/**************************************************************/

typedef priority_queue<Node*, vector<Node*>, CompareStruct> prioq;

/**
 * The graph class. It is used
 * to store the vertices and
 * the neighbors of each one.
 */
class Graph {

private:

    int size;
    vector <list <Destination> > edge;

public:

    Graph(int size);
    virtual ~Graph ();

    void addEdge(int i, int j, int d);
    void print();

    int getSize();
    list<Destination> getEdges(int i);

    MST prim();

};

Graph::Graph(int size) {

    this->size = size;
    for (int i = 0; i <= this->size; i++) {
        list<Destination> l;
        edge.push_back(l);
    }

}

Graph::~Graph() {

}

void Graph::addEdge(int i, int j, int d) {

    Destination to(j, d);
    Destination from(i, d);

    edge[i].push_back(to);
    edge[j].push_back(from);

}

void Graph::print() {

    for (int i = 1; i <= this->size; i++) {
        cout << "Vertex " << i << " edges..." << endl;
        for (destIt it = edge[i].begin(); it != edge[i].end(); ++it) {
            cout << i << " -> " << it->getId() << " with distance " << it->getDistance() << endl;
        }
        cout << endl;
    }

}

int Graph::getSize() {
    return this->size;
}

list<Destination> Graph::getEdges(int i) {
    return edge[i];
}

MST Graph::prim() {

    int parent[this->size + 1];
    int weight[this->size + 1];
    int level[this->size + 1];
    bool visited[this->size + 1];
    Node *current;
    prioq openSet;

    fill_n(parent, this->size + 1, -1);
    fill_n(weight, this->size + 1, INT_MAX);
    fill_n(level, this->size + 1, 0);
    fill_n(visited, this->size + 1, false);

    MST mst(this->size);

    int start = 1;
    weight[start] = 0;
    level[start] = 1;
    openSet.push(new Node(start, 0));

    while (!openSet.empty()) {

        current = openSet.top();
        openSet.pop();

        //cout << "Current is " << current->id << endl;

        if (visited[current->id])
            continue;

        visited[current->id] = true;

        for (destIt it = edge[current->id].begin(); it != edge[current->id].end(); ++it) {

            if (visited[it->getId()])
                continue;

            //cout << "Neighbor is " << it->getId() << endl;

            if (it->getDistance() < weight[it->getId()]) {
                openSet.push(new Node(it->getId(), it->getDistance()));
                weight[it->getId()] = it->getDistance();
                parent[it->getId()] = current->id;
                level[it->getId()] = level[current->id] + 1;
            }

        }

    }

    mst.putParent(start, start);
    mst.putLevel(start, level[start]);
    mst.putWeight(start, weight[start]);
    for (int i = 2; i <= this->size; i++) {
        mst.addEdge(parent[i], i, weight[i]);
        mst.putParent(i, parent[i]);
        mst.putLevel(i, level[i]);
        mst.putWeight(i, weight[i]);
    }

    return mst;

}

/**************************************************************/

int main() {

    int N, M, Q;
    int i, x, y, d;
    int lca;

    N = read_int();
    M = read_int();

    Graph graph(N);

    for (i = 1; i <= M; i++) {

        x = read_int();
        y = read_int();
        d = read_int();
        graph.addEdge(x, y, d);

    }

    MST mst = graph.prim();

    //mst.print();

    mst.preProccess();

    Q = read_int();

    for (i = 1; i <= Q; i++) {

        x = read_int();
        y = read_int();
        lca = mst.lca(x, y);
        cout << mst.bottleneck(x, y, lca) << endl;

    }

    return 0;

}
