#include "parallelepiped.h"
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <GLUT/glut.h>
parallelepiped::parallelepiped(){
	this->length = DEFAULT_SIZE;
	this->width  = DEFAULT_SIZE;
	this->height = DEFAULT_SIZE;
	position = new vector();
	CHECK_NULLSTRING
	texture = nullString;
}
			
parallelepiped::parallelepiped(float length, float width, float height, char*textureName){
	this->length = length;
	this->width  = width;
	this->height = height;
	position = new vector();
	texture = textureName;
}

float parallelepiped::verticalOffset(){
	return 0;
}

void parallelepiped::preview(){
	std::cout<<"parallelepiped of "<<this->length<<"x"<<this->width<<"x"<<this->height<<" at ";	//endline will be put by position->preview
	position->preview();
	std::cout<<"\ttexture: "<<texture<<std::endl;
}

void parallelepiped::draw()
{
	/*
	float mdiffuse[] = {2,3,5,1};
	float emit[] = {0.35,0.35,0.0,1};
	float shine[] = {128};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mdiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,emit);
	*/

	parallelepiped* p = this;
	
	glPushMatrix();
		glTranslatef(p->position->X(), p->position->Y(), p->position->Z());
			glBegin(GL_POLYGON);
				//face in zx plane
				glTexCoord2f(0.0, 0.0); glVertex3f(0,0 ,p->width);//A
				glTexCoord2f(0.0, 1.0); glVertex3f(p->length, 0, p->width);//B
				glTexCoord2f(1.0, 1.0); glVertex3f(p->length, 0, 0);//C
				glTexCoord2f(1.0, 0.0); glVertex3f(0, 0, 0);//H
		glEnd();

		glBegin(GL_POLYGON);
				//face in yz plane
				glTexCoord2f(0.0, 0.0); glVertex3f(0, 0 , 0);//A
				glTexCoord2f(0.0, 1.0); glVertex3f(0, 0, p->width);//F
				glTexCoord2f(1.0, 1.0); glVertex3f(0, p->height, 0);//H
				glTexCoord2f(1.0, 0.0); glVertex3f(0, p->height, p->width);//E

		glEnd();

		glBegin(GL_POLYGON);
				//face in xy plance
				glTexCoord2f(0.0, 0.0); glVertex3f(p->length, 0, 0);//C
				glTexCoord2f(0.0, 1.0); glVertex3f(0, 0, 0);//H
				glTexCoord2f(1.0, 1.0); glVertex3f(0, p->height,0);//E
				glTexCoord2f(1.0, 0.0); glVertex3f(p->length,p->height, 0);//D
		glEnd();
		glBegin(GL_POLYGON);
				//|| to XY plane. AGBF
				glTexCoord2f(0.0, 0.0); glVertex3f(0, p->height, p->width);//F
				glTexCoord2f(0.0, 1.0); glVertex3f(0,0 ,p->width);//A
				glTexCoord2f(1.0, 1.0); glVertex3f(p->length, p->height, p->width);//G
				glTexCoord2f(1.0, 0.0); glVertex3f(p->length, 0, p->width);//B
		        
		glEnd();
		
		glBegin(GL_POLYGON);
				//|| to yz plane bcdg
				glTexCoord2f(0.0, 0.0); glVertex3f(p->length, 0, p->width);//B
				glTexCoord2f(0.0, 1.0); glVertex3f(p->length, 0, 0);//C
				glTexCoord2f(1.0, 1.0); glVertex3f(p->length, p->height, 0);//D
				glTexCoord2f(1.0, 0.0); glVertex3f(p->length, p->height, p->width);//G	
		glEnd();
		glBegin(GL_POLYGON);

					//|| to xz
				glTexCoord2f(0.0, 0.0); glVertex3f(0, p->height,0);//E
				glTexCoord2f(0.0, 1.0); glVertex3f(0, p->height, p->width);//F
				glTexCoord2f(1.0, 1.0); glVertex3f(p->length, p->height, 0);//D
				glTexCoord2f(1.0, 0.0); glVertex3f(p->length, p->height, p->width);//G
			glEnd();
	glPopMatrix();
	glFlush();
}

//bounding box constructors
parallelepiped::parallelepiped(parallelepiped* toCopy){
	this->length = toCopy->length;
	this->width  = toCopy->width;
	this->height = toCopy->height;

	position = new vector( toCopy->position );

	texture = toCopy->texture;
}

parallelepiped::parallelepiped(cylinder* toEnvelop){
	double maxRad = toEnvelop->topRadius > toEnvelop->baseRadius
	                 ? toEnvelop->topRadius
					 : toEnvelop->baseRadius;

	this->length = maxRad*2;
	this->width  = maxRad*2;
	this->height = toEnvelop->height;

	position = new vector( toEnvelop->position );
	//translate to bottom-left-back corner
	position->_x -= maxRad;
	position->_z -= maxRad;

	texture = toEnvelop->texture;
}

parallelepiped::parallelepiped(sphere* toEnvelop){
	double diam = toEnvelop->radius*2;

	this->length = diam;
	this->width  = diam;
	this->height = diam;

	position = toEnvelop->position->subtract( toEnvelop->radius );

	texture = toEnvelop->texture;
}

parallelepiped::parallelepiped(disk* toEnvelop){
	double diam = toEnvelop->radius*2;

	this->length = diam;
	this->width  = diam;
	this->height = diam;

	position = new vector( toEnvelop->position );
	//translate to bottom-left-back corner
	position->_x -= toEnvelop->radius;

	texture = toEnvelop->texture;
}

parallelepiped::parallelepiped(torus* toEnvelop){
	double diam = toEnvelop->outerRadius*2;

	this->length = diam;
	this->width  = diam;
	this->height = toEnvelop->verticalOffset()*2;

	position = new vector( toEnvelop->position );
	//translate to bottom-left-back corner
	position->_x -= toEnvelop->outerRadius;
	position->_z -= toEnvelop->outerRadius;
	position->_y -= toEnvelop->verticalOffset();

	texture = toEnvelop->texture;
}

parallelepiped::parallelepiped(teapot* toEnvelop){
	this->length = toEnvelop->size;
	this->width  = toEnvelop->size;
	this->height = toEnvelop->size;

	position = toEnvelop->position->subtract( toEnvelop->verticalOffset() );

	texture = toEnvelop->texture;
}

parallelepiped::parallelepiped(Stage* toEnvelop){
	this->length = toEnvelop->length();
	this->width  = toEnvelop->width();
	this->height = toEnvelop->height();

	position = new vector( toEnvelop->westWall->coord,
	                             toEnvelop->floor->coord,
	                             toEnvelop->northWall->coord,
	                             false
	                           );

	//texture = toEnvelop->texture;
	CHECK_NULLSTRING;
	texture = nullString;
}
