#include <iostream>
#include <map>
using namespace std;

class rt {
	public:
	int dist[10], next[10];
};

class DVR {
	int n;
	int graph[10][10];
	rt *routingTable;

	string nodes[10];
	public:
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	DVR(int size) {
		n = size;
		routingTable = new rt[10];

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				graph[i][j] = -1;
			}
		}
		cout << "Nodes: ";
		for (int i = 0; i < n; i++) {
			nodes[i] = char(65 + i);
			cout << nodes[i] << " ";
		}
	}
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	void setGraphData() {
		int value;
		cout << "(For no direct link, enter '999')\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					graph[i][j] = 0;
				}
				else {
					cout << "Enter distance[" << nodes[i] << "][" << nodes[j] << "]: ";
					cin >> graph[i][j];
				}
				routingTable[i].dist[j] = graph[i][j];
				routingTable[i].next[j] = j;
			}
			cout << endl;
		}
	}
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	void displayRoutingTable() {
		for (int i = 0; i < n; i++) {
			cout << nodes[i] << ":\n--------------------\nDest\tDist\tNext\n--------------------\n";
			for (int j = 0; j < n; j++) {
				cout << nodes[j] << "\t";
                if (routingTable[i].dist[j] == 999) {
                    cout << char(236) << "\t-" << "\n";
                }
                else
                cout << routingTable[i].dist[j] << "\t" << nodes[routingTable[i].next[j]] << "\n";
			}
			cout << "--------------------\n\n";
		}
	}
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	map <int, int> findNeighbours(int i) {
		map<int, int> nodesMap;
		for (int j = 0; j < n; j++) {
			if (graph[i][j] != 0 && graph[i][j] != 999) {
				nodesMap[j] = graph[i][j];
			}
		}
		return nodesMap;
	}
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	void bellmanFord() {
		int count;
		for (int iteration = 0; iteration < n-1; iteration++) {
			for (int i = 0; i < n; i++) {

				map <int, int> neighbours = findNeighbours(i);
				int newDistances[n-1];
				for (int j = 0; j < n; j++) {
					count = 0;
					map <int, int>::iterator iter = neighbours.begin();
					if (i == j) continue;
					while (count < neighbours.size() || iter != neighbours.end()) {
						newDistances[count++] = iter->second + routingTable[iter->first].dist[j];
						iter++;
					}
					int min = findMin(newDistances);
                    iter = neighbours.begin();
					for (int k = 0; k < neighbours.size(); k++) {
						if (k == min) {
							routingTable[i].dist[j] = newDistances[min];
							routingTable[i].next[j] = iter->first;
                            break;
						}
						iter++;
					}
				}
			}
		}
	}
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	int findMin(int arr[]) {
		int minElement = arr[0], min = 0;
		for (int i = 1; i < n-1; i++) {
			if (arr[i] < minElement) {
				minElement = arr[i];
				min = i;
			}
		}
		return min;
	}
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	void displayGraph() {
		cout << "\nInput Graph:\n\n";
		for (int i = 0; i < n; i++) {
			cout << "\t" << nodes[i];
		}
		cout << "\n\n";
		for (int i = 0; i < n; i++) {
			cout << nodes[i] << "\t";
			for (int j = 0; j < n; j++) {
				if (graph[i][j] == 999) {
					cout << char(236) << "\t";
				}
				else {
					cout << graph[i][j] << "\t";
				}
			}
			cout << endl;
		}
		cout << "\n";
	}	
};
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int main(int argc, char const *argv[]) {
	int n;
	cout << "=-=-=-= Distance Vector Routing Protocol =-=-=-=\n\n";
	cout << "Enter the no. of nodes: ";
	cin >> n;
	DVR G(n);
	
	cout << "\n";
	G.setGraphData();
	G.displayGraph();
	cout << "=-=-= Initial Routing Tables =-=-=\n";
	G.displayRoutingTable();
	G.bellmanFord();
    cout << "\n=-=-= Final Routing Table =-=-=\n";
    G.displayRoutingTable();
	return 0;
}
/*
Output:

=-=-=-= Distance Vector Routing Protocol =-=-=-=

Enter the no. of nodes: 4
Nodes: A B C D 
(For no direct link, enter '999')
Enter distance[A][B]: 2
Enter distance[A][C]: 999
Enter distance[A][D]: 1

Enter distance[B][A]: 2
Enter distance[B][C]: 3
Enter distance[B][D]: 7

Enter distance[C][A]: 999
Enter distance[C][B]: 3
Enter distance[C][D]: 11

Enter distance[D][A]: 1
Enter distance[D][B]: 7
Enter distance[D][C]: 11


Input Graph:

        A       B       C       D

A       0       2       ∞       1
B       2       0       3       7
C       ∞       3       0       11
D       1       7       11      0

=-=-= Initial Routing Tables =-=-=
A:
--------------------
Dest    Dist    Next
--------------------
A       0       A
B       2       B
C       ∞       -
D       1       D
--------------------

B:
--------------------
Dest    Dist    Next
--------------------
A       2       A
B       0       B
C       3       C
D       7       D
--------------------

C:
--------------------
Dest    Dist    Next
--------------------
A       ∞       -
B       3       B
C       0       C
D       11      D
--------------------

D:
--------------------
Dest    Dist    Next
--------------------
A       1       A
B       7       B
C       11      C
D       0       D
--------------------


=-=-= Final Routing Table =-=-=
A:
--------------------
Dest    Dist    Next
--------------------
A       0       A
B       2       B
C       5       B
D       1       D
--------------------

B:
--------------------
Dest    Dist    Next
--------------------
A       2       A
B       0       B
C       3       C
D       3       A
--------------------

C:
--------------------
Dest    Dist    Next
--------------------
A       5       B
B       3       B
C       0       C
D       6       B
--------------------

D:
--------------------
Dest    Dist    Next
--------------------
A       1       A
B       3       A
C       6       A
D       0       D
--------------------
*/
