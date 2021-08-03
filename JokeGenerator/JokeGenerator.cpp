/* * * * * * * * * * * * * * * * * * *
 * Collin Gee and Brady McNeely
 *
 * Project 3: Reddit Joke Generator
 * * * * * * * * * * * * * * * * * * */

#include "jsoncpp-master/include/json/json.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

class Joke {
private:
	string title, body, id;
	int score;
	int titleSize;
	int bodySize;

	void setTitleSize() {
		this->titleSize = title.size();
	}
	void setBodySize() {
		this->bodySize = body.size();
	}
public:
	
	void print() {
		cout << title << endl;
		cout << body << endl;
	}

	//Returns string version of priority type (parameter is the priority type the user entered ex. score or id)
	string getPriorityValue(string priority) {
		if (priority == "score")
			return to_string(score);
		else if (priority == "title")
			return to_string(titleSize);
		else if (priority == "total")
			return to_string(titleSize + bodySize);
		else
			return id;
	}

	Joke() {
		// Shouldn't ever need this
		// Setting the 
		cout << "We are calling the default joke constructor\nThis is an issue\n";
		this->id = "DEFAULT JOKE CONSTRUCTOR";
		this->title = "DEFAULT JOKE CONSTRUCTOR";
		this->body = "DEFAULT JOKE CONSTRUCTOR";
		this->score = 999999999;
	}
	Joke(string newId, string newTitle, string newBody, int newScore) {
		this->id = newId;
		this->title = newTitle;
		this->body = newBody;
		this->score = newScore;
	}
};

//Checking for valid sorting criteria (Current types are id, score, title length, and total length)
bool validType(string type) {
	if (type == "id" || type == "score" || type == "title" || type == "total")
		return true;
	return false;
}

//Checking for valid sorting direction
bool validDirection(string direction) {
	if (direction == "ascending" || direction == "descending")
		return true;
	return false;
}

//Implementation of Shell Sort (General layout of the algorithm comes from the second set of lecture slides for Module 6: Sorting)
void shellSort(vector<Joke>& jokes, vector<pair<string, string>> priorities) {
	for (int i = 0; i < priorities.size(); i++) {
		int gap = jokes.size() / 2;
		while (gap > 0) {
			for (int j = 0; j + gap < jokes.size(); j++) {
				
				//Sorting first priority
				if (i == 0) {
					if (priorities[i].second == "ascending" && jokes[j].getPriorityValue(priorities[i].first) > jokes[j + gap].getPriorityValue(priorities[i].first))
						swap(jokes[j], jokes[j + gap]);
					else if (jokes[j].getPriorityValue(priorities[i].first) < jokes[j + gap].getPriorityValue(priorities[i].first))
						swap(jokes[j], jokes[j + gap]);
				}
				
				//Sorting second priority
				else if (i == 1) {
					if (jokes[j].getPriorityValue(priorities[0].first) == jokes[j + gap].getPriorityValue(priorities[0].first)) {
						if (priorities[i].second == "ascending" && jokes[j].getPriorityValue(priorities[i].first) > jokes[j + gap].getPriorityValue(priorities[i].first))
							swap(jokes[j], jokes[j + gap]);
						else if (jokes[j].getPriorityValue(priorities[i].first) < jokes[j + gap].getPriorityValue(priorities[i].first))
							swap(jokes[j], jokes[j + gap]);
					}
				}
			}

			if (gap == 2)
				gap = 1;
			else
				gap /= 2.2;
		}
	}
}

//Implementing merge sort
void merge(vector<Joke>& jokes, int start, int middle, int end, bool isAscending, string type) {
	//inspiration taken from Aman's powerpoint sorting-2
	int first = middle - start + 1;
	int second = end - middle;

	vector<Joke> half1;
	vector<Joke> half2;

	//combining the split vectors
	int t1 = 0;
	int t2 = 0;
	for (int ii = 0; ii < first; ii++) {
		t1 = ii + start;
		half1.push_back(jokes.at(t1));
	}
	for (int jj = 0; jj < second; jj++) {
		t2 = jj + middle + 1;
		half2.push_back(jokes.at(t2));
	}

	int p1 = 0;
	int p2 = 0;

	//sorting the 2 split vectors while combining them
	while ((p1 < half1.size()) && (p2 < half2.size())) {
		if (half1.at(p1).getPriorityValue(type) <= half2.at(p2).getPriorityValue(type)) {
			if (isAscending) {
				
				jokes.at(start) = half1.at(p1);
				p1++;
			}
			else {
				
				jokes.at(start) = half2.at(p2);
				p2++;
			}
			start++;
		}
		else {
			if (isAscending) {
				
				jokes.at(start) = half2.at(p2);
				p2++;
			}
			else {
				
				jokes.at(start) = half1.at(p1);
				p1++;
			}
			start++;
		}
	}

	while (p1 < half1.size()) {
		jokes.at(start) = half1.at(p1);
		p1++;
		start++;
	}

	while (p2 < half2.size()) {
		jokes.at(start) = half2.at(p2);
		p2++;
		start++;
	}
}

