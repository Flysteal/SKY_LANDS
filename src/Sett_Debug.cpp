#include "Sett_Debug.h"
#include "glfw/glfw3.h"
#include "DeltaTime.h"

static bool vsyncEnabled = true;
float BackColor[3] = { 0.0f, 0.0f, 0.0f };
float Outline = 0.04f;

void Update_Settings(){
    // Tell OpenGL a new frame is about to begin
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Debug_Settings()
{
    ImGui::Begin("Sky Lands-Debug");

    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::SameLine();
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

void Render_Settings(){
    // Renders the ImGUI elements
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}