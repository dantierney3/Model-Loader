#include "Parser.h"
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Stores each face
struct Face
{
	std::vector<int> vertexIndex;
	std::vector<int> textureIndex;
	std::vector<int> normalIndex;
};

// Create temp vectors to store the contents of the .obj file
vector< unsigned int > out_V, out_TI, out_NI;
vector< glm::vec2 > temp_vT;
vector< glm::vec3 > temp_vN;

// Create vectors to store and hold the object vectors after parsing
vector< glm::vec3 > vectors;
vector< glm::vec2 > vectorTextures;
vector< glm::vec3 > vectorNormals;

void storeFace(Face face) // Stores the face data in the main array
{

	// variables for loops
	int vICount;
	int tICount;
	int nICount;

	// set up variables for loops
	vICount = face.vertexIndex.size();
	tICount = face.textureIndex.size();
	nICount = face.normalIndex.size();

	for (int i = 0; i < vICount; i++) // Stores the vertex index of the current face
	{
		unsigned int vertexIndex = face.vertexIndex[i];
		out_V.push_back(vertexIndex);
	}
	for (int i = 0; i < tICount; i++)	// Stores the texture index for the current face
	{
		unsigned int textureIndex = face.textureIndex[i];
		out_TI.push_back(textureIndex);
	}
	for (int i = 0; i < nICount; i++)	// Stores the normal index for the current face
	{
		unsigned int normalIndex = face.normalIndex[i];
		out_NI.push_back(normalIndex);
	}
}

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
	string currentLine;

	// Parsing Loop
	while (getline(objFile, currentLine)) // Takes a line from the file and stores it in 'value'
	{
		// Passes the line from the file to a stringstream 'line'
		stringstream line(currentLine);

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

			// Debug output to make sure that the file is being loaded correctly
			cout << word << ": " << temp_v.x << " " <<temp_v.y << " " << temp_v.z << endl;

			// Push back the vector to the vector 'vectors'
			vectors.push_back(temp_v);
		}
		else if (word == "vt")
		{
			// Create temporary vector
			glm::vec2 temp_vt;

			// Pass the data from the line to the vector
			line >> temp_vt.x >> temp_vt.y;

			// Debug output to make sure that the file is being loaded correctly
			cout << word << ": " << temp_vt.x << " " << temp_vt.y << endl;
			// Push bacl the vector to the vector 'vectorTextures'
			vectorTextures.push_back(temp_vt);
		}
		else if (word == "vn")
		{
			// Create a temporary vector
			glm::vec3 temp_vn;

			// Pass the data from the line to the vector
			line >> temp_vn.x >> temp_vn.y >> temp_vn.z;

			// Debug output to make sure the file is being loaded correctly
			cout << word << ": " << temp_vn.x << " " << temp_vn.y << " " << temp_vn.z << endl;

			// Push back the vector to the vector 'vectorNormals'
			vectorNormals.push_back(temp_vn);
		}
		else if (word == "f")
		{
			Face face;

			// Create temp arrays for indexes
			int vertexIndex[3], uvIndex[3], normalIndex[3];

			// Determine the set size of the f values

			std::string temp;	// Create string to store the first series of f values
			std::string value;

			//Debug output to show f values in command line
			string lineString;
			lineString = line.str();
			cout << word << ": " << lineString << endl;

			while (!line.eof()) // Check that we arent at the end of the line
			{
				line >> temp; // Put the next "word" from line into the temp string
				if (!temp.empty()) // Check that temp isnt empty
				{
					std::istringstream item(temp);
					getline(item, value, '/');
					face.vertexIndex.push_back(std::stoi(value) - 1);
					getline(item, value, '/');
					if (!value.empty())		// Check if the face has texture coords
					{
						face.textureIndex.push_back(std::stoi(value) - 1);
					}
					if (getline(item, value, '/')) // Check if the face has normals
					{
						face.normalIndex.push_back(std::stoi(value) - 1);
					} 
				}
			}
			
		}
		else
		{
			cout << "Incompatible file type!" << endl;
		}
	}
	
}

