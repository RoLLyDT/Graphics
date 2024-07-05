#define _USE_MATH_DEFINES 
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>

#include "ModelViewerCamera.h"
#include "camera.h"
#include "shader.h"
#include "window.h"
#include "texture.h"

#define DEG2RAD(deg) (deg * M_PI / 180.0)


unsigned int VAO_circle, VBO_circle;
unsigned int VAO_cylinder, VBO_cylinder;
unsigned int VAO_platform, VBO_platform;
unsigned int VAO_control, VBO_control;
unsigned int VAO_door, VBO_door;
unsigned int VAO_trolley, VBO_trolley;
unsigned int VAO_beam, VBO_beam;


float modelZPosition = 0.0f;
const float maxZPosition = 0.5f;  // Maximum Z position
const float minZPosition = -3.0f; // Minimum Z position
const float movementSpeed = 0.005f; // Adjust the movement speed as needed

glm::vec3 cube_pos = glm::vec3(0.0f, 0.0f, 0.0f);

//Being Used
float platform[] ={
	//pos					//col
	// right side
	// ABC 		
	-1.0f, -1.0f, -1.0f,  	0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	1.0f, -1.0f, -1.0f,  	1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	1.0f,  1.0f, -1.0f,  	1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	1.0f,  1.0f, -1.0f,  	1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	-1.0f,  1.0f, -1.0f,  	0.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	-1.0f, -1.0f, -1.0f,  	0.0f, 0.0f,	1.0f,  0.0f,  0.0f,

	// LEFT SIDE
	//EGH
	-1.0f, -1.0f,  1.0f,  	0.0f, 0.0f,    -1.0f,  0.0f,  0.0f,
	1.0f, -1.0f,  1.0f,  	1.0f, 0.0f,	   -1.0f,  0.0f,  0.0f,
	1.0f,  1.0f,  1.0f,  	1.0f, 1.0f,	   -1.0f,  0.0f,  0.0f,
	1.0f,  1.0f,  1.0f,  	1.0f, 1.0f,	   -1.0f,  0.0f,  0.0f,
	-1.0f,  1.0f,  1.0f,  	0.0f, 1.0f,	   -1.0f,  0.0f,  0.0f,
	-1.0f, -1.0f,  1.0f,  	0.0f, 0.0f,	   -1.0f,  0.0f,  0.0f,

	// back side
	//FDE
	-1.0f,  1.0f,  1.0f,  	1.0f, 0.0f,    0.0f,  0.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,  	1.0f, 1.0f,	   0.0f,  0.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,  	0.0f, 1.0f,	   0.0f,  0.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,  	0.0f, 1.0f,	   0.0f,  0.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,  	0.0f, 0.0f,	   0.0f,  0.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,  	1.0f, 0.0f,	   0.0f,  0.0f, -1.0f,

	// front side
	//HCB
	1.0f,  1.0f,  1.0f,  	1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
	1.0f,  1.0f, -1.0f,  	1.0f, 1.0f,	 0.0f,  0.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 	0.0f, 1.0f,	 0.0f,  0.0f, 1.0f,
	1.0f, -1.0f, -1.0f,  	0.0f, 1.0f,	 0.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f,  	0.0f, 0.0f,	 0.0f,  0.0f, 1.0f,
	1.0f,  1.0f,  1.0f,  	1.0f, 0.0f,	 0.0f,  0.0f, 1.0f,

	//BOTTOM
	//ABG
	-1.0f, -1.0f, -1.0f,  	0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
	1.0f, -1.0f, -1.0f,  	1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
	1.0f, -1.0f,  1.0f,  	1.0f, 0.0f,	 0.0f,  1.0f,  0.0f,
	1.0f, -1.0f,  1.0f,  	1.0f, 0.0f,	 0.0f,  1.0f,  0.0f,
	-1.0f, -1.0f,  1.0f,  	0.0f, 0.0f,	 0.0f,  1.0f,  0.0f,
	-1.0f, -1.0f, -1.0f,  	0.0f, 1.0f,	 0.0f,  1.0f,  0.0f,
};
float control[] = {
	// pos                   // col
   -0.5f, -0.5f, -0.75f,    0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.75f,    1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.75f,    1.0f, 0.0f,	1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.75f,    1.0f, 0.0f,	1.0f,  0.0f,  0.0f,
   -0.5f,  0.5f, -0.75f,    0.0f, 0.0f,	1.0f,  0.0f,  0.0f,
   -0.5f, -0.5f, -0.75f,    0.0f, 1.0f,	1.0f,  0.0f,  0.0f,

   -0.5f, -0.5f,  0.75f,    0.0f, 1.0f, -1.0f,  0.0f,  0.0f,//left side
	0.5f, -0.5f,  0.75f,    1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.75f,    1.0f, 0.0f,	-1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.75f,    1.0f, 0.0f,	-1.0f,  0.0f,  0.0f,
   -0.5f,  0.5f,  0.75f,    0.0f, 0.0f,	-1.0f,  0.0f,  0.0f,
   -0.5f, -0.5f,  0.75f,    0.0f, 1.0f,	-1.0f,  0.0f,  0.0f,

   -0.5f,  0.5f,  0.75f,	0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
   -0.5f,  0.5f, -0.75f,	1.0f, 0.0f,	0.0f,  0.0f, -1.0f,
   -0.5f, -0.5f, -0.75f,	1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
   -0.5f, -0.5f, -0.75f,	1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
   -0.5f, -0.5f,  0.75f,	0.0f, 1.0f,	0.0f,  0.0f, -1.0f,
   -0.5f,  0.5f,  0.75f,	0.0f, 0.0f,	0.0f,  0.0f, -1.0f,

	0.5f,  0.5f,  0.75f,    0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.75f,    1.0f, 0.0f,	0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.75f,    1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.75f,    1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.75f,    0.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.75f,    0.0f, 0.0f,	0.0f,  0.0f, 1.0f,

   -0.5f, -0.5f, -0.75f,    0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.75f,    1.0f, 1.0f,	0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.75f,    1.0f, 0.0f,	0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.75f,    1.0f, 0.0f,	0.0f, -1.0f,  0.0f,
   -0.5f, -0.5f,  0.75f,    0.0f, 0.0f,	0.0f, -1.0f,  0.0f,
   -0.5f, -0.5f, -0.75f,    0.0f, 1.0f,	0.0f, -1.0f,  0.0f,

   -0.5f,  0.5f, -0.75f,    0.0f, 1.0f, 0.0f,  1.0f,  0.0f,//top side
	0.5f,  0.5f, -0.75f,    1.0f, 1.0f,	0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.75f,    1.0f, 0.0f,	0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.75f,    1.0f, 0.0f,	0.0f,  1.0f,  0.0f,
   -0.5f,  0.5f,  0.75f,    0.0f, 0.0f,	0.0f,  1.0f,  0.0f,
   -0.5f,  0.5f, -0.75f,    0.0f, 1.0f,	0.0f,  1.0f,  0.0f,
};
float door[] = {
	// ABCD=ABC+ACD
	-3.15f, -0.4f, -0.75f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-3.15f, -0.4f, -0.85f,  1.0f, 1.0f,	0.0f, -1.0f,  0.0f,
	0.15f, -0.4f, -0.85f,   0.0f, 1.0f,	0.0f, -1.0f,  0.0f,
	-3.15f, -0.4f, -0.75f,  1.0f, 0.0f,	0.0f, -1.0f,  0.0f,
	0.15f, -0.4f, -0.75f,   0.0f, 0.0f,	0.0f, -1.0f,  0.0f,
	0.15f, -0.4f, -0.85f,   0.0f, 1.0f,	0.0f, -1.0f,  0.0f,

	// ABWQ = ABW+AWQ
	-3.15f, -0.4f, -0.75f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	-3.15f, -0.4f, -0.85f,  1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-3.15f, 4.4f, -0.85f,   0.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-3.15f, -0.4f, -0.75f,  1.0f, 0.0f,	0.0f,  0.0f, -1.0f,
	-3.15f, 4.4f, -0.75f,   0.0f, 0.0f,	0.0f,  0.0f, -1.0f,
	-3.15f, 4.4f, -0.85f,   0.0f, 1.0f,	0.0f,  0.0f, -1.0f,

	// bcew = bce + bew
	-3.15f, -0.4f, -0.85f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	0.15f, -0.4f, -0.85f,   0.0f, 0.0f,	1.0f,  0.0f,  0.0f,
	0.15f, 4.4f, -0.85f,    0.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	-3.15f, -0.4f, -0.85f,  1.0f, 0.0f,	1.0f,  0.0f,  0.0f,
	-3.15f, 4.4f, -0.85f,   1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	0.15f, 4.4f, -0.85f,    0.0f, 1.0f,	1.0f,  0.0f,  0.0f,

	// cdze = cdz+cze
	0.15f, -0.4f, -0.75f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	0.15f, -0.4f, -0.85f,   1.0f, 0.0f,	0.0f,  0.0f, 1.0f,
	0.15f, 4.4f, -0.85f,    0.0f, 0.0f,	0.0f,  0.0f, 1.0f,
	0.15f, -0.4f, -0.75f,   1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	0.15f, 4.4f, -0.75f,    0.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	0.15f, 4.4f, -0.85f,    0.0f, 0.0f,	0.0f,  0.0f, 1.0f,

	// daqz = daq + dqz
	-3.15f, 4.4f, -0.75f,   1.0f, 0.0f, 0.0f,  1.0f,  0.0f,//top side
	-3.15f, 4.4f, -0.85f,   1.0f, 1.0f,	0.0f,  1.0f,  0.0f,
	0.15f, 4.4f, -0.85f,    0.0f, 1.0f,	0.0f,  1.0f,  0.0f,
	-3.15f, 4.4f, -0.75f,   1.0f, 0.0f,	0.0f,  1.0f,  0.0f,
	0.15f, 4.4f, -0.75f,    0.0f, 0.0f,	0.0f,  1.0f,  0.0f,
	0.15f, 4.4f, -0.85f,    0.0f, 1.0f,	0.0f,  1.0f,  0.0f,
};
float trolley[] = {
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,		1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 0.0f,	1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 0.0f,	1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 0.0f,	1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,	1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,	0.0f, 1.0f, -1.0f,  0.0f,  0.0f,//left side
	0.5f, -0.5f,  0.5f,		1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,	-1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 1.0f,	-1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 0.0f,	0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,	0.0f,  0.0f, -1.0f,

	0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,		1.0f, 0.0f,	0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,		0.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		0.0f, 0.0f,	0.0f,  0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,		1.0f, 1.0f,	0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,	0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,		1.0f, 0.0f,	0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,	0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,	0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,  1.0f,  0.0f,//top
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,	0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,	0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,		1.0f, 0.0f,	0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,	0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,	0.0f,  1.0f,  0.0f,
};
float beam[] = {
	/* A 000-  B 100 - C 210 - D 220 - E 320 - F 310 - G 400 - H 500 */
	/* ABC  -  ADC  -  DCF  -  DEF  -  EFG  - EHG */
	0.f, 0.f, 0.f,	 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,// A  normal 001
	1.f, 0.f, 0.f,	 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,// B
	2.f, 1.f, 0.f,	 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,// C
	0.f, 0.f, 0.f,	 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,// A
	2.f, 2.f, 0.f,	 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,// D
	2.f, 1.f, 0.f,	 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,// C

	2.f, 2.f, 0.f,	 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,// D normal 001
	2.f, 1.f, 0.f,	 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,// C
	3.f, 1.f, 0.f,	 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,// F
	2.f, 2.f, 0.f,	 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,// D
	3.f, 2.f, 0.f,	 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,// E
	3.f, 1.f, 0.f,	 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,// F

	3.f, 2.f, 0.f,	 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,// E normal 001
	3.f, 1.f, 0.f,	 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,// F
	4.f, 0.f, 0.f,	 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,// G
	3.f, 2.f, 0.f,	 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,// E
	5.f, 0.f, 0.f,	 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,// H
	4.f, 0.f, 0.f,	 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,// G

	0.f, 0.f, 1.f,	 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,// A1 normal 00-1
	1.f, 0.f, 1.f,	 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,// B1
	2.f, 1.f, 1.f,	 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,// C1
	0.f, 0.f, 1.f,	 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,// A1
	2.f, 2.f, 1.f,	 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,// D1
	2.f, 1.f, 1.f,	 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,// C1

	2.f, 2.f, 1.f,	 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,// D1 normal 00-1
	2.f, 1.f, 1.f,	 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,// C1
	3.f, 1.f, 1.f,	 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,// F1
	2.f, 2.f, 1.f,	 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,// D1
	3.f, 2.f, 1.f,	 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,// E1
	3.f, 1.f, 1.f,	 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,// F1

	3.f, 2.f, 1.f,	 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,// E1 normal 00-1
	3.f, 1.f, 1.f,	 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,// F1
	4.f, 0.f, 1.f,	 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,// G1
	3.f, 2.f, 1.f,	 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,// E1
	5.f, 0.f, 1.f,	 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,// H1
	4.f, 0.f, 1.f,	 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,// G1

	0.f, 0.f, 0.f,	 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,// A normal 0-10
	0.f, 0.f, 1.f,	 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,// A1
	1.f, 0.f, 0.f,	 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,// B
	1.f, 0.f, 1.f,	 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,// B1
	0.f, 0.f, 1.f,	 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,// A1
	1.f, 0.f, 0.f,	 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,// B

	4.f, 0.f, 0.f,	 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,// G normal 0-10
	4.f, 0.f, 1.f,	 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,// G1
	5.f, 0.f, 0.f,	 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,// H
	5.f, 0.f, 1.f,	 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,// H1
	4.f, 0.f, 1.f,	 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,// G1
	5.f, 0.f, 0.f,	 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,// H

	0.f, 0.f, 0.f,	 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,// A normal -100
	2.f, 2.f, 0.f,	 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,// D
	0.f, 0.f, 1.f,	 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,// A1
	2.f, 2.f, 1.f,	 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,// D1
	2.f, 2.f, 0.f,	 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,// D
	0.f, 0.f, 1.f,	 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,// A1

	2.f, 2.f, 0.f,	 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,// D normal 010
	2.f, 2.f, 1.f,	 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,// D1
	3.f, 2.f, 0.f,	 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,// E
	3.f, 2.f, 1.f,	 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,// E1
	2.f, 2.f, 1.f,	 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,// D1
	3.f, 2.f, 0.f,	 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,// E

	3.f, 2.f, 0.f,	 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,// E normal 100
	3.f, 2.f, 1.f,	 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,// E1
	5.f, 0.f, 0.f,	 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,// H
	5.f, 0.f, 1.f,	 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,// H1
	3.f, 2.f, 1.f,	 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,// E1
	5.f, 0.f, 0.f,	 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,// H

	1.f, 0.f, 0.f,	 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,// B normal 100
	1.f, 0.f, 1.f,	 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,// B1
	2.f, 1.f, 0.f,	 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,// C
	2.f, 1.f, 1.f,	 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,// C1
	1.f, 0.f, 1.f,	 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,// B1
	2.f, 1.f, 0.f,	 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,// C

	2.f, 1.f, 0.f,	 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,// C normal 0-10
	2.f, 1.f, 1.f,	 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,// C1
	3.f, 1.f, 0.f,	 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,// F
	3.f, 1.f, 1.f,	 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,// F1 
	2.f, 1.f, 1.f,	 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,// C1
	3.f, 1.f, 0.f,	 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,// F

	4.f, 0.f, 0.f,	 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,// G normal -100
	4.f, 0.f, 1.f,	 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,// G1
	3.f, 1.f, 0.f,	 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,// F
	3.f, 1.f, 1.f,	 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,// F1 
	4.f, 0.f, 1.f,	 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,// G1
	3.f, 1.f, 0.f,	 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,// F
};





