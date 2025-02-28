#include "Sett_Debug.h"
#include "glfw/glfw3.h"
#include "DeltaTime.h"

static bool vsyncEnabled = true;
float BackColor[3] = {0.308f, 0.504f, 0.784f };
float Outline = 0.04f;


void i_Init_Settings(GLFWwindow *window){
    // Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 420");
}

void i_Update_Settings(){
    // Tell OpenGL a new frame is about to begin
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void i_Debug_Settings()
{
    ImGui::Begin("Sky Lands-Debug");
    ImGui::Text("FPS: %.f", ImGui::GetIO().Framerate);
    ImGui::Text("ms/frame: %.3f", 1000.0f / ImGui::GetIO().Framerate); 
    ImGui::Spacing();  
    if(ImGui::Checkbox("Enable Vsync", &vsyncEnabled)){
        glfwSwapInterval(vsyncEnabled ? 1 : 0);
    }
 ImGui::Spacing();
    ImGui::Text("time: %f", glfwGetTime());
    ImGui::Text("DeltaTime: %f", deltaTime);
 ImGui::Spacing();
    ImGui::Text("Mouse Position: (%f, %f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
    ImGui::ColorEdit3("Background Color", BackColor);
    ImGui::InputFloat("outline ", &Outline, 0.1f, 1.0f, "%.3f");
 ImGui::Spacing();
    ImGui::End();


}

void i_Render_Settings(){
    // Renders the ImGUI elements
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}