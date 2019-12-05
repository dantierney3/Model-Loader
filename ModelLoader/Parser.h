#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class Parser
{
public:
	void parseObj();
	vector<glm::vec3> returnVertex();
	vector<glm::vec2> returnTexture();
	vector<glm::vec3> returnNormal();
};

