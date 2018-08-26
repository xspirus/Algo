#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>
#include <algorithm>
#include <unordered_set>

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

/**************************************************************/

struct Node {

    int id, cost;

    Node();
    Node(int id, int cost);

};

Node::Node() {
    id = 0;
    cost = 0;
}

Node::Node(int id, int cost) {
    this->id = id;
    this->cost = cost;
}

/**************************************************************/

struct CompareStruct {

    bool operator () (const Node *lhs, const Node *rhs) const {
        return (lhs->cost > rhs->cost);
    }

};

/**************************************************************/

typedef priority_queue<Node*, vector<Node*>, CompareStruct> prioq;

class Solver {

private:

    int size;
    prioq openSet;
    vector<bool> visited;
    vector<int> gScore;
    vector < unordered_set <int> > cameFrom;
    vector<long long int> paths;

public:

    Solver(int size);

    void restore();
    long long int solve(int start, int end, Graph graph);
    long long int finalSolve(int start, int end, Graph graph);
    long long int getPaths(int i);
    unordered_set<int> getAncestors(int i);

};

Solver::Solver(int size) {

    this->size = size;
    for (int i = 0; i <= this->size; i++) {
        visited.push_back(false);
        gScore.push_back(INT_MAX);
        unordered_set<int> l;
        cameFrom.push_back(l);
        paths.push_back(0);
    }

}

void Solver::restore() {

    while (!openSet.empty())
        openSet.pop();

    for (int i = 0; i <= this->size; i++) {
        visited[i] = false;
        gScore[i] = INT_MAX;
        cameFrom[i].clear();
        paths[i] = 0;
    }

}

long long int Solver::getPaths(int i) {
    return paths[i];
}

unordered_set<int> Solver::getAncestors(int i) {
    return cameFrom[i];
}

long long int Solver::solve(int start, int end, Graph graph) {

    Node *current;
    int best = INT_MAX, id, score;
    long long int result;
    list<Destination> neighbors;

    gScore[start] = 0;
    paths[start] = 1;
    openSet.push(new Node(start, gScore[start]));

    while (!openSet.empty()) {

        current = openSet.top();
        openSet.pop();

        id = current->id;
        score = current->cost;

        if (visited[id])
            continue;

        visited[id] = true;
        //cout << "Current is " << id << " with score " << score << endl;

        if (current->id == end) {
            //cout << "Found the end" << endl;
            best = current->cost;
            result = paths[end];
            break;
        }

        neighbors = graph.getEdges(id);

        for (destIt it = neighbors.begin(); it != neighbors.end(); ++it) {

            //cout << "Neighbor is " << it->getId() << " with score " << score + it->getDistance();

            if ((score + it->getDistance()) > best) {
                //cout << "...Not gonna enter openSet" << endl;
                continue;
            }

            if ((score + it->getDistance()) < gScore[it->getId()]) {
                paths[it->getId()] = paths[id];
                //cout << "...Entering openSet";
                //cout << "...as id " << it->getId();
                //cout << "...with " << paths[it->getId()] << " paths";
                openSet.push(new Node(it->getId(), (score + it->getDistance())));
                gScore[it->getId()] = score + it->getDistance();
                /*cameFrom[it->getId()].clear();
                cameFrom[it->getId()].insert(id);
                for (unordered_set<int>::iterator kappa = cameFrom[id].begin(); kappa != cameFrom[id]. end(); ++kappa) {
                    cameFrom[it->getId()].insert(*kappa);
                }*/
            } else if ((score + it->getDistance()) == gScore[it->getId()]) {
                paths[it->getId()] += paths[id];
                /*if (cameFrom[it->getId()].count(id) == 0)
                    cameFrom[it->getId()].insert(id);
                for (unordered_set<int>::iterator kappa = cameFrom[id].begin(); kappa != cameFrom[id]. end(); ++kappa) {
                    if (cameFrom[it->getId()].count(*kappa) == 0)
                        cameFrom[it->getId()].insert(*kappa);
                }*/
                //cout << "...Increasing paths to " << paths[it->getId()];
            }

            //cout << endl;

        }

        //cout << endl;

    }

    //cout << start << "\t-->\t" << end << "\t: " << result << "\troutes with distance " << best << endl;

    return result;

}

