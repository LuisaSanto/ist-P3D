 ///////////////////////////////////////////////////////////////////////
//
// P3D Course
// (c) 2016 by João Madeiras Pereira
// TEMPLATE: Whitted Ray Tracing NFF scenes and drawing points with Modern OpenGL
//
//You should develop your rayTracing( Ray ray, int depth, float RefrIndex) which returns a color and
// to develop your load_NFF function
//
///////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <chrono>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Assets/Scene.h"
#include "Assets/Ray.h"
#include "Assets/Color.h"
#include "Assets/Camera.h"
#include "Assets/LensCamera.h"

//#include "scene.h"

#define CAPTION "ray tracer"

#define VERTEX_COORD_ATTRIB 0
#define COLOR_ATTRIB 1

#define MAX_DEPTH 3



//Jittering Sampling parameters
#define N 4 //Number of samples


#define samplesDOF 4			//Actually sqrt(numero de amostras dof) //Set to 1 if disabled
#define aperture (float) 0.1
#define fdRatio 1
#define M_PI (float) 3.1415926535
#define RAND (float)rand()/RAND_MAX
#define PIRAND (float)rand()/RAND_MAX*M_PI
#define ERAND (float)rand()/RAND_MAX





// Points defined by 2 attributes: positions which are stored in vertices array and colors which are stored in colors array
float *colors;
float *vertices;

int size_vertices;
int size_colors;

GLfloat m[16];  //projection matrix initialized by ortho function

GLuint VaoId;
GLuint VboId[2];

GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UniformId;

Scene scene;
int RES_X, RES_Y;

/* Draw Mode: 0 - point by point; 1 - line by line; 2 - full frame */
int draw_mode=2;

/* Camera Mode: 0 - prespective; 1 - DoP; */
int camera_mode = 0;

int WindowHandle = 0;

LensCamera* lensCamera;



//Soft shadows: 0 - off; 1 - softShadows with Jittering Method
int softShadows = 0;

//Anti- Alising:  0 - off ; 1 - antiAliasinng with Stochastic Sampling;  2 - antiAliasing with Jittering Method
int antiAliasing = 0;


//Acceleration grid: 0 - off; 1 - on;
int acceleration_grid = 0;


///////////////////////////////////////////////////////////////////////  RAY-TRACE SCENE

/*Color rayTracing( Ray ray, int depth, float RefrIndex)
{
    INSERT HERE YOUR CODE
}*/

/////////////////////////////////////////////////////////////////////// ERRORS

bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void checkOpenGLError(std::string error)
{
	if(isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}
/////////////////////////////////////////////////////////////////////// SHADERs
const GLchar* VertexShader =
{
	"#version 330 core\n"

	"in vec2 in_Position;\n"
	"in vec3 in_Color;\n"
	"uniform mat4 Matrix;\n"
	"out vec4 color;\n"

	"void main(void)\n"
	"{\n"
	"	vec4 position = vec4(in_Position, 0.0, 1.0);\n"
	"	color = vec4(in_Color, 1.0);\n"
	"	gl_Position = Matrix * position;\n"

	"}\n"
};

const GLchar* FragmentShader =
{
	"#version 330 core\n"

	"in vec4 color;\n"
	"out vec4 out_Color;\n"

	"void main(void)\n"
	"{\n"
	"	out_Color = color;\n"
	"}\n"
};

void createShaderProgram()
{
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, 0);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, 0);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);

	glBindAttribLocation(ProgramId, VERTEX_COORD_ATTRIB, "in_Position");
	glBindAttribLocation(ProgramId, COLOR_ATTRIB, "in_Color");
	
	glLinkProgram(ProgramId);
	UniformId = glGetUniformLocation(ProgramId, "Matrix");

	checkOpenGLError("ERROR: Could not create shaders.");
}

