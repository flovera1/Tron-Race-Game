#include <assert.h>
#include "Plano.h"	//function declarations

//constructors

Plano::Plano(){
	this->parallel = XY;
	
	this->w_inf = -5;
	this->w_sup =  5;
	
	this->h_inf = -5;
	this->h_sup =  5;
	
	this->coord =  0;
}

Plano::Plano(char parallel, GLdouble w_inf, GLdouble w_sup, GLdouble h_inf, GLdouble h_sup, GLdouble coord){
	assert(parallel == XY || parallel == YZ || parallel == ZX);
	this->parallel = parallel;
	
	assert(w_inf <= w_sup);
	this->w_inf = w_inf;
	this->w_sup = w_sup;
	
	assert(h_inf <= h_sup);
	this->h_inf = h_inf;
	this->h_sup = h_sup;
	
	this->coord = coord;
}

//Information functions

//anchura del plano
GLdouble Plano::width(){
	return this->w_sup - this->w_inf;
}

//altura del plano
GLdouble Plano::height(){
	return this->h_sup - this->h_inf;
}

//Eje a lo largo del cual se encuentra coord. Retorna 'x', 'y', ó 'z'.
char Plano::coordAxis(){
	switch(this->parallel){
		case(XY):
			return 'z';
		case(YZ):
			return 'x';
		case(ZX):
			return 'y';
		default:
			return '?';
	}
}

//graphic functions
void Plano::draw(){
	glBegin(GL_QUADS);
		switch(this->parallel){
			case(XY):
				glVertex3f(this->w_inf, this->h_inf, coord);
				glVertex3f(this->w_inf, this->h_sup, coord);
				glVertex3f(this->w_sup, this->h_sup, coord);
				glVertex3f(this->w_sup, this->h_inf, coord);
				break;
			case(YZ):
				glVertex3f(coord, this->h_inf, this->w_inf);
				glVertex3f(coord, this->h_sup, this->w_inf);
				glVertex3f(coord, this->h_sup, this->w_sup);
				glVertex3f(coord, this->h_inf, this->w_sup);
				break;
			case(ZX):
				glVertex3f(this->w_inf, coord, this->h_inf);
				glVertex3f(this->w_inf, coord, this->h_sup);
				glVertex3f(this->w_sup, coord, this->h_sup);
				glVertex3f(this->w_sup, coord, this->h_inf);
				break;
		}
	glEnd();
}