glm::vec3 lightDirection = glm::vec3(0.1f, -.81f, -.61f);
glm::vec3 lightPos = glm::vec3(2.f, 6.f, 7.f);
SCamera Camera;

void setupShape(unsigned int& VAO, unsigned int& VBO, float* vertices, int size)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

float* CreateCircle(int num_segments, float radius)
{
	int n_verts = num_segments * 3;
	int n_atts = n_verts * 3;
	float* verts = (float*)malloc(sizeof(float) * (n_atts));

	float angle_offset = DEG2RAD(360.f) / num_segments;
	float current_angle = 0.f;

	for (int sc = 0; sc < num_segments; sc++)
	{
		verts[sc * 3 * 3] = 0.f;
		verts[sc * 3 * 3 + 1] = 0.f;
		verts[sc * 3 * 3 + 2] = 0.f;

		verts[sc * 3 * 3 + 3] = sin(current_angle) * radius;
		verts[sc * 3 * 3 + 4] = cos(current_angle) * radius;
		verts[sc * 3 * 3 + 5] = 0.f;

		verts[sc * 3 * 3 + 6] = sin(current_angle + angle_offset) * radius;
		verts[sc * 3 * 3 + 7] = cos(current_angle + angle_offset) * radius;
		verts[sc * 3 * 3 + 8] = 0.f;

		current_angle += angle_offset;
	}

	return verts;
}

