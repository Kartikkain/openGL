#include<iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "FrameBufferTexture.h"
#include "Mesh.h"
#include "FBO.h"
#include "RBO.h"



using namespace std;

const int height = 800;
const int width = 800;


int main()
{
	// intialize the GLFW

	glfwInit();
	
	// Tell GLFW what version of opengl we are using

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tell GLFW what profile of glfw we are using
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating the new GLFW window
	
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGl_Tutorial", NULL, NULL);

	float quadVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,//0
		-1.0f, -1.0f,  0.0f, 0.0f,//1
		 1.0f, -1.0f,  1.0f, 0.0f,//2
		 1.0f,  1.0f,  1.0f, 1.0f//3
	};

	GLuint quadverticesindices[] =
	{
		0,1,2,
		0,2,3
	};
	
	float skyboxVertices[] =
	{
		//   Coordinates
		-1.0f, -1.0f,  1.0f,//        7--------6
		 1.0f, -1.0f,  1.0f,//       /|       /|
		 1.0f, -1.0f, -1.0f,//      4--------5 |
		-1.0f, -1.0f, -1.0f,//      | |      | |
		-1.0f,  1.0f,  1.0f,//      | 3------|-2
		 1.0f,  1.0f,  1.0f,//      |/       |/
		 1.0f,  1.0f, -1.0f,//      0--------1
		-1.0f,  1.0f, -1.0f
	};

	unsigned int skyboxIndices[] =
	{
		// Right
		1, 2, 6,
		6, 5, 1,
		// Left
		0, 4, 7,
		7, 3, 0,
		// Top
		4, 5, 6,
		6, 7, 4,
		// Bottom
		0, 3, 2,
		2, 1, 0,
		// Back
		0, 1, 5,
		5, 4, 0,
		// Front
		3, 7, 6,
		6, 2, 3
	};



	// Initializing triangle vertexes

	Vertex verticies[] =
	{
		       // coordinates						// normal						//color			//tex coordinates
		Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},//0
		Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},//1
		Vertex{glm::vec3(1.0f,  0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},//2
		Vertex{glm::vec3(1.0f,  0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},//3

	};

	GLuint indices[] =
	{
		
		0, 1, 2,
		0, 2, 3,
		
	};

	Vertex lightvertices[] =
	{
		Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)}, //0
		Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)}, //1
		Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},  //2
		Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},  //3
		Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)}, //4
		Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)}, //5
		Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},  //6
		Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}   //7
	};

	GLuint lightindicies[] =
	{
		0,1,2,
		0,2,3,
		0,4,7,
		0,7,3,
		3,7,6,
		3,6,2,
		2,6,5,
		2,5,1,
		1,5,4,
		1,4,0,
		4,5,6,
		4,6,7
	};
	
	// Checking if window exist or not 
	if (window == NULL)
	{
		cout << "Could'nt find window";
		glfwTerminate();
		return -1;
	}
	
	// Assigning the window to the current context
	
	glfwMakeContextCurrent(window);

	// Load Glad 
	
	gladLoadGL();
	
	// Assigning the viewport
	
	glViewport(0, 0, width, height);

	string path = "res/wood.png";
	string negativePath = "res/wood_negative.png";
	Texture textures[]
	{
		Texture(path.c_str(), "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE),
		Texture(negativePath.c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	Shader shaderprogram("default.vert", "default.frag");
	Shader lightshader("light.vert", "light.frag");
	Shader skyboxshader("skybox.vert", "skybox.frag");
	Shader framebuffershader("framebuffer.vert", "framebuffer.frag");

	std::vector<Vertex> vert(verticies, verticies + sizeof(verticies) / sizeof(Vertex));
	std::vector<GLuint> indic(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	

	Mesh floor(vert, indic, tex);
		
	std::vector<Vertex> lightvert(lightvertices, lightvertices + sizeof(lightvertices) / sizeof(Vertex));
	std::vector<GLuint> lightindic(lightindicies, lightindicies + sizeof(lightindicies) / sizeof(GLuint));

	


	Mesh Light(lightvert, lightindic, tex);
	
	GLfloat WorldAmbient = 0.2f;
	glm::vec4 lightcolor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightpos = glm::vec3(0.0f, 0.5f, 0.0f);
	glm::vec3 lightrotation = glm::vec3(0.0f, 0.0f, 0.0f);
	

	glm::vec3 pyramidpos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidmodel = glm::mat4(1.0f);
	pyramidmodel = glm::translate(pyramidmodel, pyramidpos);

	GLint light_model_loc = glGetUniformLocation(lightshader.ID, "model");
	GLint light_source_loc = glGetUniformLocation(lightshader.ID, "lightcolor");

	GLint pyramid_model_loc = glGetUniformLocation(shaderprogram.ID, "model");
	GLint pyramid_loc = glGetUniformLocation(shaderprogram.ID, "lightcolor");
	GLint light_pos_loc = glGetUniformLocation(shaderprogram.ID, "lightpos");
	GLint camera_pos_loc = glGetUniformLocation(shaderprogram.ID, "campos");

	GLint Ambient_loc = glGetUniformLocation(shaderprogram.ID, "ambient");
	GLint a_loc = glGetUniformLocation(shaderprogram.ID, "a");
	GLint b_loc = glGetUniformLocation(shaderprogram.ID, "b");
	GLint Outercone_loc = glGetUniformLocation(shaderprogram.ID, "OuterCone");
	GLint Innercone_loc = glGetUniformLocation(shaderprogram.ID, "InnerCone");
	GLint Scale_loc = glGetUniformLocation(shaderprogram.ID, "Scale");
	GLint light_type_loc = glGetUniformLocation(shaderprogram.ID, "isSpot");

	GLint skybox_loc = glGetUniformLocation(skyboxshader.ID, "skybox");
	GLint skybox_view_loc = glGetUniformLocation(skyboxshader.ID, "view");
	GLint skybox_projection_loc = glGetUniformLocation(skyboxshader.ID, "projection");

	GLint framebuffer_texture_loc = glGetUniformLocation(framebuffershader.ID, "screenTexture");
	
	
	floor.BindingTextures(shaderprogram);

	GLuint recVAO, recVBO,recIBO;
	glGenVertexArrays(1, &recVAO);
	glGenBuffers(1, &recVBO);
	glGenBuffers(1, &recIBO);
	glBindVertexArray(recVAO);
	glBindBuffer(GL_ARRAY_BUFFER, recVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, recIBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadverticesindices), &quadverticesindices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	
	

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	
	// Create Frame Buffer

	FBO fbo;
	fbo.Bind();

	// Create Framebuffer Texture

	FBOTexture fbotexture;
	fbotexture.Bind();
	fbotexture.Gettexture(width, height);
	fbotexture.AssignTextureToFramebuffer();
	
	// Create Render Buffer Object

	RBO rbo;
	rbo.Bind();
	rbo.RBOstorage(width, height);
	rbo.RenderBufferToFrameBuffer();

	auto framebufferstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (framebufferstatus != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "framebuffer status code: " << framebufferstatus << std::endl;



	unsigned int skyboxVAO, skyboxVBO, skyboxIBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxIBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::string facesofcube[6] =
	{
		"res/skybox/sky/right.png",
		"res/skybox/sky/left.png",
		"res/skybox/sky/top.png",
		"res/skybox/sky/bottom.png",
		"res/skybox/sky/front.png",
		"res/skybox/sky/back.png"
	};

	unsigned int cubemaptexture;
	glGenTextures(1, &cubemaptexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemaptexture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	for (unsigned int i = 0;i < 6;i++)
	{
		int width, height, color_ch;
		unsigned char* data = stbi_load(facesofcube[i].c_str(), &width, &height, &color_ch, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "fail to load texture" << facesofcube[i] << std::endl;
			stbi_image_free(data);
		}
	}

	

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO io = ImGui::GetIO();(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	framebuffershader.Activate();
	glUniform1i(framebuffer_texture_loc, 0);
	

	float a = 3.0f;
	float b = 0.7f;
	float innerCone = 0.95f;
	float outerCone = 0.90f;
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	bool Spotlight = true;


	while (!glfwWindowShouldClose(window))
	{
		fbo.Bind();
		glClearColor(0.1f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glm::mat4 lightmodel = glm::mat4(1.0f);
		lightmodel = glm::translate(lightmodel, lightpos);
		
		
		camera.updatematrix(45.0f, 0.1f, 100.0f);

		
		camera.input(window);

		

		floor.Draw(shaderprogram, camera);

		
		
		// setting  uniform value 
		
		glUniformMatrix4fv(pyramid_model_loc, 1, GL_FALSE, glm::value_ptr(pyramidmodel));
		glUniform1f(Ambient_loc, WorldAmbient);
		glUniform3f(Scale_loc, scale.x, scale.y, scale.z);
		glUniform4f(pyramid_loc, lightcolor.x, lightcolor.y, lightcolor.z, lightcolor.w);
		glUniform3f(light_pos_loc, lightpos.x, lightpos.y, lightpos.z);
		glUniform3f(camera_pos_loc, camera.Position.x, camera.Position.y, camera.Position.z);
		glUniform1i(light_type_loc, Spotlight);
		glUniform1f(a_loc,a);
		glUniform1f(b_loc,b);
		glUniform1f(Innercone_loc, innerCone);
		glUniform1f(Outercone_loc, outerCone);

		
		Light.Draw(lightshader, camera);

		glUniformMatrix4fv(light_model_loc, 1, GL_FALSE, glm::value_ptr(lightmodel));
		glUniform4f(light_source_loc, lightcolor.x, lightcolor.y, lightcolor.z, lightcolor.w);
		
		
		fbo.Unbind();
		glDisable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		framebuffershader.Activate();
		glBindVertexArray(recVAO);
		fbotexture.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(quadverticesindices), GL_UNSIGNED_INT, 0);

		glDepthFunc(GL_LEQUAL);

		skyboxshader.Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.orientation, camera.up)));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
		glUniform1i(skybox_loc, 0);
		glUniformMatrix4fv(skybox_view_loc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(skybox_projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemaptexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		glDepthFunc(GL_LESS);
		
		ImGui::Begin("My name is the window");
		ImGui::Text("Hello opengl");
		ImGui::InputFloat3("Light Position",&lightpos.x);
		ImGui::InputFloat3("Model Scale", &scale.x);
		if(Spotlight)
		{
			ImGui::SliderFloat("Spot Light inner cone", &innerCone, 0.0f, 1.0f);
			ImGui::SliderFloat("Spot Light outer cone", &outerCone, 0.0f, 1.0f);
		}
		else
		{
			ImGui::SliderFloat("Point Light a", &a, 0.0f, 10.0f);
			ImGui::SliderFloat("Point Light b", &b, 0.0f, 10.0f);
		}
		ImGui::ColorEdit4("light color", (float*)&lightcolor);
		ImGui::Checkbox("spot light", &Spotlight);
		ImGui::End();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		

		glfwSwapBuffers(window);

		// Handling all the events
	
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	
	shaderprogram.Delete();
	lightshader.Delete();
	skyboxshader.Delete();
	fbo.Delete();
	glDeleteVertexArrays(1, &recVAO);
	glDeleteBuffers(1, &recVBO);
	// Destroying  the window before programme ends 
	
	glfwDestroyWindow(window);
	
	
	// terminate the GLFW before programme ends
	
	glfwTerminate();
	return 0;
}