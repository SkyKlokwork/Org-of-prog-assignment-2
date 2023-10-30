#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <forward_list>

using namespace std;


class State
	{
	private:
		char input;
		bool finalstate = false;
		vector<int> linkedPoint;

	public:
		State() {}

		State(char input)
			{
			this->input = input;
			}

		~State() {}

		void insertNext(int nextp)
			{
			linkedPoint.push_back(nextp);
			}

		vector<int> get_Linked()
			{
			return linkedPoint;
			}

		bool is_split()
			{
			return linkedPoint.size() > 1;
			}

		char get_Char()
			{
			return input;
			}
		bool is_epsilon()
			{
			return input == '@';
			}

		void set_FinalState()
			{
			finalstate = true;
			}

		bool is_FinalState()
			{
			return finalstate;
			}
	};
// possible OBJECT for NFA?
class List
	{
	private:
		vector<State*> NFAs;

	public:
		List() {};

	public:
		void add(size_t identifier, size_t next_node, char ch)
			{
			if (identifier + 1 <= NFAs.size())
				{
				NFAs[identifier]->insertNext(next_node);
				}
			else
				{
				State* node = new State(ch);
				node->insertNext(next_node);
				NFAs.push_back(node);
				}
			}

		void populate_list(vector<string> fileList)
			{
			for (string str : fileList)
				{
				stringstream ss(str);
				string temp;
				size_t slot, pointer;
				int count = 0;
				char data;
				while (getline(ss, temp, ','))
					{
					if (count == 0)
						{
						slot = stoi(temp);
						}
					else if (count == 1)
						{
						pointer = stoi(temp);
						}
					else
						{
						data = temp[0];
						}
					count++;
					}
				add(slot, pointer, data);
				}
			NFAs[NFAs.size() - 1]->set_FinalState();
			}

		char get_value(int thing)
			{
			return NFAs[thing]->get_Char();
			}

		void compile_epsilon() {
			for(State *state : NFAs) {
				if(state->is_epsilon()) {

				}
			}
		}
	};

vector<string> FileReader(string filepath);

int main()
	{
	List List;
	string filepath;
	vector<string> fileList = FileReader(filepath);
	List.populate_list(fileList);
	cout << "value at 13 is: " << List.get_value(13);
	return 0;
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