float* CreateCylinder(int num_segments, float radius, float height)
{
	int n_verts = num_segments * 3 * 6; // 2 circles * 3 vertices * num_segments + side triangles
	int n_atts = n_verts * 3;
	float* verts = (float*)malloc(sizeof(float) * n_atts);

	float angle_offset = 2.0f * M_PI / num_segments;
	float current_angle = 0.f;

	// Create upper circle
	for (int sc = 0; sc < num_segments; sc++)
	{
		verts[sc * 3 * 3] = 0.f;
		verts[sc * 3 * 3 + 1] = height / 2.0f;
		verts[sc * 3 * 3 + 2] = 0.f;

		verts[sc * 3 * 3 + 3] = sin(current_angle) * radius;
		verts[sc * 3 * 3 + 4] = height / 2.0f;
		verts[sc * 3 * 3 + 5] = cos(current_angle) * radius;

		verts[sc * 3 * 3 + 6] = sin(current_angle + angle_offset) * radius;
		verts[sc * 3 * 3 + 7] = height / 2.0f;
		verts[sc * 3 * 3 + 8] = cos(current_angle + angle_offset) * radius;

		current_angle += angle_offset;
	}

	// Create lower circle
	for (int sc = 0; sc < num_segments; sc++)
	{
		verts[(num_segments + sc) * 3 * 3] = 0.f;
		verts[(num_segments + sc) * 3 * 3 + 1] = -height / 2.0f;
		verts[(num_segments + sc) * 3 * 3 + 2] = 0.f;

		verts[(num_segments + sc) * 3 * 3 + 3] = sin(current_angle) * radius;
		verts[(num_segments + sc) * 3 * 3 + 4] = -height / 2.0f;
		verts[(num_segments + sc) * 3 * 3 + 5] = cos(current_angle) * radius;

		verts[(num_segments + sc) * 3 * 3 + 6] = sin(current_angle + angle_offset) * radius;
		verts[(num_segments + sc) * 3 * 3 + 7] = -height / 2.0f;
		verts[(num_segments + sc) * 3 * 3 + 8] = cos(current_angle + angle_offset) * radius;

		current_angle += angle_offset;
	}

	// Create side triangles
	for (int sc = 0; sc < num_segments; sc++)
	{
		// Triangle 1
		verts[(2 * num_segments + sc) * 3 * 3] = sin(current_angle) * radius;
		verts[(2 * num_segments + sc) * 3 * 3 + 1] = height / 2.0f;
		verts[(2 * num_segments + sc) * 3 * 3 + 2] = cos(current_angle) * radius;

		verts[(2 * num_segments + sc) * 3 * 3 + 3] = sin(current_angle) * radius;
		verts[(2 * num_segments + sc) * 3 * 3 + 4] = -height / 2.0f;
		verts[(2 * num_segments + sc) * 3 * 3 + 5] = cos(current_angle) * radius;

		verts[(2 * num_segments + sc) * 3 * 3 + 6] = sin(current_angle + angle_offset) * radius;
		verts[(2 * num_segments + sc) * 3 * 3 + 7] = height / 2.0f;
		verts[(2 * num_segments + sc) * 3 * 3 + 8] = cos(current_angle + angle_offset) * radius;

		// Triangle 2
		verts[(3 * num_segments + sc) * 3 * 3] = sin(current_angle + angle_offset) * radius;
		verts[(3 * num_segments + sc) * 3 * 3 + 1] = height / 2.0f;
		verts[(3 * num_segments + sc) * 3 * 3 + 2] = cos(current_angle + angle_offset) * radius;

		verts[(3 * num_segments + sc) * 3 * 3 + 3] = sin(current_angle) * radius;
		verts[(3 * num_segments + sc) * 3 * 3 + 4] = -height / 2.0f;
		verts[(3 * num_segments + sc) * 3 * 3 + 5] = cos(current_angle) * radius;

		verts[(3 * num_segments + sc) * 3 * 3 + 6] = sin(current_angle + angle_offset) * radius;
		verts[(3 * num_segments + sc) * 3 * 3 + 7] = -height / 2.0f;
		verts[(3 * num_segments + sc) * 3 * 3 + 8] = cos(current_angle + angle_offset) * radius;

		current_angle += angle_offset;
	}

	return verts;
}




