#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
namespace Renderer {
	class Camera {
	private:
		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
		glm::mat4 view;
		glm::mat4 proj;
		float yaw;
		float pitch;
		float mouseSensitivity;
		float zoom;
		float speed;
		void setView() {
			view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		}
		void updateCameraVectors(float pitch, float yaw) {
			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			cameraFront = glm::normalize(direction);
			setView();
		}
	public:
		Camera(glm::vec3 p = glm::vec3(0.0f, 1.0f, 8.0f), glm::vec3 f = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : cameraPos(p), cameraFront(f), cameraUp(up), mouseSensitivity(0.1), yaw(-90.0f), pitch(0.0f), speed(10.0f) {
			setView();


		}
		inline void setPos(glm::vec3 p) { cameraPos = p; }
		inline void setFront(glm::vec3 f) { cameraFront = f; }
		inline void setUp(glm::vec3 up) { cameraUp = up; }
		void setProj(float f, int width, int height) { proj = glm::perspective(glm::radians(f), (float)width / (float)height, 0.1f, 100.0f); }
		inline glm::vec3 getPos() { return cameraPos; }
		inline glm::vec3 getFront() { return cameraFront; }
		inline glm::vec3 getUp() { return cameraUp; }
		inline glm::mat4 getView() { return view; }
		inline glm::mat4 getProj() { return proj; }
		void camMovement(GLFWwindow* window, const float deltaTime) {
			//Movimiento
			float cameraSpeed = speed * deltaTime;
			const float angle = 0.05f;
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				cameraPos += cameraFront * cameraSpeed;
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				cameraPos -= cameraSpeed * cameraFront;
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
				cameraPos -= glm::normalize(cameraUp) * cameraSpeed;
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
				cameraPos += glm::normalize(cameraUp) * cameraSpeed;

			if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {//Se resetea la camara a la posicion de origen
				cameraPos = glm::vec3(0.0f, 1.0f, 8.0f);
				cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
				cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

			}
			//Actualizamos el valor de la matriz vista de la camara
			view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		}
		void camRotation(float xoffset, float yoffset, GLboolean constrainPitch = true)
		{
			xoffset *= mouseSensitivity;
			yoffset *= mouseSensitivity;

			yaw += xoffset;
			pitch += yoffset;

			if (constrainPitch)
			{
				if (pitch > 89.0f)
					pitch = 89.0f;
				if (pitch < -89.0f)
					pitch = -89.0f;
			}

			// update Front, Right and Up Vectors using the updated Euler angles
			updateCameraVectors(pitch, yaw);
		}

		// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
		void ProcessMouseScroll(float yoffset)
		{
			zoom -= (float)yoffset;
			if (zoom < 1.0f)
				zoom = 1.0f;
			if (zoom > 45.0f)
				zoom = 45.0f;
		}

	};

}