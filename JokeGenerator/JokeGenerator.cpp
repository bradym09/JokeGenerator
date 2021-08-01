/* * * * * * * * * * * * * * * * * * *
 * Collin Gee and Brady McNeely
 *
 * Project 3: Reddit Joke Generator
 * * * * * * * * * * * * * * * * * * */

#include "jsoncpp-master\dist\json\json.h"
#include <iostream>
#include <fstream>

using namespace std;

class Joke {
private:
	string title, body, id;
	int score;

public:
	Joke();
	Joke(string newId, string newTitle, string newBody, int newScore);
};

void shellSort(Joke jokes[]) {

}

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