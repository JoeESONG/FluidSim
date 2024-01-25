//
//  Main.cpp
//  FluidSimDemo
//
//

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "FluidSimEffect.h"

const int DEFAULT_WIDTH = 1080;
const int DEFAULT_HEIGHT = 1440;

SimEnv simEnv;
FluidSimEffect effect;
bool playing = true;

void InitSimEnv()
{
	simEnv.SetDeltaTime(0.1f);
	simEnv.SetGravity(-10.0f);
	simEnv.SetRestDensity(0.01f);
	simEnv.SetGasConstant(0.001f);
	simEnv.SetViscosityConstant(0.002f);
	simEnv.SetSurfaceTensionConstant(0.005f);
	simEnv.SetCoreRadius(0.10f);
	simEnv.SetWaterTankSize(glm::vec2(2.5f, 2.5f));
	simEnv.SetWaterBlobSize(glm::vec2(1.0f, 1.5f));
	simEnv.SetWaterBlobInitY(2.0f);
	simEnv.SetParticleCount(500);
	simEnv.SetParticleMass(0.01f);

	simEnv.m_useSpikyKernelForPressure = false;
	simEnv.m_useViscosityKernel = false;
	simEnv.m_usePoly6KernelForSurfaceTension = false;

}

bool InitEffect(GLFWwindow* window)
{
	bool ret = false;

	effect.Destroy();

	ret = effect.Init();
	if (ret)
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		effect.Resize(width, height);
	}

	return ret;
}

void InitUI(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void UpdateUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();

	ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
	flags |= ImGuiWindowFlags_NoFocusOnAppearing;
	flags |= ImGuiWindowFlags_NoSavedSettings;
	flags |= ImGuiWindowFlags_NoMove;
	flags |= ImGuiWindowFlags_NoNav;

	ImGuiViewport* viewport = ImGui::GetMainViewport();

	float padding = 10.0f;

	ImVec2 pos;
	pos.x = viewport->WorkPos.x + viewport->WorkSize.x - padding;
	pos.y = viewport->WorkPos.y + padding;

	ImGui::SetNextWindowPos(pos, ImGuiCond_Always, ImVec2(1.0f, 0.0f));
	ImGui::SetNextWindowBgAlpha(0.8f);

	if (ImGui::Begin("SimEnv", nullptr, flags))
	{
		ImGui::SliderFloat("ViscosityConstant", &simEnv.m_viscosityConstant, 0.0f, 0.1f);
		ImGui::SliderFloat("SurfaceTensionConstant", &simEnv.m_surfaceTensionConstant, 0.0f, 0.01f);
		ImGui::SliderFloat("CoreRadius", &simEnv.m_coreRadius, 0.1f, 0.3f);
		ImGui::SliderFloat("WaterBlobInitY", &simEnv.m_waterBlobInitY, 2.0f, 6.0f);
		ImGui::SliderInt("ParticleCount", &simEnv.m_particleCount, 100, 2000);

		ImGui::Checkbox("UseSpikyKernelForPressure", &simEnv.m_useSpikyKernelForPressure);
		ImGui::Checkbox("UseViscosityKernel", &simEnv.m_useViscosityKernel);
		ImGui::Checkbox("UsePoly6KernelForSurfaceTension", &simEnv.m_usePoly6KernelForSurfaceTension);

		ImGui::Indent(100.0f);

		if (!playing)
		{
			if (ImGui::Button("Play"))
			{
				playing = true;
			}
		}
		else
		{
			if (ImGui::Button("Pause"))
			{
				playing = false;
			}
		}

		ImGui::SameLine(220.0f);

		if (ImGui::Button("Reset"))
		{
			playing = true;
			effect.SetEnv(simEnv);
		}

		ImGui::Unindent();
	}

	ImGui::End();
	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ErrorCallback(int ec, const char* desc)
{
	std::cerr << "error code " << ec << ": " << desc << std::endl;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	effect.Resize(width, height);
	effect.Draw();

	glfwSwapBuffers(window);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		else if (key == GLFW_KEY_R)
		{
			effect.Reset();
		}
	}
}

int main(int argc, const char* argv[])
{
	glfwSetErrorCallback(ErrorCallback);

	if (glfwInit() != GLFW_TRUE)
	{
		std::cerr << "Failed to init glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "FluidSimDemo", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	float xscale, yscale;
	glfwGetWindowContentScale(window, &xscale, &yscale);

	int width, height;
	width = int(DEFAULT_WIDTH / xscale);
	height = int(DEFAULT_HEIGHT / yscale);

	glfwSetWindowSize(window, width, height);

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetKeyCallback(window, KeyCallback);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to init glew" << std::endl;
		return -1;
	}

	std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	InitSimEnv();

	if (!InitEffect(window))
	{
		std::cerr << "Failed to init effect" << std::endl;
		return -1;
	}

	if (playing)
	{
		effect.SetEnv(simEnv);
	}

	InitUI(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		effect.Update(playing);
		effect.Draw();

		UpdateUI();

		glfwSwapBuffers(window);
	}

	effect.Destroy();

	glfwTerminate();

	return 0;
}

