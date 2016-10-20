#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node {
	string key;
	vector<node*> parents;
	map<node*, int> idxOfParents;
	map<int, double> probabilitiesTable;
};

typedef struct node Node;

vector<Node*> readNodes() {
	string node_key;
	while (cin >> node_key) {
		if (node_key[node_key.size()-1] == ',') {
			node_key = node_key.substr(0, node_key.size()-1);
		}
		cout << node_key << endl;
	}
}

int main () {
	string input_type;
	cin >> input_type;
	if (input_type == "[Nodes]") {
		readNodes();
	}
	cin >> input_type;
	if (input_type == "[Probabilities]") {

	}
	cin >> input_type;
	if (input_type == "[Queries]") {

	}
	return 0;
}