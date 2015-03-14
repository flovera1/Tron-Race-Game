#include <iostream>	//cout
#include "Stage.h"

//Crea un escenario con cuatro paredes semitransparentes y un piso, en el centro actual.
//id est: el centro del piso es (0,0,0)
//el color es especificado al llamar a drawStage
Stage::Stage(GLdouble length, GLdouble width, GLdouble height){
	
	northWall = new Plano(XY, -length/2, length/2, 0, height,   width/2);
	southWall = new Plano(XY, -length/2, length/2, 0, height,  -width/2);
	eastWall  = new Plano(YZ,  -width/2,  width/2, 0, height,  length/2);
	westWall  = new Plano(YZ,  -width/2,  width/2, 0, height, -length/2);
	
	floor     = new Plano(ZX, -length/2, length/2, -width/2, width/2, 0);
}

//Crea un escenario de 10x10x10
Stage::Stage(){
	northWall = new Plano(XY, -5, 5, 0, 5,  5);
	southWall = new Plano(XY, -5, 5, 0, 5, -5);
	eastWall  = new Plano(YZ, -5, 5, 0, 5,  5);
	westWall  = new Plano(YZ, -5, 5, 0, 5, -5);
	
	floor     = new Plano(ZX, -5, 5, -5, 5, 0);
}

//Dibuja el piso y las paredes de la escena del color especificado
//Este método cambia glColor por lo que debe ser vuelto a fijar si se va a dibujar algo adicional luego de dibujar la escena
void Stage::draw(GLdouble R, GLdouble G, GLdouble B){
	glPushMatrix();
		glColor4d(R, G, B, .75);
		floor->draw();
		
		glColor4d(R, G, B, .25);
		northWall->draw();
		southWall->draw();
		eastWall->draw();
		westWall->draw();
	glPopMatrix();
}

void Stage::preview(){
	std::cout<<std::endl;
	std::cout<<"\t"<<this->northWall->coord<<std::endl;
	std::cout<<this->westWall->coord<<"\t\t"<<this->eastWall->coord<<std::endl;
	std::cout<<"\t"<<this->southWall->coord<<std::endl;
}

//intenta estimar el parámetro "length" originalmente pasado al constructor
GLdouble Stage::length(){
	return this->eastWall->coord - this->westWall->coord;
}

//intenta estimar el parámetro "width" originalmente pasado al constructor
GLdouble Stage::width(){
	return this->northWall->coord - this->southWall->coord;
}

//intenta estimar el parámetro "length" originalmente pasado al constructor
GLdouble Stage::height(){
	return this->northWall->h_sup - this->northWall->h_inf;
}