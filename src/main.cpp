#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include "Model.h"
#include "DeltaTime.h"
#include "Sett_Debug.h"


const unsigned short int width = 800;
const unsigned short int height = 800;



int main()
{

// #1
    if (!glfwInit()) { std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;  //check for error
     }
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //the version
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); //the version
     // Tell GLFW we are using the CORE profile
     // So that means we only have the modern functions
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	 glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Sky Lands ", NULL, NULL);
	
    if (!window) { std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); //here too
        return -2;
     }
    glfwMakeContextCurrent(window);

     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -3; // special one:) & Initialize GLAD
    }
    gladLoadGL();

	const char* versionString = (const char*)glGetString(GL_VERSION);
    printf("OpenGL version: %s\n", versionString);

// #2

	// Create a query object for the GPU time
	GLuint query;
	glGenQueries(1, &query);
	GLuint drawCallsQuery;
	glGenQueries(1, &drawCallsQuery);
	


	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("/home/fly/SKY_LANDS/Resourcefiles/Shader/default.vert",
		  				 "/home/fly/SKY_LANDS/Resourcefiles/Shader/default.frag");

    Shader outliningProgram("/home/fly/SKY_LANDS/Resourcefiles/Shader/outlining.vert", 
							"/home/fly/SKY_LANDS/Resourcefiles/Shader/outlining.frag");

	Shader grassProgram("/home/fly/SKY_LANDS/Resourcefiles/Shader/default.vert",
					    "/home/fly/SKY_LANDS/Resourcefiles/Shader/grass.frag");
	

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);


	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	grassProgram.Activate();
	glUniform4f(glGetUniformLocation(grassProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(grassProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    
//#3

	bool vsyncEnabled =true;
    glfwSwapInterval(vsyncEnabled); //vsync on 
    glEnable(GL_DEPTH_TEST);// what is closer then others
	glViewport(0, 0, width, height);

    //do not use!! .. 
    //glDepthFunc(GL_LESS);


    // glEnable(GL_CULL_FACE); // for renedering and sonic faster  |
    glEnable(GL_FRONT); // the front for an obkect				   |face cool +_-
    glEnable(GL_CCW); //counter clock wise						   |


    // Enables the Stencil Buffer
	glEnable(GL_STENCIL_TEST);
	// Sets rules for outcomes of stecil tests
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

//#4	

    // Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 420");

//#5	

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	//create a camera object
	
	// Load in a model ---
	Model map("/home/fly/SKY_LANDS/Resourcefiles/models/map/scene.gltf");
	Model ground("/home/fly/SKY_LANDS/Resourcefiles/models/ground/scene.gltf");
	Model grass("/home/fly/SKY_LANDS/Resourcefiles/models/grass/scene.gltf");

//#6


	GLuint64 lastGpuTime = 0;
    while (!glfwWindowShouldClose(window))
    {
 	updateDeltaTime();

    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // clears buffer

		glBeginQuery(GL_TIME_ELAPSED, query);

	
    	camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 1000.0f);


		Update_Settings(); //for the imgui update frame
		Debug_Settings(); // for imgui window settings
		glClearColor(BackColor[0], BackColor[1], BackColor[2], 1.0f); // to set the color to the imgui input 


        // End the query
        glEndQuery(GL_TIME_ELAPSED);
		// Get the GPU time
		GLuint64 gpuTime;
		glGetQueryObjectui64v(query, GL_QUERY_RESULT, &gpuTime);
		// Update the last GPU time
		lastGpuTime = gpuTime;



        // Make it so the stencil test always passes
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		// Enable modifying of the stencil buffer
		glStencilMask(0xFF);
        //  ^ | ^ | ^
	    //  Draw a model
		ground.Draw(shaderProgram, camera);


        // Make it so only the pixels without the value 1 pass the test
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		// Disable modifying of the stencil buffer
		glStencilMask(0x00);
		// Disable the depth buffer
		glDisable(GL_DEPTH_TEST);

        outliningProgram.Activate();
		glUniform1f(glGetUniformLocation(outliningProgram.ID, "outlining"), Outline);
		ground.Draw(shaderProgram, camera);
		glDisable(GL_CULL_FACE);


		grass.Draw(grassProgram, camera);
		glEnable(GL_CULL_FACE);

		
        // Enable modifying of the stencil buffer
		glStencilMask(0xFF);
		// Clear stencil buffer
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		// Enable the depth buffer
		glEnable(GL_DEPTH_TEST);

		
		Render_Settings(); // for imgui render frame
		
	    glfwSwapBuffers(window);
	    glfwPollEvents();
    }
    

	glDeleteQueries(1, &query);
    // Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
    // Delete all the objects we've created
    shaderProgram.Delete();
    outliningProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}