long long int Solver::finalSolve(int start, int end, Graph graph) {

    Node *current;
    int best = INT_MAX, id, score;
    long long int result;
    list<Destination> neighbors;

    gScore[start] = 0;
    paths[start] = 1;
    openSet.push(new Node(start, gScore[start]));

    while (!openSet.empty()) {

        current = openSet.top();
        openSet.pop();

        id = current->id;
        score = current->cost;

        if (visited[id])
            continue;

        visited[id] = true;
        //cout << "Current is " << id << " with score " << score << endl;

        if (current->id == end) {
            //cout << "Found the end" << endl;
            best = current->cost;
            result = paths[end];
            break;
        }

        neighbors = graph.getEdges(id);

        for (destIt it = neighbors.begin(); it != neighbors.end(); ++it) {

            //cout << "Neighbor is " << it->getId() << " with score " << score + it->getDistance();

            if ((score + it->getDistance()) > best) {
                //cout << "...Not gonna enter openSet" << endl;
                continue;
            }

            if ((score + it->getDistance()) < gScore[it->getId()]) {
                paths[it->getId()] = paths[id];
                //cout << "...Entering openSet";
                //cout << "...as id " << it->getId();
                //cout << "...with " << paths[it->getId()] << " paths";
                openSet.push(new Node(it->getId(), (score + it->getDistance())));
                gScore[it->getId()] = score + it->getDistance();
                cameFrom[it->getId()].clear();
                cameFrom[it->getId()].insert(id);
                for (unordered_set<int>::iterator kappa = cameFrom[id].begin(); kappa != cameFrom[id]. end(); ++kappa) {
                    cameFrom[it->getId()].insert(*kappa);
                }
            } else if ((score + it->getDistance()) == gScore[it->getId()]) {
                paths[it->getId()] += paths[id];
                if (cameFrom[it->getId()].count(id) == 0)
                    cameFrom[it->getId()].insert(id);
                for (unordered_set<int>::iterator kappa = cameFrom[id].begin(); kappa != cameFrom[id]. end(); ++kappa) {
                    if (cameFrom[it->getId()].count(*kappa) == 0)
                        cameFrom[it->getId()].insert(*kappa);
                }
                //cout << "...Increasing paths to " << paths[it->getId()];
            }

            //cout << endl;

        }

        //cout << endl;

    }

    cout << start << "\t-->\t" << end << "\t: " << result << "\troutes with distance " << best << endl;

    return result;

}

/**************************************************************/

int main() {

    int N, M, Q, K;
    int i, j, d, counter;
    long long int maximum = 0;

    N = read_int();
    M = read_int();
    Q = read_int();
    K = read_int();

    Graph graph(N);
    Solver solver(N);
    vector<long long int> passing(N + 1);

    for (counter = 0; counter < M; counter++) {
        i = read_int();
        j = read_int();
        d = read_int();
        graph.addEdge(i, j, d);
    }

    //graph.print();

    for (counter = 0; counter < Q; counter++) {
        i = read_int();
        j = read_int();
        cout << solver.solve(i, j, graph) << endl;
        solver.restore();
    }

    if (K == 2) {
        cout << solver.solve(1, N, graph) << endl;
        solver.restore();
    } else {
        /**
         * Initial solution
         */
        /*//cout << solver.solve(1, N, graph) << endl;
        solver.finalSolve(1, N, graph);
        unordered_set<int> kappa = solver.getAncestors(N);
        //cout << "From 1 to N..." << endl;
        for (unordered_set<int>::iterator index = kappa.begin(); index != kappa.end(); ++index) {
            passing[*index] = solver.getPaths(*index);
            //cout << "passing[" << *index << "] = " << solver.getPaths(*index) << endl;
        }
        solver.restore();
        //cout << solver.solve(N, 1, graph) << endl;
        solver.finalSolve(N, 1, graph);
        //cout << "From N to 1..." << endl;
        kappa = solver.getAncestors(1);
        for (unordered_set<int>::iterator index = kappa.begin(); index != kappa.end(); ++index) {
            passing[*index] *= solver.getPaths(*index);
            //cout << "passing[" << *index << "] = " << solver.getPaths(*index) << endl;
        }
        solver.restore();

        //cout << endl;
        for (counter = 1; counter <= N; counter++) {
            //cout << passing[counter] << endl;
        }
        sort(passing.begin(), passing.end());
        cout << passing[N - K + 3] << endl;
        //cout << endl;
        for (counter = 1; counter <= N; counter++) {
            //cout << passing[counter] << endl;
        }*/

        /**
         * Test
         */
        K = K - 2;
        int start = 1, end = N;
        unordered_set<int> path;
        unordered_set<int>::iterator it;
        for (counter = 0; counter < K; counter++) {

            for (i = 0; i <= N; i++) {
                passing[i] = 0;
            }
            maximum = 0;

            solver.finalSolve(start, end, graph);
            path = solver.getAncestors(end);
            for (it = path.begin(); it != path.end(); ++it) {
                cout << "Been through " << *it << endl;
                //cout << "Paths " << solver.getPaths(*it) << endl;
                passing[*it] = solver.getPaths(*it);
            }
            solver.restore();

            solver.finalSolve(end, start, graph);
            path = solver.getAncestors(start);
            for (it = path.begin(); it != path.end(); ++it) {
                //cout << "Been through " << *it << endl;
                //cout << "Paths " << solver.getPaths(*it) << endl;
                passing[*it] *= solver.getPaths(*it);
                //cout << "With " << passing[*it] << endl;
                if (passing[*it] > maximum) {
                    maximum = passing[*it];
                    end = *it;
                }
            }
            solver.restore();
            //cout << "Start is now " << start << endl;
            break;

        }
        //cout << maximum << endl;
    }

    return 0;

}
