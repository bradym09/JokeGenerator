/* * * * * * * * * * * * * * * * * * *
 * Collin Gee and Brady McNeely
 *
 * Project 3: Reddit Joke Generator
 * * * * * * * * * * * * * * * * * * */

//#include "jsoncpp-master/dist/json/json.h" <- didn't exist
#include "jsoncpp-master/include/json/json.h"
#include <iostream>
#include <fstream>
#include <vector>

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
//									  ^ Feel free to change these
bool validType(string type) {
	if (type == "id" || type == "score" || type == "type" || type == "total")
		return true;
	return false;
}

//Checking for valid sorting direction
bool validDirection(string direction) {
	if (direction == "ascending" || direction == "descending")
		return true;
	return false;
}

// Implementation of Shell Sort
void shellSort(vector<Joke>& jokes) {

}

// Implementation of Shell Sort
void mergeSort(vector<Joke>& jokes) {

}

int main() {
	// Initializing the necessary classes
	Json::Value root;
	Json::Reader read;

	//Reading the json object
	string fileName = "reddit_jokes.json";
	ifstream file(fileName);
	file >> root;
	vector<Joke> jokes;
	

	cout << root.size() << endl;

	//Filling the jokes vector
	for (int i = 0; i < root.size(); i++) {
		Joke joke = Joke(root[i]["id"].asString(), root[i]["title"].asString(),
			root[i]["body"].asString(), root[i]["score"].asInt());
		jokes.push_back(joke);
	}

	jokes[0].print();

	cout << "Welcome to the Reddit Joke Generator\n";

	char repeat = 'n';

	do {

		//Getting one or two priorites from user
		cout << "Would you like to sort with 1 or 2 priorities? ";
		int priorityCount;
		cin >> priorityCount;

		cout << "Great! " << priorityCount << " it is.\n";


		//Getting type and directions
		vector<pair<string, string>> priorities;
		for (int i = 0; i < priorityCount; i++) {

			string type, direction;

			//Loop until valid type and direction are given
			do {
				cout << "Please type how you would like to sort and specify ascending/descending separated by a space\n";
				cout << "Sorting options: id, score, title, total (title and total are lengths)\n";

				cin >> type;
				cin >> direction;

			} while (!validType(type) || !validDirection(direction));
			
			priorities.push_back({ type, direction });
		}


		//Determine sorting method
		string sort;

		do {
			cout << "Would you like to use a shell or merge sort? (s/m) ";
			cin >> sort;
		} while (!(sort == "s" || sort == "m"));

		if (sort == "s")
			shellSort(jokes);
		else
			mergeSort(jokes);
		
		cout << "Jokes have been sorted!\n";


		//Printing jokes
		string printing;

		do {
			string index;

			//Loop for valid input
			do {
				cout << "Please choose a joke index (1-" << root.size() << ") or enter 'R' for a random joke ";
				cin >> index;
			} while (!(index == "R" || (stoi(index) > 1 && stoi(index) < root.size())));

			//Print the joke
			if (index == "R") {
				//Print random joke
				jokes[rand() % root.size()].print();
			}
			else
				jokes[stoi(index) - 1].print();

			//Ask the user if they want to print another joke
			cout << "Would you like to print another joke? (y/n) ";
			cin >> printing;
			
		} while (printing == "y");


		//Ask the user if they want to sort again
		cout << "Would you like to use the Reddit Joke Generator again? (y/n) ";
		cin >> repeat;

	} while (repeat == 'y');

	cout << "Thank you for using the Reddit Joke Generator! Goodbye!\n";

	return 0;
}