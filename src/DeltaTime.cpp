#include "DeltaTime.h"

float deltaTime= 0.0f;
float lastFrame= 0.0f;

void updateDeltaTime(){
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;

    if(deltaTime > 0.1f) deltaTime = 0.1f;

    lastFrame = currentFrame;
}