void processKeyboard(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		lightDirection = Camera.Front;
		lightPos = Camera.Position;
	}

	bool cam_changed = false;
	float x = 0.f, y = 0.f;

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		x = 1.f;
		y = 0.f;
		cam_changed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		x = -1.f;
		y = 0.f;
		cam_changed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		x = 0.f;
		y = 1.f;
		cam_changed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		x = 0.f;
		y = -1.f;
		cam_changed = true;
	}


	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		cam_dist += 0.01;
		cam_changed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		cam_dist -= 0.01;
		cam_changed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		modelZPosition -= movementSpeed;
		modelZPosition = max(modelZPosition, minZPosition);
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		modelZPosition += movementSpeed;
		modelZPosition = min(modelZPosition, maxZPosition);
	}

	if (cam_changed)
	{
		MoveAndOrientCamera(Camera, cube_pos, cam_dist, x, y);
	}

}

unsigned int loadShaderSource()
{

	return 0;
}

int main(int argc, char** argv)
{
	GLFWwindow* window = CreateGLFWWindow(1200, 800, "20219332");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	unsigned int shaderProgram = LoadShader("mvp.vert", "col.frag");

	InitCamera(Camera, -90, 15);
	MoveAndOrientCamera(Camera, cube_pos, cam_dist, 0.f, 0.f);

	GLuint texture_door = setup_texture("textures/door.bmp");
	GLuint texture_platform = setup_texture("textures/plat.bmp");
	GLuint texture_control = setup_texture("textures/rail.bmp");
	GLuint texture_trolley = setup_texture("textures/trolley.bmp");
	GLuint texture_wheel = setup_texture("textures/wheel.bmp");
	GLuint texture_rail = setup_texture("textures/rail.bmp");
	GLuint texture_beams = setup_texture("textures/bny.bmp");
	

	setupShape(VAO_platform, VBO_platform, platform, sizeof(platform));
	setupShape(VAO_control, VBO_control, control, sizeof(control));
	setupShape(VAO_door, VBO_door, door, sizeof(door));
	setupShape(VAO_trolley, VBO_trolley, trolley, sizeof(trolley));
	setupShape(VAO_beam, VBO_beam, beam, sizeof(beam));


	int num_segs = 32;
	float* verticesC = CreateCircle(num_segs, 1.f);
	float* vertices = CreateCylinder(num_segs, 1.f, 1.f);
	
	

	glGenVertexArrays(1, &VAO_cylinder);
	glGenBuffers(1, &VBO_cylinder);
	glBindVertexArray(VAO_cylinder);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_cylinder);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_segs * 3 * 3 * 6, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glGenVertexArrays(1, &VAO_circle);
	glGenBuffers(1, &VBO_circle);
	glBindVertexArray(VAO_circle);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_circle);
	//COPY VERTICES HERE
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_segs * 3 * 3, verticesC, GL_STATIC_DRAW);
	//SETUP ATTRIBUTES HERE
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);


	float rotationSpeed = 1.0f;

	while (!glfwWindowShouldClose(window))
	{

		processKeyboard(window);

		glClearColor(0.89f, 0.988f, 0.525f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUniform3f(glGetUniformLocation(shaderProgram, "lightDirection"), lightDirection.x, lightDirection.y, lightDirection.z);
		glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(shaderProgram, "lightColour"), 1.f, 1.f, 1.f);
		glUniform3f(glGetUniformLocation(shaderProgram, "camPos"), Camera.Position.x, Camera.Position.y, Camera.Position.z);



		glm::mat4 view = glm::mat4(1.f);
		view = glm::lookAt(Camera.Position, Camera.Position + Camera.Front, Camera.Up);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection = glm::mat4(1.f);
		projection = glm::perspective(glm::radians(45.f), (float)800 / (float)600, 1.f, 150.f);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		/* Platform */
		glBindTexture(GL_TEXTURE_2D, texture_platform);
		glUseProgram(shaderProgram);
		glm::mat4 model = glm::mat4(1.f);
				  model = glm::translate(model, glm::vec3(0.f, -0.65f, 0.f));
				  model = glm::scale(model, glm::vec3(40.f, 0.f, 40.f));
		int mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_platform);
		glDrawArrays(GL_TRIANGLES, 0, 30);
		glBindVertexArray(0);
		/* Platform */


		/* Control Box */
		glBindTexture(GL_TEXTURE_2D, texture_control);
		glUseProgram(shaderProgram);
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(4.f, 2.4f, 1.0f));
		model =	glm::scale(model, glm::vec3(4.5f, 6.f, 1.f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		/* Control Box */

		/* Door of the Box */
		float rotationAngle = glm::radians(45.0f) * glm::sin(rotationSpeed * (float)glfwGetTime());

		// Ensure rotation angle stays within the desired range (0 to 45 degrees)
		if (rotationAngle < 0.0f) {
			rotationAngle = 0.0f;
		}
		else if (rotationAngle > glm::radians(45.0f)) {
			rotationAngle = glm::radians(45.0f);
		}

		glBindTexture(GL_TEXTURE_2D, texture_door);
		glUseProgram(shaderProgram);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(5.85f, 0.f, 1.0f));
		model = glm::scale(model, glm::vec3(1.25f, 1.2f, 1.f));
		model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, -0.1f, 0.0f));
		mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_door);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		/* Door of the Box */


		/* Trolley */
		glBindTexture(GL_TEXTURE_2D, texture_trolley);
		glUseProgram(shaderProgram);

		/* Main */
		for (float i = 0; i <= 3.f; i += 3.f)
		{
			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(-1.f, i, -3.f + modelZPosition));
			model = glm::scale(model, glm::vec3(0.25f, 0.25f, 4.f));
			glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO_control);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(-3.f, i, -3.f + modelZPosition));
			model = glm::scale(model, glm::vec3(0.25f, 0.25f, 4.f));
			glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO_control);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(-2.f, i, 0.f + modelZPosition));
			model = glm::scale(model, glm::vec3(2.5f, 0.25f, 0.25f));
			glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO_control);
			glDrawArrays(GL_TRIANGLES, 0, 36); //Further from the camera

			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(-2.f, i, -6.f + modelZPosition));
			model = glm::scale(model, glm::vec3(2.5f, 0.25f, 0.25f));
			glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO_control);
			glDrawArrays(GL_TRIANGLES, 0, 36); //Closer to the camera
		}

		/* beams */
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-2.f, 1.8f, 0.f + modelZPosition));
		model = glm::scale(model, glm::vec3(2.f, 0.15f, 0.2f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36); //Further from the camera

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-2.f, 1.8f, -6.f + modelZPosition));
		model = glm::scale(model, glm::vec3(2.f, 0.15f, 0.2f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36); //Closer to the camera

		/* beams up */
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-1.f, 1.5f, 0.f + modelZPosition));
		model = glm::scale(model, glm::vec3(0.25f, 3.f, 0.25f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-3.f, 1.5f, 0.f + modelZPosition));
		model = glm::scale(model, glm::vec3(0.25f, 3.f, 0.25f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-1.f, 1.5f, -6.f + modelZPosition));
		model = glm::scale(model, glm::vec3(0.25f, 3.f, 0.25f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-3.f, 1.5f, -6.f + modelZPosition));
		model = glm::scale(model, glm::vec3(0.25f, 3.f, 0.25f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/* platform of trolley top */
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-2.f, 3.f, -3.f + modelZPosition));
		model = glm::scale(model, glm::vec3(2.f, 0.25f, 4.f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-2.f, 3.25f, -3.f + modelZPosition));
		model = glm::scale(model, glm::vec3(2.5f, 0.25f, 4.f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-1.f, 3.5f, -2.85f + modelZPosition));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 4.f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36); //upper platfrom

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-3.f, 3.5f, -2.85f + modelZPosition));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 4.f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36); //upper platfrom

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-2.f, 3.5f, -6.f + modelZPosition));
		model = glm::scale(model, glm::vec3(2.5f, 0.25f, 0.25f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36); //Closer to the camera upper platfrom



		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-1.5f, 3.75f, -6.5f + modelZPosition));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));  // Rotate 45 degrees around the X-axis (upward)
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.7f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36); //handle

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-2.5f, 3.75f, -6.5f + modelZPosition));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));  // Rotate 45 degrees around the X-axis (upward)
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.7f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36); //handle

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-2.f, 4.f, -7.f + modelZPosition));
		model = glm::scale(model, glm::vec3(1.f, 0.1f, 0.1f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36); //handle
		/* Trolley */
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, texture_rail);
		glUseProgram(shaderProgram);
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-.6f, -.5f, -4.f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, -12.f));
		mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_trolley);
		glDrawArrays(GL_TRIANGLES, 0, 36); //Rail

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-3.4f, -.5f, -4.f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, -12.f));
		mloc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_trolley);
		glDrawArrays(GL_TRIANGLES, 0, 36); //Rail



		/* Wheels */
		glBindTexture(GL_TEXTURE_2D, texture_wheel);
		glUseProgram(shaderProgram);

		glm::mat4 modelCylinder = glm::mat4(1.f);
		modelCylinder = glm::translate(modelCylinder, glm::vec3(-.6f, 0.f, 0.f + modelZPosition));
		modelCylinder = glm::rotate(modelCylinder, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		modelCylinder = glm::scale(modelCylinder, glm::vec3(0.5f, 0.3f, 0.5f));
		int mlocCylinder = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mlocCylinder, 1, GL_FALSE, glm::value_ptr(modelCylinder));
		glBindVertexArray(VAO_cylinder);
		glDrawArrays(GL_TRIANGLES, 0, num_segs * 3 * 3 * 6);

		modelCylinder = glm::mat4(1.f);
		modelCylinder = glm::translate(modelCylinder, glm::vec3(-.6f, 0.f, -6.f + modelZPosition));
		modelCylinder = glm::rotate(modelCylinder, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		modelCylinder = glm::scale(modelCylinder, glm::vec3(0.5f, 0.3f, 0.5f));
		glUniformMatrix4fv(mlocCylinder, 1, GL_FALSE, glm::value_ptr(modelCylinder));
		glBindVertexArray(VAO_cylinder);
		glDrawArrays(GL_TRIANGLES, 0, num_segs * 3 * 3 * 6);

		modelCylinder = glm::mat4(1.f);
		modelCylinder = glm::translate(modelCylinder, glm::vec3(-3.4f, 0.f, 0.f + modelZPosition));
		modelCylinder = glm::rotate(modelCylinder, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		modelCylinder = glm::scale(modelCylinder, glm::vec3(0.5f, 0.3f, 0.5f));
		glUniformMatrix4fv(mlocCylinder, 1, GL_FALSE, glm::value_ptr(modelCylinder));
		glBindVertexArray(VAO_cylinder);
		glDrawArrays(GL_TRIANGLES, 0, num_segs * 3 * 3 * 6);

		modelCylinder = glm::mat4(1.f);
		modelCylinder = glm::translate(modelCylinder, glm::vec3(-3.4f, 0.f, -6.f + modelZPosition));
		modelCylinder = glm::rotate(modelCylinder, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		modelCylinder = glm::scale(modelCylinder, glm::vec3(0.5f, 0.3f, 0.5f));
		glUniformMatrix4fv(mlocCylinder, 1, GL_FALSE, glm::value_ptr(modelCylinder));
		glBindVertexArray(VAO_cylinder);
		glDrawArrays(GL_TRIANGLES, 0, num_segs * 3 * 3 * 6);

		glBindVertexArray(0); 
		/* Wheels */

		/* Furnace */
		glBindTexture(GL_TEXTURE_2D, texture_wheel);
		glUseProgram(shaderProgram);

		modelCylinder = glm::mat4(1.f);
		modelCylinder = glm::translate(modelCylinder, glm::vec3(-2.f, 5.f, 6.f));
		modelCylinder = glm::rotate(modelCylinder, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelCylinder = glm::scale(modelCylinder, glm::vec3(2.5f, 10.f, 2.5f));
		mlocCylinder = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mlocCylinder, 1, GL_FALSE, glm::value_ptr(modelCylinder));
		glBindVertexArray(VAO_cylinder);
		glDrawArrays(GL_TRIANGLES, 0, num_segs * 3 * 3 * 6);

		glBindTexture(GL_TEXTURE_2D, texture_beams);
		glUseProgram(shaderProgram);
		modelCylinder = glm::mat4(1.f);
		modelCylinder = glm::translate(modelCylinder, glm::vec3(-2.f, 5.f, 1.f));
		modelCylinder = glm::rotate(modelCylinder, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelCylinder = glm::scale(modelCylinder, glm::vec3(1.75f, 0.5f, 1.75f));
		mlocCylinder = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mlocCylinder, 1, GL_FALSE, glm::value_ptr(modelCylinder));
		glBindVertexArray(VAO_cylinder);
		glDrawArrays(GL_TRIANGLES, 0, num_segs * 3 * 3 * 6);

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-1.5f, 4.75f, 0.5f));
		model = glm::rotate(model, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));  // Rotate 45 degrees around the X-axis (upward)
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.7f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36); //handle

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-2.5f, 4.75f, 0.5f ));
		model = glm::rotate(model, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));  // Rotate 45 degrees around the X-axis (upward)
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.7f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36); //handle

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-2.f, 4.85f, 0.f));
		model = glm::scale(model, glm::vec3(1.f, 0.2f, 0.05f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_control);
		glDrawArrays(GL_TRIANGLES, 0, 36); //handle

		glBindVertexArray(0);



		glBindTexture(GL_TEXTURE_2D, texture_beams);
		glUseProgram(shaderProgram);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-5.8f, -0.6f, 8.5f));
		model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_beam);
		glDrawArrays(GL_TRIANGLES, 0, 84);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-5.8f, -0.6f, 2.5f));
		model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
		glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_beam);
		glDrawArrays(GL_TRIANGLES, 0, 84);
		/* Furnace */

		/* Circle */

		/*glm::mat4 modelCircle = glm::mat4(1.f);
		modelCircle = glm::translate(modelCircle, glm::vec3(-0.5f, 0.f, 0.f)); 
		modelCircle = glm::rotate(modelCircle, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelCircle = glm::scale(modelCircle, glm::vec3(0.5, 0.5f, 1.f)); 
		int mlocCircle = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(mlocCircle, 1, GL_FALSE, glm::value_ptr(modelCircle));
		glBindVertexArray(VAO_circle);
		glDrawArrays(GL_TRIANGLES, 0, num_segs * 3);*/

		/* Circle */

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();

	return 0;
}

/*Change the color of the model
int col = glGetUniformLocation(shaderProgram, "color");
glUniform3f(col, 1.0f, 0.0f, 1.0f);*/
