/*---------------------------------------------------------*/
/* ----------------   Práctica 2 --------------------------*/
/*-----------------    2025-2   ---------------------------*/
/*------------- Lopez Flores Diego Alberto ---------------*/
#include <glew.h>
#include <glfw3.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

GLFWmonitor *monitors;
GLuint VBO[2], VAO[2], EBO[2];
GLuint shaderProgramYellow, shaderProgramColor;

static const char* myVertexShader = "										\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
																			\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);							\n\
}";

static const char* myVertexShaderColor = "									\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
layout (location = 1) in vec3 aColor;										\n\
out vec3 ourColor;															\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos, 1.0);											\n\
	ourColor = aColor;														\n\
}";

// Fragment Shader
static const char* myFragmentShaderYellow = "									\n\
#version 330																\n\
																			\n\
out vec3 finalColor;														\n\
																			\n\
void main()																	\n\
{																			\n\
    finalColor = vec3(1.0f, 1.0f, 0.0f);									\n\
}";

static const char* myFragmentShaderColor = "								\n\
#version 330 core															\n\
out vec4 FragColor;															\n\
in vec3 ourColor;															\n\
																			\n\
void main()																	\n\
{																			\n\
	FragColor = vec4(ourColor, 1.0f);										\n\
}";

void myData(void);
void setupShaders(void);
void display(void);
void getResolution(void);


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	float vertices[] = 
	{
		// positions					color RGB//
		//Babrilla
		-0.41291f,	0.67084f,	0.0f,	0.8f, 0.8f, 0.8f, //C	#0
		-0.36279f,	0.70685f,	0.0f,	0.8f, 0.8f, 0.8f, //D	#1
		-0.29224f,	0.64895f,	0.0f,	0.8f, 0.8f, 0.8f, //E	#2
		-0.26888f,	0.55844f,	0.0f,	0.8f, 0.8f, 0.8f, //F	#3
		-0.20417f,	0.64846f,	0.0f,	0.8f, 0.8f, 0.8f, //G	#4
		-0.29141f,	0.7757f,	0.0f,	0.8f, 0.8f, 0.8f, //H	#5
		-0.20249f,	0.84471f,	0.0f,	0.8f, 0.8f, 0.8f, //I	#6
		//Pecho
		-0.22472f,	0.44408f,	0.0f,	0.8f, 0.8f, 0.8f,//M	#7
		-0.42666f,	0.39313f,	0.0f,	0.8f, 0.8f, 0.8f,//N	#8
		-0.36552f,	0.45102f,	0.0f,	0.8f, 0.8f, 0.8f,//O	#9
		-0.36135f,	0.56774f,	0.0f,	0.8f, 0.8f, 0.8f,//P	#10
		-0.49763f,	0.155199f,	0.0f,	0.8f, 0.8f, 0.8f,//A_1	#11
		//oreja interna
		0.11596f,	0.3061f,	0.0f,	0.8f, 0.8f, 0.8f,//T	#12
		-0.0421f,	0.35741f,	0.0f,	0.8f, 0.8f, 0.8f,//S 	#13
		0.0f,		0.3f,		0.0f,	0.8f, 0.8f, 0.8f,//U 	#14
		-0.0103f,	0.25517f,	0.0f,	0.8f, 0.8f, 0.8f,//V 	#15
		-0.06823f,	0.30629f,	0.0f,	0.8f, 0.8f, 0.8f,//W 	#16
		//pansa
		-0.00132f,	-0.22054f,	0.0f,	0.8f, 0.8f, 0.8f,//F_1	#17
		-0.36225f,	-0.22114f,	0.0f,	0.8f, 0.8f, 0.8f,//G_1	#18
		-0.20641f,	-0.22114f,	0.0f,	0.8f, 0.8f, 0.8f,//H_1	#19
		-0.2f,		-0.4f,		0.0f,	0.8f, 0.8f, 0.8f,//J_1	#20
		-0.27959f,	-0.38782f,	0.0f,	0.8f, 0.8f, 0.8f,//K_1	#21
		-0.20506f,	-0.52468f,	0.0f,	0.8f, 0.8f, 0.8f,//L_1	#22
		//mano
		-0.38122f,	-0.75775f,	0.0f,	0.8f, 0.8f, 0.8f,//M_1	#23
		-0.4571f,	-0.78078f,	0.0f,	0.8f, 0.8f, 0.8f,//N_1	#24
		-0.49233f,	-0.84311f,	0.0f,	0.8f, 0.8f, 0.8f,//O_1	#25
		-0.34463f,	-0.84176f,	0.0f,	0.8f, 0.8f, 0.8f,//P_1	#26
		//pata
		-0.14544f,	-0.6114f,	0.0f,	0.8f, 0.8f, 0.8f,//Q_1	#27
		-0.06549f,	-0.76046f,	0.0f,	0.8f, 0.8f, 0.8f,//S_1	#28
		-0.15899f,	-0.76317f,	0.0f,	0.8f, 0.8f, 0.8f,//T_1	#29
		-0.2037f,	-0.84176f,	0.0f,	0.8f, 0.8f, 0.8f,//U_1	#30
		0.1905f,	-0.84355f,	0.0f,	0.8f, 0.8f, 0.8f,//V_1	#31
		//punta cola
		0.83786f,	-0.5516f,	0.0f,	0.8f, 0.8f, 0.8f,//D_2	#32
		0.76254f,	-0.35123f,	0.0f,	0.8f, 0.8f, 0.8f,//E_2	#33
		0.9146f,	-0.32991f,	0.0f,	0.8f, 0.8f, 0.8f,//F_2	#34
		0.77959f,	-0.21764f,	0.0f,	0.8f, 0.8f, 0.8f,//G_2	#35
		0.80375f,	-0.0798f,	0.0f,	0.8f, 0.8f, 0.8f,//H_2	#36
		//Parte Roja
		//Cabeza
		-0.13857f,	0.67195f,	0.0f,	0.8f, 0.0f, 0.0f,//J	#37 
		-0.06724f,	0.63397f,	0.0f,	0.8f, 0.0f, 0.0f,//K	#38
		-0.10985f,	0.55431f,	0.0f,	0.8f, 0.0f, 0.0f,//L	#39
		-0.00855f,	0.45199f,	0.0f,	0.8f, 0.0f, 0.0f,//Q	#40
		-0.20249f,	0.84471f,	0.0f,	0.8f, 0.0f, 0.0f,//I	#41
		-0.20417f,	0.64846f,	0.0f,	0.8f, 0.0f, 0.0f,//G	#42
		-0.26888f,	0.55844f,	0.0f,	0.8f, 0.0f, 0.0f,//F	#43
		-0.22472f,	0.44408f,	0.0f,	0.8f, 0.0f, 0.0f,//M	#44
		-0.06823f,	0.30629f,	0.0f,	0.8f, 0.0f, 0.0f,//W	#45
		-0.0421f,	0.35741f,	0.0f,	0.8f, 0.0f, 0.0f,//S	#46
		//oreja
		0.05791f,	0.40693f,	0.0f,	0.8f, 0.0f, 0.0f,//R	#47
		0.11596f,	0.3061f,	0.0f,	0.8f, 0.0f, 0.0f,//T	#48
		//cuerpo
		-0.49763f,	0.155199f,	0.0f,	0.8f, 0.0f, 0.0f,//A_1	#49
		-0.00132f,	-0.22054f,	0.0f,	0.8f, 0.0f, 0.0f,//F_1	#50
		0.0f,		0.0f,		0.0f,	0.8f, 0.0f, 0.0f,//E_1	#51
		-0.17161f,	0.05182f,	0.0f,	0.8f, 0.0f, 0.0f,//C_1	#52
		0.05218f,	0.15634f,	0.0f,	0.8f, 0.0f, 0.0f,//B_1	#53
		-0.06823f,	0.30629f,	0.0f,	0.8f, 0.0f, 0.0f,//W	#54
		-0.0103f,	0.25517f,	0.0f,	0.8f, 0.0f, 0.0f,//V	#55
		//lomo
		0.29849f,	-0.08113f,	0.0f,	0.8f, 0.0f, 0.0f,//D_1	#56
		-0.00132f,	-0.22054f,	0.0f,	0.8f, 0.0f, 0.0f,//F_1	#57
		0.05376f,	-0.5572f,	0.0f,	0.8f, 0.0f, 0.0f,//R_1	#58
		0.33667f,	-0.44434f,	0.0f,	0.8f, 0.0f, 0.0f,//Z_1	#59
		0.42498f,	-0.58516f,	0.0f,	0.8f, 0.0f, 0.0f,//W_1	#60
		0.468f,		-0.41177f,	0.0f,	0.8f, 0.0f, 0.0f,//A_2	#61
		//pansa
		-0.13866f,	-0.46912f,	0.0f,	0.8f, 0.0f, 0.0f,//I_1	#62
		-0.14544f,	-0.6114f,	0.0f,	0.8f, 0.0f, 0.0f,//Q_1	#63
		-0.20641f,	-0.22114f,	0.0f,	0.8f, 0.0f, 0.0f,//H_1	#64
		-0.2f,		-0.4f,		0.0f,	0.8f, 0.0f, 0.0f,//J_1	#65
		//pata
		-0.36225f,	-0.22114f,	0.0f,	0.8f, 0.0f, 0.0f,//G_1	#66
		-0.27959f,	-0.38782f,	0.0f,	0.8f, 0.0f, 0.0f,//K_1	#67
		-0.20506f,	-0.52468f,	0.0f,	0.8f, 0.0f, 0.0f,//L_1	#68
		-0.38122f,	-0.75775f,	0.0f,	0.8f, 0.0f, 0.0f,//M_1	#69
		-0.34463f,	-0.84176f,	0.0f,	0.8f, 0.0f, 0.0f,//P_1	#70
		//poto
		0.1905f,	-0.84355f,	0.0f,	0.8f, 0.0f, 0.0f,//V_1	#71
		0.51649f,	-0.61202f,	0.0f,	0.8f, 0.0f, 0.0f,//B_2	#72
		0.59784f,	-0.7137f,	0.0f,	0.8f, 0.0f, 0.0f,//C_2	#73
		//cola
		0.76254f,	-0.35123f,	0.0f,	0.8f, 0.0f, 0.0f,//E_2	#74
		0.83786f,	-0.5516f,	0.0f,	0.8f, 0.0f, 0.0f,//D_2	#75
	};

	unsigned int indices[] =
	{
		2,1,0,3,4,6,5, //E,D,C,F,G,I,H #7
		//7
		7,3,0,10,9,8,11,//M,F,C,P,O,N,A_1 #7
		//14
		14,12,13,16,15,//U,T,S,W,V #5
		//19
		19,17,11,18,21,22,20,//H_1,F_1,A_1,G_1,K_1,L_1,J_1 #7
		//26
		26,23,24,25,//P_1,M_1,N_1,O_1 #4
		//30
		28,27,31,30,29,//S_1,Q_1,V_1,U_1,T_1 #5
		//35
		34,36,35,33,32,//F_2,H_2,G_2,E_2,D_2 #5
		//40
		39,40,38,37,41,42,43,44,45,46,40,//L,Q,K,J,I,G,F,M,W,S,Q #11
		//51
		46,48,47,40,//S,T,R,Q #4
		//55
		49,50,51,52,53,55,54,44,//A_1,F_1,E_1,C_1,B_1,V,W,M #8  //11B, 49R
		//63
		56,53,52,51,57,58,59,60,61,//D_1,B_1,C_1,E_1,F_1,R_1,Z_1,W_1,A_2 #9
		//72
		62,63,58,57,64,65,//I_1,Q_1,R_1,F_1,H_1,J_1 #6
		//78
		69,70,68,67,66,//M_1,P_1,L_1,K_1,G_1 #5
		//83
		71,73,72,60,59,58,63,//V_1,C_2,B_2,W_1,Z_1,R_1,Q_1 #7
		//90
		72,73,75,74//B_2,C_2,D_2,E_2 #4
	};

	glGenVertexArrays(2, VAO);//se crea 2 arreglos de vertices llamado "VAO"
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);

	glBindVertexArray(VAO[0]);//se indica que contenedor se quiere usar, en este caso en el [0]
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);//la operaciones se realizan en el contenedor [0]
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//se llena el buffer, se determina el tamaño, y se indica que esos datos se ocupan para dibujo
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//entrada dentro del shader (0), que tome 3 valores (x,y,z), tipo flotante, false para normalizar (valores entre 0 y 1),el void 0 para el primer valor del atributo 
	glEnableVertexAttribArray(0);//					se cambia a 6 * sizeof(float) para indicar cada cuanto va a leer la posicion 0 de la cordenada
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//entrada 1,pasar 3 valores (rgb), tipo flotante, no normalizados, la ubicacion 3 del arreglo se toma el atributo de color
	glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void setupShaders()
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &myVertexShader, NULL);
	glCompileShader(vertexShader);

	unsigned int vertexShaderColor = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderColor, 1, &myVertexShaderColor, NULL);
	glCompileShader(vertexShaderColor);

	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &myFragmentShaderYellow, NULL);
	glCompileShader(fragmentShaderYellow);

	unsigned int fragmentShaderColor = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderColor, 1, &myFragmentShaderColor, NULL);
	glCompileShader(fragmentShaderColor);


	//Crear el Programa que combina Geometría con Color
	shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	shaderProgramColor = glCreateProgram();
	glAttachShader(shaderProgramColor, vertexShaderColor);
	glAttachShader(shaderProgramColor, fragmentShaderColor);
	glLinkProgram(shaderProgramColor);
	//Check for errors 

	//ya con el Programa, el Shader no es necesario
	glDeleteShader(vertexShader);
	glDeleteShader(vertexShaderColor);
	glDeleteShader(fragmentShaderYellow);
	glDeleteShader(fragmentShaderColor);

}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 1 2025", NULL, NULL); //Bug?
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//My Functions
	//Setup Data to use
	myData();
	//To Setup Shaders
	setupShaders();
    
    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

        // render
        // Background color
        glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		//Display Section
		//glUseProgram(shaderProgramYellow);//shader basico con color amarillo
		glUseProgram(shaderProgramColor);

		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);

		glPointSize(10.0);
		//glDrawElements(GL_POINTS, 5, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_POINTS, 0, 52);
		//Parte Blanca
		glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT, (void*)(7 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(14 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT, (void*)(19 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(26 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(30 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(35 * sizeof(float)));
		//Parte roja
		glDrawElements(GL_TRIANGLE_FAN, 11, GL_UNSIGNED_INT, (void*)(40 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(51 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, (void*)(55 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 9, GL_UNSIGNED_INT, (void*)(63 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(72 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(78 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT, (void*)(83 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(90 * sizeof(float)));

		glBindVertexArray(0);
		glUseProgram(0);

		//End of Display Section

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);  //Close
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}