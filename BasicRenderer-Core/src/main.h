#pragma once
#include <iostream>
#include <fstream>
//#include <gl/glew.h>
//#include <GLFW/glfw3.h>
#include <string>
//#include <sstream>
#include "Shader.h"
#include "Core/BOX.h"
#include "Camera.h"
#include "Texture.h"
#include "Mesh.h"
#include "Core/Model.h"


    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    glm::mat4 projection = glm::mat4(1.0f);
    Camera cam;
    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;
    bool firstMouse = true;
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

    int boot();


    int main()
    {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



        // glfw window creation
        // --------------------
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Basic Render", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, mouse_callback);

        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (glewInit() != GLEW_OK) {

            std::cout << "Problem initializing glew\n";
        }


        std::cout << glGetString(GL_VERSION) << std::endl;
        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);

        // build and compile our shader zprogram
        // ------------------------------------
        Shader ourShader("BasicShader.shader");
        //Shader ourShader("StandardMatShader.shader");

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------



        // world space positions of our cubes
        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        Mesh cube;
        cube.init(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
            cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);
        //Mesh tengu;
        //tengu.importFile("tengu.obj");
        //tengu.setSize(0.12);


        Texture colorTex("SeamlessWood-Diffuse.jpg");
        Texture tenguColorTex("tengu-color.png");
        Texture tenguNormalTex("tengu-normal.png");
        Texture normalTex("SeamlessWood-NormalMap.tif");
        // either set it manually like so:
        Material mat(&ourShader);
        mat.addColorTex(&colorTex);
        mat.addNormalTex(&normalTex);

        Material tengu_m(&ourShader);
        tengu_m.addColorTex(&tenguColorTex);
        tengu_m.addNormalTex(&tenguNormalTex);
        Model demon;
        demon.loadMesh("tengu.obj");
        demon.setScale(0.12);
        demon.loadMaterial(&tengu_m);
        // or set it via the texture class
        //ourShader.setInt("colorTex", 0);
        cube.setMaterial(&mat);
        //tengu.setMaterial(&tengu_m);

        cam.setProj(45.0, SCR_WIDTH, SCR_HEIGHT);


        //projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        // render loop
        // -----------
        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            ourShader.bind();
            //processInput(window);


            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!



                //colorTex.bind(0);


           // glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

            //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            // pass transformation matrices to the shader
            //ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
            //ourShader.setMat4("view", view);
            ourShader.setMat4("projection", cam.getProj());
            ourShader.setMat4("view", cam.getView());


            for (unsigned int i = 0; i < 10; i++)
            {
                // calculate the model matrix for each object and pass it to shader before drawing
                //glm::mat4 model = glm::mat4(1.0f);
                //model = glm::translate(model, cubePositions[i]);
                //cube.setModel(model);
                cube.setPos(cubePositions[i]);
                //cube.setOffset(cubePositions[i]);
                float angle = 20.0f * i;
                cube.setSize(0.5);
                cube.setRotation(angle, glm::vec3(1.0f, 0.3f, 0.5f));
                //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
              // model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));

                cube.draw();
                // glDrawElements(GL_TRIANGLES, cubeNTriangleIndex*3, GL_UNSIGNED_INT, (void*)0);
                  //glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            //tengu.draw();
           demon.draw();


            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }


        glfwTerminate();
        return 0;
    }


    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        cam.camMovement(window, deltaTime);

    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
            if (firstMouse)
            {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

            lastX = xpos;
            lastY = ypos;

            cam.camRotation(xoffset, yoffset);
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
            firstMouse = true;
        }
    }


    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {

        cam.setProj(45.0f, (float)width, (float)height);

        glViewport(0, 0, width, height);
    }
    int boot() {










        return 1;
    }
