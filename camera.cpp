#include <iostream>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <GLUT/glut.h>
#include "MATH.h"
#include "vector.h"
#include "camera.h"

//Dimensiones del área de juego
#define	ALTURA_MAXIMA	75

//propiedades universales para toda cámara
#define ANCHO    20
#define ALTO     15
#define NEAR      0.1
#define FAR     200.0
#define APERTURE 12

/* coordenadas de el punto al que apunta la cámara */
vector* center = new vector(0, ALTURA_MAXIMA/2, 0, false);

void camera:: Rotate ( GLfloat Angle ){

	Angle = (Angle * PI)/ 180.0;

	this->camera_angle += Angle;
	this->eye->_x = this->center->_x + this->radius*cos(this->camera_angle);
	this->eye->_z = this->center->_z + this->radius*sin(this->camera_angle);
}
//tan las de abaJO
void camera:: MoveUpward ( GLfloat Distance ){
	this->eye->_y += Distance;
}
 
void camera::focus()
{
	gluPerspective(APERTURE, this->aspectratio, NEAR, FAR);	//ADDED
	glOrtho(-ANCHO, ANCHO, -ALTO, ALTO, 1.0, -1.0);
	gluLookAt( this->eye->_x, this->eye->_y, this->eye->_z,
	           this->center->_x, this->center->_y , this->center->_z ,
	           this->up->_x, this->up->_y, this->up->_z
	         );
}

camera::camera()
{
	this->radius = 85.0;
	this->eye    = new vector(85, ALTURA_MAXIMA,  0, false);
	this->center = new vector(0, ALTURA_MAXIMA/2, 0, false);
	this->up     = new vector(0, 1, 0, true);

	camera_angle = 0;
	aspectratio = 1;
}

