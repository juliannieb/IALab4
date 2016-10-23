#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct node {
	string key;
	vector<node*> parents;
	map<string, int> idxOfParents;
	map<string, double> probabilitiesTable;
	double probability;
};

typedef struct node Node;

Node* initializeNode(string key) {
	Node *new_node = new Node;
	new_node -> key = key;
	new_node -> parents = vector<Node*>(0);
	new_node -> idxOfParents = map<string, int>();
	new_node -> probabilitiesTable = map<string, double>();
	new_node -> probability = 0.0;
	return new_node;
}

string remove_chars(string s, char c) {
	string ans = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != c)
			ans.push_back(s[i]);
	}
	return ans;
}

vector<string> split(string complete_string, char c) {
	vector<string> ans = vector<string>(0);
	string s = "";
	for (int i = 0; i < complete_string.size(); i++) {
		if (complete_string[i] == c) {
			ans.push_back(s);
			s = "";
		}
		else {
			if (c != ' ' && complete_string[i] == ' ') {
				continue;
			}
			s.push_back(complete_string[i]);
		}
	}
	ans.push_back(s);
	return ans;
}

pair< vector<Node*>, map<string, Node*> > readNodes() {
	string line;
	vector<Node*> nodes = vector<Node*>(0);
	map<string, Node*> nodes_map;
	getline(cin, line);
	line = remove_chars(line, ' ');
	vector<string> nodeKeys = split(line, ',');
	for (int i = 0; i < nodeKeys.size(); i++) {
		string node_key = nodeKeys[i];
		Node *new_node = initializeNode(node_key);
		nodes.push_back(new_node);
		nodes_map[node_key] = new_node;
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

void set_probabilities(map<string, Node*> &nodes_map, string query, string evidence, string probability) {
	float prob = atof(probability.c_str());
	cout << "prob = " << prob << endl;
}

void read_probabilities(vector<Node*> &nodes, map<string, Node*> &nodes_map) {
	string line;
	getline(cin, line);
	while(getline(cin, line)) {
		if (line.empty()) {
			//cout << "Empty" << endl;
			break;
		}
		line = remove_chars(line, ' ');
		//cout << line << endl;
		vector<string> nodes_and_prob = split(line, '=');
		string nodes = nodes_and_prob[0];
		string prob = nodes_and_prob[1];
		//cout << nodes << " ------ " << prob << endl;
		vector<string> query_and_evidence = split(nodes, '|');
		if (query_and_evidence.size() == 2) {
			string query = query_and_evidence[0];
			string evidence = query_and_evidence[1];
			cout << "Query: " << query_and_evidence[0] << " --- Evidence: " << evidence << " --- " << prob << endl;
		}
		else {
			string query = query_and_evidence[0];
			cout << "Query: " << query_and_evidence[0] << " --- " << prob << endl;
		}
	}
}

int main () {
	string input_type;
	getline(cin, input_type);
	pair< vector<Node*>, map<string, Node*> > readed_nodes;
	vector<Node*> nodes;
	map<string, Node*> nodes_map;
	if (input_type == "[Nodes]") {
		readed_nodes = readNodes();
		nodes = readed_nodes.first;
		nodes_map = readed_nodes.second;
		printNodes(nodes);
	}
	getline(cin, input_type);
	if (input_type == "[Probabilities]") {
		read_probabilities(nodes, nodes_map);
	}
	getline(cin, input_type);
	if (input_type == "[Queries]") {

	}
	return 0;
}