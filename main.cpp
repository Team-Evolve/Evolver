#include "include/Window.h"
#include "include/Shader.h"
#include "include/Camera.h"
#include "include/Model.h"
#include "include/ObjectManager.h"
#include "include/GUI.h"
#include "include/Timer.h"
#include "include/Transform.h"
#include "include/Input.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

evolver::Input input;

void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	input.ExecuteKeys();
}

void wPressed()
{
	std::cout << "W Key Pressed\n";
}

int main()
{
	input.SetKeyAndAction(GLFW_KEY_W, wPressed);

	evolver::Window window(WIDTH, HEIGHT);
	window.SetKeyboardCallback(Key_Callback);
	
	evolver::Shader modelShader({ "shaders/model/model.vert", "shaders/model/model.frag" }, "model", true);
	evolver::Camera camera(WIDTH, HEIGHT);
	// evolver::Model model("models/test/dragon.obj");
	evolver::ObjectManager objectManager;
	evolver::GUI gui(window.GetWindowPointer());
	evolver::Timer timer;
	evolver::Transform transform;

	LOG_INFO("Window Initialized");

	transform.Translate(glm::vec3(0.0f, 0.0f, 0.0f));
	transform.SetProjMatrix(camera.GetFOV(), (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);

	glViewport(0, 0, WIDTH, HEIGHT);

	while (window.Loop())
	{
		timer.Update();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gui.CreateNewFrame();

		modelShader.Load();
		modelShader.SetMat4("model_matrix", transform.GetModelMatrix());
		modelShader.SetMat4("view_matrix", camera.GetViewMatrix());
		modelShader.SetMat4("proj_matrix", transform.GetProjMatrix());
		objectManager.RenderCube();
		modelShader.Unload();

		gui.StartFrame("Shader Editor");
		gui.SetText("Hello World");
		gui.EndFrame();

		gui.Render();

		// check if the object rendered
		objectManager.UpdateTime(timer.GetMiliseconds());
		objectManager.CheckObjectRenderTime(3.0, 60.0);

		window.Swap();
		window.PollEvents();
	}

	return 0;
}