#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <queue>


using namespace std;

class Node {
	public:
		Node() {}
		Node(int identifier) {
			this->identifier = identifier;
		}
		Node(int identifier, char ch) {   // for edge case in which we need to generate a node with both to start (possibly redundant)
			this->identifier = identifier;
			this->ch = ch;
		}

		~Node() {
			next_nodes.clear();
		}

		void set_node_ident(int new_identifier){this->identifier = new_identifier;}
		int get_node_ident() {return this->identifier;}

		void set_node_char(char new_ch){this->ch = new_ch;}
		char get_node_char() {return this->ch;}

		void add_next_node(Node *new_reference){
			this->next_nodes.push_back(new_reference);
		}

		vector<Node*> get_node_list(){return this->next_nodes;}

		Node *get_top_node(){
			return this->next_nodes[0];
		}

		bool is_epsilon(){
			return this->ch == '@';
		}

		void set_accepting() {
			this->accepting = true;
		}
		bool is_accepting() {
			return this->accepting;
		}

		int identifier;

		bool operator<(const Node& rhs) const {
			return identifier < rhs.identifier;
		}
		
		bool operator==(const Node& rhs){
			return identifier == rhs.identifier;
		}

		Node *returnThis() {
			return this;
		}
	private:
		char ch;
		bool accepting = false;
		vector<Node*> next_nodes;

};


class Linked_List {
	public:
		Linked_List() {}
		~Linked_List(){
			for(int i = easy_heap.size() -1 ; i >= 0; i--) {
				delete easy_heap[i];
			}
			easy_heap.clear();
		}

		void modify_current(char ch, Node *next_node) {
			current->set_node_char(ch);
			current->add_next_node(next_node);
		}

		void modify_previous(char ch, int prev_node_ident) {
			find_branch_start(prev_node_ident);
			tail->set_node_char(ch);
			tail->add_next_node(current);
		}

		void find_branch_start(int indentifier) {
			current = head;
			for(auto ptr: easy_heap) {
				if(indentifier == ptr->identifier) {
					current = ptr;
					return;
				}
			}
		}

		void add_new_node(int n_identifier, char ch,int identifier) {
			if(tail == current  && n_identifier < identifier) {
				modify_previous(ch,n_identifier);
				return;
			}
			if (n_identifier == tail->get_node_ident()) {
				modify_current(ch,tail);
				current = tail;
				return;
			}
			if(identifier < current->get_node_ident()) {
				find_branch_start(identifier);
			}
			Node *ptr = new Node(n_identifier);
			easy_heap.push_back(ptr);
			num_of_nodes++;
			modify_current(ch,ptr);
			current = ptr;
			if(tail->get_node_ident() <= current->get_node_ident()){tail = current;}
		}

		void populate(vector<string> file_vector) {
			for(string text: file_vector) {
				stringstream ss(text);
				int identifier, next;
				char ch;
				size_t loop_count = 0;
				string temp;
				while(getline(ss,temp,',')) {
					if (loop_count == 0) {
						identifier = stoi(temp);
						}
					else if (loop_count == 1) {
						next = stoi(temp);
						}
					else {
						ch = temp[0];
						}
					loop_count++;
				}
				add_new_node(next,ch,identifier);
				}
				tail->set_accepting();
			}
		void print_current() {
			find_branch_start(8);
			auto list = current->get_node_list();
			for(auto obj : list) {
				cout << obj->get_node_ident() << " ";
			}
			cout << endl;
		}

		vector<Node*> get_eclosure(int identifier) {
			vector<Node*> accessed_list = {easy_heap[identifier]};
			for(int i = 0 ;accessed_list.back()->is_epsilon(); i++) {
				for (Node* temp : accessed_list[i]->get_node_list()) {
   				if (find_if(accessed_list.begin(), accessed_list.end(), [&temp](Node* rhs) { return *temp == *rhs; }) != accessed_list.end()) {
      				continue;
					}
					accessed_list.emplace_back(temp);
				}
			}
			return accessed_list;
		}

		void print_eclosure() {
			for(size_t i = 0; i < easy_heap.size(); i++) {
				auto List = get_eclosure(i);
				cout << "N" << List[0]->get_node_ident() << ": { ";
				for (auto *node: List) {
					cout << "N" << node->get_node_ident() << " ";
				}
				cout << "}" << endl;
			}
		}
	private:
		Node *head = new Node(0);
		Node *tail = head, *current = tail;
		int num_of_nodes = 1;
		vector<Node*> easy_heap = {head};
	
};


class State{
public:
State() {}
~State() {}
private:

};
class DFA{
public:
DFA(Linked_List& nfa) {
	convert_NFA(nfa);
}
~DFA() {}
void convert_NFA(const Linked_List&) {
	
}

private:
};



vector<string> filereader(const string& filepath);

int main() {
	string filepath =  "./input/testcase1.txt";
	vector<string> fileList = filereader(filepath);
	Linked_List NFAs;
	NFAs.populate(fileList);
	NFAs.print_current();
	NFAs.print_eclosure();


	//TODO: DFA code
}

vector<string> filereader(const string& filePath)
	{
	vector<string> processedCode;
	ifstream fileContent(filePath);
	if (!fileContent.is_open())
		{
		throw runtime_error("Error attempting to open file " + filePath);
		}
	cout << "valid file type detected!\n";
	string temp;
	while (getline(fileContent, temp))
		{
		processedCode.emplace_back(temp);
		}
	return processedCode;
	}