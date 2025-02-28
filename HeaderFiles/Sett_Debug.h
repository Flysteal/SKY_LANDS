#ifndef SET_DEBUG_H
#define SET_DEBUG_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

extern float BackColor[3];
extern float Outline;

extern void i_Init_Settings(GLFWwindow *window); ///for init imgui settings
extern void i_Debug_Settings(); //for imgui settings
extern void i_Update_Settings(); //for imgui settings
extern void i_Render_Settings();// for imgui render 
// extern void 


#endif