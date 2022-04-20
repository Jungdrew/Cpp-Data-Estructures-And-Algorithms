#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class MatAdj{
    private:
        vector< vector<size_t> > graph;
        size_t nEdges;

    public:
        MatAdj(size_t nodes){
            graph.reserve(nodes);
            for(size_t i = 0; i < nodes; i++){
                vector<size_t> a(nodes, 0);
                graph.push_back(a); 
            }
            nEdges = 0;
        }

        size_t numNodes(){ return graph.size(); }
        size_t numEdges(){ return nEdges; }

        vector<size_t>& adjacent(size_t s){
            return graph[s];
        }

        void print(){
            for(size_t i = 0; i < numNodes(); i++){
                for(size_t j = 0; j < numNodes(); j++){
                    cout << " " << graph[i][j];
                }
                cout << endl;
            }
        }

        void addEdge(size_t s, size_t t){
            graph[s][t] = 1;
        }

        void DFS(size_t source, vector<size_t> &parent, vector<bool> &visited);
};

/**
 * ANCHOR -> DFS Code
 * > The function takes a source node, a vector of parents, and a vector of visited nodes. It marks the
 * source node as visited, and then for each adjacent node, it marks it as visited and sets its parent
 * to the source node. 
 * 
 * The function is recursive, so it will call itself on each adjacent node.
 * 
 * @param source The node we're currently at
 * @param parent A vector of size numNodes() that will contain the parent of each node.
 * @param visited A vector of booleans that indicates whether a node has been visited or not.
 * 
 * @return void.
 */
void MatAdj::DFS(size_t source, vector<size_t>& parent, vector<bool>& visited){

    if(visited[source])
        return;

    visited[source] = true;
    for(size_t i = 0; i < numNodes(); i++){
        if(adjacent(source)[i] && !visited[i]){
            parent[i] = source;
            DFS(i, parent, visited);
        }
    }

}

//* ANCHOR -> Print Vectors */
template <typename T>
void printVector(vector<T> Print){
    cout << "[ ";
    for(typename vector<T>::iterator i = Print.begin(); i < Print.end(); i++)
        cout << *i << " ";
    cout << "]";
}

int main(){
/* ANCHOR -> DFS EXAMPLE
    MatAdj n(8);
    n.addEdge(0, 2);
    n.addEdge(1, 3);
    n.addEdge(1, 6);
    n.addEdge(2, 0);
    n.addEdge(2, 1);
    n.addEdge(2, 5);
    n.addEdge(3, 5);
    n.addEdge(4, 2);
    n.addEdge(4, 7);
    n.addEdge(4, 6);
    n.addEdge(5, 1);
    n.addEdge(5, 3);
    n.addEdge(5, 7);
    n.addEdge(6, 5);
    n.addEdge(7, 6);
    n.print();

    size_t AdjSize = n.numNodes();

    vector<size_t> parent( AdjSize,  0 );
    vector<bool> visited( AdjSize, false );

    cout << endl << "DFS : ";
    n.DFS(7, parent, visited);
    printVector(parent);
    printVector(visited); 
*/

    return 0;
}