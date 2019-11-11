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
vector< glm::vec3 > temp_v;
vector< glm::vec3 > temp_vI;
vector< glm::vec3 > temp_vN;

void Parser::parseObj()
{
	bool fileLoad = false;
	do
	{
		// Ask the user for the .obj directory
		cout << "Please enter the path of the object you wish to load." << endl;
		string input;
		getline(cin, input);

		// Open file at the directory specified by the user
		ifstream objFile(input);

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
}

