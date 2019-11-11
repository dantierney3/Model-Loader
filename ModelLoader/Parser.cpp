#include "Parser.h"
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


// Create temp vectors to store the contents of the .obj file
vector< unsigned int > v, vI, vN;
vector< glm::vec2 > temp_vT;
vector< glm::vec3 > temp_vN;

// Create vectors to store and hold the object vectors after parsing
vector< glm::vec3 > vectors;
vector< glm::vec2 > vT;
vector<glm::vec3 > vN;

void Parser::parseObj()
{
	bool fileLoad = false;

	ifstream objFile;

	do
	{
		// Ask the user for the .obj directory
		cout << "Please enter the path of the object you wish to load." << endl;
		string input;
		getline(cin, input);

		// Open file at the directory specified by the user
		objFile.open(input);

		// Check if the file has been found / opened
		if (objFile.is_open())
		{
			cout << "File opened successfully!" << endl;
			fileLoad = true; // If file is opened, allows the program to exit the loop
		}
		else
		{
			cout << "Error: File path incorrect, or file does not exist" << endl;
		}

	} while (fileLoad == false); // Will retry file load if the file was not found / open

	// Create a value variable to store a line from the file
	string value;

	// Parsing Loop
	while (getline(objFile, value)) // Takes a line from the file and stores it in 'value'
	{
		// Passes the line from the file to a stringstream 'line'
		stringstream line(value);

		// 'word' variable used to store the first word of the line from the stream
		string word;

		// Pass the first word of 'line' to 'word'
		line >> word;

		if (word == "v")
		{
			// Create temporary vector v
			glm::vec3 temp_v;

			// Pass the data from the line to the vector
			line >> temp_v.x >> temp_v.y >> temp_v.z;

			// Push back the vector to the vector of vectors
			vectors.push_back(temp_v);
		}
	}
	
}

