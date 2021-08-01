/* * * * * * * * * * * * * * * * * * *
 * Collin Gee and Brady McNeely
 *
 * Project 3: Reddit Joke Generator
 * * * * * * * * * * * * * * * * * * */

//#include "jsoncpp-master/dist/json/json.h" <- didn't exist
#include "jsoncpp-master/include/json/json.h"
#include <iostream>
#include <fstream>

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
void shellSort(Joke jokes[]) {

}

// Implementation of Shell Sort
void mergeSort(Joke jokes[]) {

}

int main() {

	//ifstream f("reddit_jokes.json");
	//File name: "reddit_jokes.json"

	cout << "Welcome to the Reddit Joke Generator\n";
	
	char repeat;

	do {

		

	} while (repeat == 'y');

	return 0;
}