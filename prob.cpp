#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <stack>

using namespace std;

struct node {
	string key;
	vector<node*> parents;
	map<string, int> idxOfParents;
	map<string, float> probabilitiesTable;
	float probability;
};

typedef struct node Node;

Node* initializeNode(string key) {
	Node *new_node = new Node;
	new_node -> key = key;
	new_node -> parents = vector<Node*>(0);
	new_node -> idxOfParents = map<string, int>();
	new_node -> probabilitiesTable = map<string, float>();
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

void readNodes(vector<Node*> &nodes, map<string, Node*> &nodes_map) {
	string line;
	getline(cin, line);
	line = remove_chars(line, ' ');
	vector<string> nodeKeys = split(line, ',');
	for (int i = 0; i < nodeKeys.size(); i++) {
		string node_key = nodeKeys[i];
		Node *new_node = initializeNode(node_key);
		nodes.push_back(new_node);
		nodes_map[node_key] = new_node;
	}
}

void printParents(vector<Node*> parents) {
	cout << "Parents: " << endl;
	for (int i = 0; i < parents.size(); i++) {
		cout << "\t" << parents[i] -> key << (i < parents.size() - 1 ? ", " : "\n");
	}
}

void printProbabilities(map<string, float> probabilitiesTable) {
	typedef map<string, float>::iterator it_type;
	cout << "Probabilities:" << endl;
	for(it_type iterator = probabilitiesTable.begin(); iterator != probabilitiesTable.end(); iterator++) {
	    cout << "\t" << iterator -> first << " - " << iterator -> second << endl;
	}
}

void printNode(Node *node) {
	cout << "Node: " << node -> key << endl;
	cout << "Probability: " << node -> probability << endl;
	printParents(node -> parents);
	printProbabilities(node -> probabilitiesTable);
	cout << endl;
}

void printNodes(vector<Node*> nodes) {
	cout << "Nodes: ";
	for (int i = 0; i < nodes.size(); i++) {
		cout << nodes[i] -> key << (i == nodes.size() - 1 ? "\n" : ", ");
	}
}

void printNodesMap(map<string, Node*> nodes_map) {
	typedef map<string, Node*>::iterator it_type;
	for(it_type iterator = nodes_map.begin(); iterator != nodes_map.end(); iterator++) {
	    cout << iterator -> first << " - " << iterator -> second << endl;
	}
}

void addParents(Node *node, vector<string> &evidenceKeys, map<string, Node*> &nodes_map) {
	for (int i = 0; i < evidenceKeys.size(); i++) {
		string parentKey = evidenceKeys[i].substr(1, evidenceKeys[i].size()-1);
		if (!((node -> idxOfParents).count(parentKey))) {
			(node -> idxOfParents)[parentKey] = (node -> parents).size();
			Node *parentNode = nodes_map[parentKey];
			(node -> parents).push_back(parentNode);
		}
	}
}

void set_probabilities(map<string, Node*> &nodes_map, string query, string evidence, string probability) {
	float prob = atof(probability.c_str());
	if (query[0] == '-')
		prob = 1 - prob;
	query = query.substr(1, query.size()-1);
	Node *queryNode = nodes_map[query];
	if (evidence == "") {
		(queryNode -> probability) = prob;
	}
	else {
		vector<string> evidenceKeys = split(evidence, ',');
		addParents(queryNode, evidenceKeys, nodes_map);
		string probKey = "";
		for (int i = 0; i < evidenceKeys.size(); i++)
			probKey += '0';
		for (int i = 0; i < evidenceKeys.size(); i++) {
			char sign = evidenceKeys[i][0];
			string parentKey = evidenceKeys[i].substr(1, evidenceKeys[i].size()-1);
			int parentIdx = (queryNode -> idxOfParents)[parentKey];
			//cout << "parent key idx = " << parentIdx << endl;
			probKey[parentIdx] = (sign == '+' ? '1' : '0');
		}
		(queryNode -> probabilitiesTable)[probKey] = prob;
	}
	//printNode(queryNode);
}

void read_probabilities(vector<Node*> &nodes, map<string, Node*> &nodes_map) {
	string line;
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
			//cout << "Query: " << query_and_evidence[0] << " --- Evidence: " << evidence << " --- " << prob << endl;
			set_probabilities(nodes_map, query, evidence, prob);
		}
		else {
			string query = query_and_evidence[0];
			//cout << "Query: " << query_and_evidence[0] << " --- " << prob << endl;
			set_probabilities(nodes_map, query, "", prob);
		}
	}
}

void read_queries(vector<Node*> &nodes, map<string, Node*> &nodes_map) {
	string line;
	while(getline(cin, line)) {
		line = remove_chars(line, ' ');
		vector<string> query_and_evidence = split(line, '|');
		string query = query_and_evidence[0];
		vector<string> queries = split(query, ',');
		if (query_and_evidence.size() > 1) {

		}
		else {
			double prob = 1.0;
			for (int i = 0; i < queries.size(); i++) {
				char sign = queries[i][0];
				string nodeKey = queries[i].substr(1, queries[i].size()-1);
				Node *node = nodes_map[nodeKey];
				if ((node -> parents).size() == 0) {
					prob *= (sign == '+' ? node -> probability : (1.0 - node -> probability));
				}
				else {
					double aux_prob = 0.0;
					typedef map<string, float>::iterator it_type;
					map<string, float> probabilitiesTable = node -> probabilitiesTable;
					for(it_type iterator = probabilitiesTable.begin(); iterator != probabilitiesTable.end(); iterator++) {
					    aux_prob += iterator -> second;
					}
					prob *= (sign == '+' ? aux_prob : (1 - aux_prob));
				}
			}
			cout << prob << endl;
		}
	}
}

void getHidden(set<Node*> &hidden, stack<Node*> &nodesStack) {
	while(!nodesStack.empty()) {
		Node *node = nodesStack.top();
		nodesStack.pop();
		if (!hidden.count(node)) {
			hidden.insert(node);
		}
		vector<Node*> parents = node -> parents;
		for (int i = 0; i < parents.size(); i++) {
			Node *parent = parents[i];
			if (!hidden.count(parent)) {
				hidden.insert(parent);
				nodesStack.push(parent);
			}
		}
	}
}

int main () {
	string input_type;
	vector<Node*> nodes = vector<Node*>(0);
	map<string, Node*> nodes_map = map<string, Node*> ();
	while(getline(cin, input_type)) {
		if (input_type == "[Nodes]") {
			readNodes(nodes, nodes_map);
		}
		//getline(cin, input_type);
		if (input_type == "[Probabilities]") {
			read_probabilities(nodes, nodes_map);
		}
		//getline(cin, input_type);
		if (input_type == "[Queries]") {
			read_queries(nodes, nodes_map);
		}
	}
	return 0;
}