void destroyShaderProgram()
{
	glUseProgram(0);
	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);
	glDeleteProgram(ProgramId);

	checkOpenGLError("ERROR: Could not destroy shaders.");
}
/////////////////////////////////////////////////////////////////////// VAOs & VBOs
void createBufferObjects()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	glGenBuffers(2, VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);

	/* Não é necessário fazer glBufferData, ou seja o envio dos pontos para a placa gráfica pois isso 
	é feito na drawPoints em tempo de execução com GL_DYNAMIC_DRAW */

	glEnableVertexAttribArray(VERTEX_COORD_ATTRIB);
	glVertexAttribPointer(VERTEX_COORD_ATTRIB, 2, GL_FLOAT, 0, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
	glEnableVertexAttribArray(COLOR_ATTRIB);
	glVertexAttribPointer(COLOR_ATTRIB, 3, GL_FLOAT, 0, 0, 0);
	
// unbind the VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(VERTEX_COORD_ATTRIB);
	glDisableVertexAttribArray(COLOR_ATTRIB);
	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void destroyBufferObjects()
{
	glDisableVertexAttribArray(VERTEX_COORD_ATTRIB);
	glDisableVertexAttribArray(COLOR_ATTRIB);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, VboId);
	glDeleteVertexArrays(1, &VaoId);
	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}

void drawPoints()
{
	glBindVertexArray(VaoId);
	glUseProgram(ProgramId);

	glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
	glBufferData(GL_ARRAY_BUFFER, size_vertices, vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
	glBufferData(GL_ARRAY_BUFFER, size_colors, colors, GL_DYNAMIC_DRAW);

	glUniformMatrix4fv(UniformId, 1, GL_FALSE, m);
	glDrawArrays(GL_POINTS, 0, RES_X*RES_Y);
	glFinish();

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	checkOpenGLError("ERROR: Could not draw scene.");
}

/////////////////////////////////////////////////////////////////////// CALLBACKS

// Render function by primary ray casting from the eye towards the scene's objects


Color traceDOFRays(Color color, int x, int y) {
    Point focalp = scene.getLensCamera().getFocalPoint(x, y);
    for (int o = 0; o < samplesDOF; o++) {
         for (int q = 0; q < samplesDOF; q++) {
             Ray ray = scene.getLensCamera().computePrimaryRay(focalp);
             color = color + scene.trace(ray, 0, 1, false, softShadows, acceleration_grid);
         }
    }
    color = color * ((float)1 / (samplesDOF * samplesDOF));
    return color;
}

void renderScene() {
	int index_pos = 0;
	int index_col = 0;

	auto start = std::chrono::high_resolution_clock::now();

	float epsilon = ((float) rand() / (RAND_MAX));

	if (softShadows == 1) {
		for (Light *l : scene.getLights()) {
			l->addJitteredPoints(N);
		}
	}


	for (int y = 0; y < RES_Y; y++)
	{
		for (int x = 0; x < RES_X; x++)
		{
            Color color; //= Color(0.0f, 0.0f, 0.0f);
            if (antiAliasing == 0) {
				if (camera_mode == 1) {
					color = traceDOFRays(color, x, y);
				} else {
					Ray ray = scene.getCamera().computePrimaryRay(x, y);
					color = color + scene.trace(ray, 0, 1, false, softShadows, acceleration_grid);
				}
            }
            //Stochastic sampling
            else if (antiAliasing == 1) {
                int n_square = N * N;
                for (int p = 1; p < n_square; p++) {
                    float i = x + epsilon;
                    float j = y + epsilon;
                    if (camera_mode == 1) {
						color = traceDOFRays(color, i, j); //Sera i, j?
                    } else {
						Ray ray = scene.getCamera().computePrimaryRay(i, j);
						color = color + scene.trace(ray, 0, 1, false, softShadows, acceleration_grid);
					}
                }
                if (camera_mode != 1) {
                    color = color * (1.0f / n_square);
                }
            }
            //Jittering sampling
            else if (antiAliasing == 2) {
                int n_square = N * N;
                for (int p = 0; p < N; p++) {
                    for (int q = 0; q < N; q++) {
                        float i = x + (p + epsilon) / N;
                        float j = y + (q + epsilon) / N;
						if (camera_mode == 1) {
							color = traceDOFRays(color, i, j); //Sera i, j?
						} else {
							Ray ray = scene.getCamera().computePrimaryRay(i, j);
							color = color + scene.trace(ray, 0, 1, false, softShadows, acceleration_grid);
						}
                    }
                }
                if (camera_mode != 1) {
                    color = color * (1.0f / n_square);
                }
            }

			vertices[index_pos++]= (float)x;
			vertices[index_pos++]= (float)y;
			colors[index_col++]= color.r();
			colors[index_col++]= color.g();
			colors[index_col++]= color.b();

			if(draw_mode == 0) {  // desenhar o conteúdo da janela ponto a ponto
				drawPoints();
				index_pos=0;
				index_col=0;
			}
		}
		printf("line %d", y);
		if(draw_mode == 1) {  // desenhar o conteúdo da janela linha a linha
				drawPoints();
				index_pos=0;
				index_col=0;
		}
	}

	if(draw_mode == 2) //preenchar o conteúdo da janela com uma imagem completa
		 drawPoints();

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);



	printf("Terminou!\n");
	cout << "Time taken by function: " <<   duration.count() << " seconds" << endl;
}



