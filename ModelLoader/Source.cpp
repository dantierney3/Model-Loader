#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <iostream>

// Resizes the openGL viewport if the user changes the size of the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

} // End framebuffer_size_callback



// Method to Initialise the render window

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

} // End init

// Input processing
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		// Closes the rendering window if the escape key is pressed
		glfwSetWindowShouldClose(window, true);

		// Output key press to console
		std::cout << "User pressed ESCAPE key, render window closed." << std::endl;

	} // End if

} // End processInput

// Set the background color of the render window
void renderWindowColor(GLFWwindow* window)
{

	// Sets the color of the window to the specified color
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

} // End renderWindowColor

int main() {

	// Calls method 'init' to create the window
	GLFWwindow* window = init(1080, 720);

	// Beginning of render loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any keys are being pressed during the render loop
		processInput(window);

		// Render commands here -->
		renderWindowColor(window);

		// Swap colour buffer
		glfwSwapBuffers(window);

		// Check triggered events (Such as keypresses)
		glfwPollEvents();
	} // End render loop

	// Termiante GLFW
	glfwTerminate();
	return 0;

} // End main