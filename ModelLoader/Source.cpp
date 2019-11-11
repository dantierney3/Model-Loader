#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <iostream>

// Resizes the openGL viewport if the user changes the size of the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* init(int width, int height)
{
	// Initialises the window
	glfwInit();

	// Sets the minimum version of OpenGL the user should have
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Sets the OpenGL profile to include the core functionality; theres no backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the window
	GLFWwindow* window = glfwCreateWindow(width, height, "Test Window", NULL, NULL);

	// Terminates GLFW if window was not created successfully 
	if (window == NULL)
	{
		std::cout << "Error: Failed to create window in 'init'" << std::endl;
		glfwTerminate();
	}

	// Sets the focus to the window
	glfwMakeContextCurrent(window);

	// Tells glfw to trigger the following callback when the window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Tells OpenGL the size of the rendering window
	glViewport(0, 0, width, height);

	// Initialises GLEW; Sets up pointers to OpenGL functions
	glewExperimental = GL_TRUE;
	glewInit();

	return window;
}


int main() {

	// Calls method 'init' to create the window
	GLFWwindow* window = init(1080, 720);

	// Beginning of render loop
	while (!glfwWindowShouldClose(window))
	{
		// Swap colour buffer
		glfwSwapBuffers(window);

		// Check triggered events (Such as keypresses)
		glfwPollEvents();
	} // End render loop

}