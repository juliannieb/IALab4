#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node {
	string key;
	vector<node*> parents;
	map<string, int> idxOfParents;
	map<int, double> probabilitiesTable;
};

typedef struct node Node;

Node* initializeNode(string key) {
	Node *new_node = new Node;
	new_node -> key = key;
	new_node -> parents = vector<Node*>(0);
	new_node -> idxOfParents = map<string, int>();
	new_node -> probabilitiesTable = map<int, double>();
	return new_node;
}

pair< vector<Node*>, map<string, Node*> > readNodes() {
	string node_key;
	vector<Node*> nodes = vector<Node*>(0);
	map<string, Node*> nodes_map;
	while (cin >> node_key) {
		if (node_key[node_key.size()-1] == ',') {
			node_key = node_key.substr(0, node_key.size()-1);
			Node *new_node = initializeNode(node_key);
			nodes.push_back(new_node);
			nodes_map[node_key] = new_node;
		}
		else {
			Node *new_node = initializeNode(node_key);
			nodes.push_back(new_node);
			nodes_map[node_key] = new_node;
			break;
		}
	}
	pair< vector<Node*>, map<string, Node*> > readed_nodes = pair< vector<Node*>, map<string, Node*> >(nodes, nodes_map);
	return readed_nodes;
}

void printNodes(vector<Node*> nodes) {
	cout << "Nodes: ";
	for (int i = 0; i < nodes.size(); i++) {
		cout << nodes[i] -> key << (i == nodes.size() - 1 ? "\n" : ", ");
	}
}

int main () {
	string input_type;
	cin >> input_type;
	pair< vector<Node*>, map<string, Node*> > readed_nodes;
	vector<Node*> nodes;
	map<string, Node*> nodes_map;
	if (input_type == "[Nodes]") {
		readed_nodes = readNodes();
		nodes = readed_nodes.first;
		nodes_map = readed_nodes.second;
		printNodes(nodes);
	}
	cin >> input_type;
	if (input_type == "[Probabilities]") {

	}
	cin >> input_type;
	if (input_type == "[Queries]") {

	}
	return 0;
}