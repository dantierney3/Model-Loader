
#include "Parser.h"


using namespace std;

// Stores each face
struct Face
{
	std::vector<int> vertexIndex;
	std::vector<int> textureIndex;
	std::vector<int> normalIndex;
};

// Struct to return the object back to the main class
struct Object
{
	vector<glm::vec3> vertex;
	vector<glm::vec2> texture;
	vector<glm::vec3> normal;
};

// Create temp vectors to store the contents of the .obj file
vector< unsigned int > out_V, out_TI, out_NI;
vector< glm::vec2 > temp_vT;
vector< glm::vec3 > temp_vN;

// Create vectors to store and hold the object vectors after parsing
vector< glm::vec3 > vectors;
vector< glm::vec2 > vectorTextures;
vector< glm::vec3 > vectorNormals;

// Output vectors
vector< glm::vec3 > vertex_out;
vector< glm::vec2 > texture_out;
vector< glm::vec3 > normal_out;

// output object
Object object;

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

	// Setup temp variables to store vectors
	glm::vec3 temp_vector;
	glm::vec2 temp_texture;
	glm::vec3 temp_normal;

	if (vICount == 3 && tICount == 3 && nICount == 3)
	{
		cout << "Face is a triangle" << endl;

		temp_vector = vectors[face.vertexIndex[0]];
		temp_texture = vectorTextures[face.textureIndex[0]];
		temp_normal = vectorNormals[face.normalIndex[0]];

		vertex_out.push_back(temp_vector);
		texture_out.push_back(temp_texture);
		normal_out.push_back(temp_normal);

		temp_vector = vectors[face.vertexIndex[1]];
		temp_texture = vectorTextures[face.textureIndex[1]];
		temp_normal = vectorNormals[face.normalIndex[1]];

		vertex_out.push_back(temp_vector);
		texture_out.push_back(temp_texture);
		normal_out.push_back(temp_normal);

		temp_vector = vectors[face.vertexIndex[2]];
		temp_texture = vectorTextures[face.textureIndex[2]];
		temp_normal = vectorNormals[face.normalIndex[2]];

		vertex_out.push_back(temp_vector);
		texture_out.push_back(temp_texture);
		normal_out.push_back(temp_normal);

		cout << "Face stored!" << endl;
	}
	else if (vICount == 4 && tICount == 4 && nICount == 4)
	{
		cout << "Face is a square, triangulating..." << endl;

		temp_vector = vectors[face.vertexIndex[0]];
		temp_texture = vectorTextures[face.textureIndex[0]];
		temp_normal = vectorNormals[face.normalIndex[0]];

		vertex_out.push_back(temp_vector);
		texture_out.push_back(temp_texture);
		normal_out.push_back(temp_normal);

		temp_vector = vectors[face.vertexIndex[1]];
		temp_texture = vectorTextures[face.textureIndex[1]];
		temp_normal = vectorNormals[face.normalIndex[1]];

		vertex_out.push_back(temp_vector);
		texture_out.push_back(temp_texture);
		normal_out.push_back(temp_normal);

		temp_vector = vectors[face.vertexIndex[2]];
		temp_texture = vectorTextures[face.textureIndex[2]];
		temp_normal = vectorNormals[face.normalIndex[2]];

		vertex_out.push_back(temp_vector);
		texture_out.push_back(temp_texture);
		normal_out.push_back(temp_normal);

		cout << "First triangle stored!" << endl;

		temp_vector = vectors[face.vertexIndex[0]];
		temp_texture = vectorTextures[face.textureIndex[0]];
		temp_normal = vectorNormals[face.normalIndex[0]];

		vertex_out.push_back(temp_vector);
		texture_out.push_back(temp_texture);
		normal_out.push_back(temp_normal);

		temp_vector = vectors[face.vertexIndex[2]];
		temp_texture = vectorTextures[face.textureIndex[2]];
		temp_normal = vectorNormals[face.normalIndex[2]];

		vertex_out.push_back(temp_vector);
		texture_out.push_back(temp_texture);
		normal_out.push_back(temp_normal);

		temp_vector = vectors[face.vertexIndex[3]];
		temp_texture = vectorTextures[face.textureIndex[3]];
		temp_normal = vectorNormals[face.normalIndex[3]];

		vertex_out.push_back(temp_vector);
		texture_out.push_back(temp_texture);
		normal_out.push_back(temp_normal);

		cout << "Second triangle stored!" << endl;
		cout << "Face stored!" << endl;
	}
	else
	{
		cout << "File is corrupt or missing data" << endl;
	}

	// Free up memory (maybe)
	//delete[] & vICount, tICount, nICount, temp_vector, temp_texture, temp_normal;
	//cout << vICount;
	cout << "Face storage process complete" << endl;
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
			cout << word << ": " << temp_v.x << " " << temp_v.y << " " << temp_v.z << endl;

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
			storeFace(face);

		}
		else
		{
			cout << "Incompatible file type!" << endl;
		}
	}

	object.vertex = vertex_out;
	object.texture = texture_out;
	object.normal = normal_out;
}

vector<glm::vec3> Parser::returnVertex() // returns the vertex vector
{
	return vertex_out;
}

vector<glm::vec2> Parser::returnTexture() // returns the textures vector
{
	return texture_out;
}

vector<glm::vec3> Parser::returnNormal() // returns the normals vector
{
	return normal_out;
}