void mergeSortRec(vector<Joke>& jokes, int start, int end, bool isAscending, string type) {
	//inspiration taken from Aman's powerpoint sorting-2

	//Keeps recursively splitting and then combines at the end
	if (start < end) {
		
		int middle = start + (end - start) / 2;
		mergeSortRec(jokes, start, middle, isAscending, type);
		mergeSortRec(jokes, middle + 1, end, isAscending, type);
		merge(jokes, start, middle, end, isAscending, type);
	}
}

void mergeSortTotal(vector<Joke>& jokes, vector<pair<string, string>> priorities) {
	//determines the ascending or descending of the list
	if (priorities.at(0).second == "ascending") {
		mergeSortRec(jokes, 0, ((int)jokes.size() - 1), true, priorities.at(0).first);
	}
	else {
		mergeSortRec(jokes, 0, ((int)jokes.size() - 1), false, priorities.at(0).first);
	}
}

int main() {

	cout << "Loading File...\n";

	// Initializing the necessary classes
	Json::Value root;
	Json::Reader read;

	//Reading the json object
	string fileName = "reddit_jokes.json";
	ifstream file(fileName);
	file >> root;
	vector<Joke> jokes;

	//Filling the jokes vector
	for (int i = 0; i < root.size(); i++) {
		Joke joke = Joke(root[i]["id"].asString(), root[i]["title"].asString(),
			root[i]["body"].asString(), root[i]["score"].asInt());
		jokes.push_back(joke);
	}

	cout << "Welcome to the Reddit Joke Generator\nDISCLAIMER: These jokes were not written by the creators of the program and some may be seen as inappropriate\n\n";

	char repeat = 'n';

	do {

		//Getting type and directions
		vector<pair<string, string>> priorities;
		string type, direction;

		//Loop until valid type and direction are given
		do {
			cout << "Please type how you would like to sort and specify ascending/descending separated by a space\n";
			cout << "Sorting options: id, score, title, total (title and total are lengths)\n";

			cin >> type;
			cin >> direction;

			cout << endl;

		} while (!validType(type) || !validDirection(direction));
			
		priorities.push_back({ type, direction });


		//Shell sort
		vector<Joke> shell = jokes;

		auto start = chrono::high_resolution_clock::now();
		shellSort(shell, priorities);
		auto stop = chrono::high_resolution_clock::now();

		chrono::duration<double> shellTime = stop - start;
		cout << "Shell Sort Time: " << shellTime.count() << endl;

		//Merge Sort
		vector<Joke> merge = jokes;

		start = chrono::high_resolution_clock::now();
		mergeSortTotal(merge, priorities);
		stop = chrono::high_resolution_clock::now();

		chrono::duration<double> mergeTime = stop - start;
		cout << "Merge Sort Time: " << mergeTime.count() << endl;
		

		cout << "Jokes have been sorted!\n\n";


		//Printing jokes
		string printing;

		do {
			string index;

			//Loop for valid input
			do {
				cout << "Please choose a joke index (1-" << root.size() << ") or enter 'R' for a random joke ";
				cin >> index;
			} while (!(index == "R" || (stoi(index) >= 1 && stoi(index) < root.size())));

			//Print the joke
			if (index == "R") {
				//Print random joke
				shell[rand() % root.size()].print();
			}
			else
				shell[stoi(index) - 1].print();

			//Ask the user if they want to print another joke
			cout << "Would you like to print another joke? (y/n) ";
			cin >> printing;
			cout << endl;
			
		} while (printing == "y");


		//Ask the user if they want to sort again
		cout << "Would you like to use the Reddit Joke Generator again? (y/n) ";
		cin >> repeat;
		cout << endl;

		priorities.clear();

	} while (repeat == 'y');

	cout << "Thank you for using the Reddit Joke Generator! Goodbye!\n";

	return 0;
}