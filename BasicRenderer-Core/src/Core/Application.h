#pragma once
#include <Core.h>
#include <GLFW/glfw3.h>

class Application {
	

public:
	int run() {
		initGraphics();

   }

private:
	
	void initGraphics() {
        // glfw: initialize and configure
  // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



        // glfw window creation
        // --------------------
        GLFWwindow* window = glfwCreateWindow(2, 2, "Basic Render", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
       
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (glewInit() != GLEW_OK) {

            std::cout << "Problem initializing glew\n";
        }


        std::cout << glGetString(GL_VERSION) << std::endl;
        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);
	}





};