void cleanup()
{
	destroyShaderProgram();
	destroyBufferObjects();
}

void ortho(float left, float right, float bottom, float top, 
			float nearp, float farp)
{
	m[0 * 4 + 0] = 2 / (right - left);
	m[0 * 4 + 1] = 0.0;
	m[0 * 4 + 2] = 0.0;
	m[0 * 4 + 3] = 0.0;
	m[1 * 4 + 0] = 0.0;
	m[1 * 4 + 1] = 2 / (top - bottom);
	m[1 * 4 + 2] = 0.0;
	m[1 * 4 + 3] = 0.0;
	m[2 * 4 + 0] = 0.0;
	m[2 * 4 + 1] = 0.0;
	m[2 * 4 + 2] = -2 / (farp - nearp);
	m[2 * 4 + 3] = 0.0;
	m[3 * 4 + 0] = -(right + left) / (right - left);
	m[3 * 4 + 1] = -(top + bottom) / (top - bottom);
	m[3 * 4 + 2] = -(farp + nearp) / (farp - nearp);
	m[3 * 4 + 3] = 1.0;
}

void reshape(int w, int h)
{
    glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, w, h);
	ortho(0, (float)RES_X, 0, (float)RES_Y, -1.0, 1.0);
}

/////////////////////////////////////////////////////////////////////// SETUP
void setupCallbacks() 
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);
}

void setupGLEW() {
	glewExperimental = GL_TRUE;
	GLenum result = glewInit() ; 
	if (result != GLEW_OK) { 
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	} 
	GLenum err_code = glGetError();
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
}

void setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	
	glutInitWindowPosition(640,100);
	glutInitWindowSize(RES_X, RES_Y);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glDisable(GL_DEPTH_TEST);
	WindowHandle = glutCreateWindow(CAPTION);
	if(WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	createShaderProgram();
	createBufferObjects();
	setupCallbacks();
}

int main(int argc, char* argv[])
{
    //INSERT HERE YOUR CODE FOR PARSING NFF FILES
	//Scene scene;
	scene.parse_nff(argv[1]);

	// If acceleration grid mode is on, create a grid
	if(acceleration_grid == 1){
		scene.createGrid();
	}

	Camera camera = scene.getCamera();
	if (camera_mode == 1) {
	    LensCamera lensCam = LensCamera(camera, fdRatio, aperture);
	    scene.addLensCamera(lensCam);
	}

	//scene.print();
	RES_X = camera.getResX();
	RES_Y = camera.getResY();
	
    //RES_Y = 512;
    //RES_X = 512;


	if(draw_mode == 0) { // desenhar o conteúdo da janela ponto a ponto
		size_vertices = 2*sizeof(float);
		size_colors = 3*sizeof(float);
		printf("DRAWING MODE: POINT BY POINT\n");
	}
	else if(draw_mode == 1) { // desenhar o conteúdo da janela linha a linha
		size_vertices = 2*RES_X*sizeof(float);
		size_colors = 3*RES_X*sizeof(float);
		printf("DRAWING MODE: LINE BY LINE\n");
	}
	else if(draw_mode == 2) { // preencher o conteúdo da janela com uma imagem completa
		size_vertices = 2*RES_X*RES_Y*sizeof(float);
		size_colors = 3*RES_X*RES_Y*sizeof(float);
		printf("DRAWING MODE: FULL IMAGE\n");
	}
	else {
		printf("Draw mode not valid \n");
		exit(0);
	}
	printf("resx = %d  resy= %d.\n", RES_X, RES_Y);

	vertices = (float*)malloc(size_vertices);
    if (vertices==NULL) exit (1);

	colors = (float*)malloc(size_colors);
    if (colors==NULL) exit (1);



	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
}
///////////////////////////////////////////////////////////////////////