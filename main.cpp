#include "include/Window.h"
#include "include/Shader.h"
#include "include/Camera.h"
#include "include/ShapeFactory.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

int main()
{
	evolver::Window window(WIDTH, HEIGHT);
	window.SetWindowAtCenter();
	
	evolver::Shader modelShader({ "shaders/model/model.vert", "shaders/model/model.frag" }, "model", true);
	evolver::Camera camera(WIDTH, HEIGHT);
	evolver::ShapeFactory shapeFactory;

	LOG_INFO("Window Initialized");

	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 proj_matrix = glm::perspective(glm::radians(camera.GetFOV()), (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
	
	glViewport(0, 0, WIDTH, HEIGHT);

	while (window.Loop())
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		modelShader.Load();
		modelShader.SetMat4("model_matrix", model_matrix);
		modelShader.SetMat4("view_matrix", camera.GetViewMatrix());
		modelShader.SetMat4("proj_matrix", proj_matrix);
		shapeFactory.RenderCube();
		modelShader.Unload();

		window.Swap();
		window.PollEvents();
	}

	return 0;
}