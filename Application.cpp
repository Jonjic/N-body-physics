#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "stb_image.h"
#include <iostream>
#include<vector>
#include<fstream> 
#include<time.h> 
#include <array>
#include <time.h>


#define G 0.000000000001
#define N 100

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

float SmallRandom();
int BigRandom();
//void nbody_init(int n, cl_float4* pos, cl_float4* vel);
//void nbody_output(int n, cl_float4* pos, cl_float4* vel);
void CalculateNewPositions(glm::vec3*, glm::vec3*, int*);


int main(void)
{
	srand(time(NULL));

	//int step, burst;

	//int nparticle = 10;
	//int nstep = 100;
	//int nburst = 20;
	//int nthread = 64;

	//float dt = 0.0001f;
	//float eps = 0.0001f;

	//size_t nparticleSize = nparticle * sizeof(cl_float4);

	//cl_float4* pos1 = (cl_float4*)malloc(nparticleSize);
	//cl_float4* pos2 = (cl_float4*)malloc(nparticleSize);
	//cl_float4* vel = (cl_float4*)malloc(nparticleSize);

	//for (int i = 0; i < nparticle; i++) {
	//	pos1[i].s[0] = 2.0f;
	//	pos1[i].s[1] = 2.0f;
	//	pos1[i].s[2] = 2.0f;
	//	pos1[i].s[3] = 2000.0f;

	//	vel[i].s[0] = 0.5f;
	//	vel[i].s[1] = -0.5f;
	//	vel[i].s[2] = 0.2f;
	//	vel[i].s[3] = 0.0f;;
	//}


	////OpenCL init functions
	//std::vector<cl::Platform> platforms;
	//cl::Platform::get(&platforms);

	//auto platform = platforms.front();
	//std::vector<cl::Device> devices;
	//platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);

	//auto device = devices.front();
	//std::ifstream kernelFile("resources/kernels/kernel.cl");
	//std::string src(std::istreambuf_iterator<char>(kernelFile), (std::istreambuf_iterator<char>()));

	//cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));

	//cl::Context context(device);
	//cl::Program program(context, sources);
	//auto err = program.build("-cl-std=CL1.2");


	//cl::Buffer devicePos1(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, nparticleSize, pos1);
	//cl::Buffer devicePos2(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, nparticleSize, pos2);
	//cl::Buffer deviceVel(context,  CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, nparticleSize, vel);

	////nbody_init(nparticle, pos1, vel); //implement


	//cl::Kernel kernel(program, "nbody_kern", &err);
	//kernel.setArg(0, dt);
	//kernel.setArg(1, eps);
	//kernel.setArg(4, vel); //upitno
	//kernel.setArg(5, vel); //upitno 

	//cl::NDRange localSize(nthread);
	//cl::NDRange globalSize(nparticle);
	////cl::NDRange globalSize((int)(ceil(N / (float)64) * 64));

	//cl::CommandQueue queue(context, device);

	//for (step = 0; step < nstep; step += nburst) {
	//	for (burst = 0; burst < nburst; burst += 2) {
	//		kernel.setArg(2, pos1);
	//		kernel.setArg(3, pos2);
	//		queue.enqueueNDRangeKernel(kernel, cl::NullRange, globalSize, localSize);

	//		kernel.setArg(2, pos2);
	//		kernel.setArg(3, pos1);
	//		queue.enqueueNDRangeKernel(kernel, cl::NullRange, globalSize, localSize);
	//	}
	//	queue.finish();

	//	queue.enqueueReadBuffer(devicePos1, GL_TRUE, 0, 10 * N * sizeof(float), pos1);
	//	for (int j = 0; j < sizeof(pos1); j++) {
	//		std::cout << pos1[j].s[0] << std::endl << pos1[j].s[1] << std::endl << pos1[j].s[3] << std::endl;
	//	}
	//}

	//nbody_output(nparticle, pos1, vel);

	//freee memory

	//queue.enqueueNDRangeKernel(kernel, cl::NullRange, globalSize, localSize);
	//queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(2, 3));
	//queue.enqueueReadBuffer(devicePos1, GL_TRUE, 0, 10 * N * sizeof(float), arr3);


	//for (int i = 0; i < N; i++) {
	//	std::cout << arr3[i].x << std::endl << arr3[i].y << std::endl << arr3[i].z << std::endl;
	//}




	//---------------------------------------------//
	//OpenGL//

	GLFWwindow* window;

	//Inicijalizacija//
	if (!glfwInit())
		return -1;

	// Kreiranje prozora i OpenGL konteksta //
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "N body physics", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Konfiguracija globalnog stanja OpenGLa
	glEnable(GL_DEPTH_TEST);




	// Vrhovi kocaka, staticki bez indeks buffera

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};


	//Pozicije za translacijske matrice
	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  2.0f),
	glm::vec3(-1.0f,  0.0f, 1.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};






	// Deklaracija buffer objekata i array objekata
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Povezivanje
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Kreiranje i kompajliranje shader programa
	Shader Shader("resources/shaders/VertexShader.shader", "resources/shaders/FragmentShader.shader");


	// Atribut pozicije
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Atribut teksture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	// TEKSTURE	// -------------------------
	unsigned int texture1, texture2;
	// Prva tekstura
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// Postavljanje parametara teksture (wrapping)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Postavljanje parametara teksture (filtriranje)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Ucitavanje slike, kreiranje tekstura i generiranje mipmapa
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // zastavica za stb_image.h da okrene teksturu oko y osi
	unsigned char *data = stbi_load("resources/textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// Tekstura 2
	//Sve je slicno kao i kod prethodne teksture, razlika kod alpha kanala
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// treba imati na umu da slika koja je koristena ima prozirnost tj. alpha kanal pa je zastavica GL_RBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// postavljanje OpenGL stanja sa trenutnim teksturama
	Shader.use();
	Shader.setInt("texture1", 0);
	Shader.setInt("texture2", 1);





	// Postavljanje brzina i masa na random vrijednosti
	int cubeMass[1000];
	glm::vec3 cubeVelocity[1000];
	for (int i = 0; i < 1000; i++)
	{
		cubeVelocity[i].x = SmallRandom();
		cubeVelocity[i].y = SmallRandom();
		cubeVelocity[i].z = SmallRandom();
	}

	for (int i = 0; i < 1000; i++)
	{
		cubeMass[i] = BigRandom();

	}



	// Glavna petlja prozora  //
	while (!glfwWindowShouldClose(window))
	{
		// Postavljanja i ciscenje color buffera
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Povezivanje tekstura na odgovarajuce teksturne jedinice
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// Aktivacija shadera
		Shader.use();

		
		// Kreiranje matrice svijeta i view i projekcijske matrice
		glm::mat4 world = glm::mat4(1.0f); 
		glm::mat4 view = glm::mat4(1.0f);  
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		// Dobivanje lokacija uniformnih matrica
		unsigned int worldLoc = glGetUniformLocation(Shader.ID, "world");
		unsigned int viewLoc = glGetUniformLocation(Shader.ID, "view");

		// Proslijedjivanje podataka shaderima
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		Shader.setMat4("projection", projection);

		// Prikazivanje
		glBindVertexArray(VAO);
		for (unsigned int i = 1; i < 1000; i++)
		{
			glm::mat4 world = glm::mat4(1.0f);
			world = glm::translate(world, cubePositions[1000 % i]);
			world = glm::scale(world, glm::vec3((float)cubeMass[i] / 200000, (float)cubeMass[i] / 200000, (float)cubeMass[i] / 200000));
			Shader.setMat4("world", world);

			// Draw call
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		//Racun novih pozicija objekata
		CalculateNewPositions(cubePositions, cubeVelocity, cubeMass);

		// Zamjena prednjeg i zadnjeg buffera
		glfwSwapBuffers(window);

		//Procesiranje dogadjaja
		glfwPollEvents();
	}


	// Dealokacija
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}

float SmallRandom() {
	int randomNum = 0.0f;
	float modifiedNum = 0.0f;
	randomNum = rand();

	if (randomNum % 2 == 0) {
		randomNum = randomNum % 1000;
		modifiedNum = 1 / (float)(randomNum + 20);
	}
	else {
		randomNum = randomNum % 1000;
		modifiedNum = -1 / (float)(randomNum + 20);
	}

	return modifiedNum;
}

int BigRandom() {
	int randomNum = 0.0f;
	randomNum = rand();

	randomNum = randomNum % 1000000;

	return randomNum;
}

void CalculateNewPositions(glm::vec3* cubePosition, glm::vec3* cubeVelocity, int* cubeMass) {

	float distanceBetweenObjects = 0.0f;
	glm::vec3 distanceVector;
	glm::vec3 normalizedDistanceVector;
	glm::vec3 velocity;
	glm::vec3 tempCubeVelocity[10];
	glm::vec3 tempCubePosition[10];
	float magnitude;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i != j) {
				distanceVector = cubePosition[i] - cubePosition[j];
				normalizedDistanceVector = glm::normalize(distanceVector);
				magnitude = glm::length(distanceVector);
				if (magnitude > 0.01)
				{
					//Calculate new velocity and then position
					tempCubeVelocity[i] = cubeVelocity[i] + (((float)-G * cubeMass[i] * cubeMass[j] / magnitude) * normalizedDistanceVector);
					tempCubePosition[i] = cubePosition[i] + tempCubeVelocity[i];
				}
				else {
					magnitude += 0.01;
					//Calculate new velocity and then position
					tempCubeVelocity[i] = cubeVelocity[i] + (((float)-G * cubeMass[i] * cubeMass[j] / magnitude) * normalizedDistanceVector);
					tempCubePosition[i] = cubePosition[i] + tempCubeVelocity[i];
				}
			}
		}
	}

	//Modificirati originalne vrijednosti;
	for (int i = 0; i < 10; i++)
	{
		cubeVelocity[i] = tempCubeVelocity[i]; 
		cubePosition[i] = tempCubePosition[i];
	}
}
