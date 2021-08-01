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

// Implementation of Shell Sort
void shellSort(vector<Joke> jokes) {

}

// Implementation of Shell Sort
void mergeSort(vector<Joke> jokes) {

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

	cout << "Welcome to the Reddit Joke Generator\n";

	char repeat = 'n';

	do {

		

	} while (repeat == 'y');

	
	return 0;
}