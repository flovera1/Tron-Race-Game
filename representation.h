#ifndef _representation
	#define _representation
	#include <iostream>	//cout
	#import <OpenGL/gl.h>
	#import <OpenGL/glu.h>
	#import <GLUT/glut.h>
	#include "vector.h"
	
	#define DEFAULT_SIZE	5
	#define SLICES	11
	#define	STACKS	7
	
	static char* nullString = NULL;

	#define CHECK_NULLSTRING\
		if(nullString == NULL){\
			nullString = new char[1];\
			nullString[0] = '\0';\
		}
	
	class representation{
		public:
			vector* position;
			char* texture;
			
			virtual void draw() = 0;
			virtual void preview() = 0;

			virtual float verticalOffset() = 0;	//gives the distance off the ground that the position vector indicates

			//replaces the filler value the contructor places in "position"
			void initPos(vector* newPosition){
				//if(position != NULL)
				//	free(position);
				position = newPosition;
			}
	};

	class cylinder: public representation{
		public:
			float baseRadius,
			      topRadius,
			      height;
			
			cylinder(){
				this->baseRadius = DEFAULT_SIZE;
				this->topRadius = DEFAULT_SIZE;
				this->height = DEFAULT_SIZE;
				
				CHECK_NULLSTRING;
				texture = nullString;
				
				position = new vector();
			}

			//initializes the size and texture of the cylinder
			//Note: the position must be initialized after the fact
			cylinder(float baseRadius, float topRadius, float height, char* textureName){
				this->baseRadius = baseRadius;
				this->topRadius = topRadius;
				this->height = height;
				texture = textureName;
				position = new vector();
			}

			void draw(){
				glPushMatrix();
					glTranslated(position->X(), position->Y(), position->Z());
					gluCylinder(gluNewQuadric(), baseRadius, topRadius, height, SLICES, 1);
				glPopMatrix();
			}
			void preview(){
				std::cout<<"cylinder base r="<<this->baseRadius<<", top r="<<this->topRadius<<", h="<<this->height<<" at ";	//endline will be put by position->preview
				position->preview();
				std::cout<<"\ttexture: "<<texture<<std::endl;
			}
			
			float verticalOffset(){
				return 0;
			}
	};
	
	class sphere: public representation{
		public:
			float radius;
			
			sphere(){
				this->radius = DEFAULT_SIZE;
				
				CHECK_NULLSTRING;
				texture = nullString;
				
				position = new vector();
			}

			//initializes the size and texture of the cylinder
			//Note: the position must be initialized after the fact
			sphere(float radius, char* textureName){
				this->radius = radius;
				texture = textureName;
				position = new vector();
			}

			void draw(){
				glPushMatrix();
					glTranslated(position->X(), position->Y(), position->Z());
					glutSolidSphere(radius, SLICES, STACKS);
				glPopMatrix();
			}
			void preview(){
				std::cout<<"sphere r="<<this->radius<<" at ";	//endline will be put by position->preview
				position->preview();
				std::cout<<"\ttexture: "<<texture<<std::endl;
			}
			
			float verticalOffset(){
				return radius;
			}
	};


	class disk: public representation{
		public:
			float radius;
			
			disk(){
				this->radius = DEFAULT_SIZE;
				
				CHECK_NULLSTRING;
				texture = nullString;
				
				position = new vector();
			}

			//initializes the size and texture of the cylinder
			//Note: the position must be initialized after the fact
			disk(float radius, char* textureName){
				this->radius = radius;
				texture = textureName;
				position = new vector();
			}

			void draw(){
				glPushMatrix();
					glTranslated(position->X(), position->Y(), position->Z());
					gluDisk(gluNewQuadric(), 0, radius, SLICES, 1);
				glPopMatrix();
			}
			void preview(){
				std::cout<<"disk r="<<this->radius<<" at ";	//endline will be put by position->preview
				position->preview();
				std::cout<<"\ttexture: "<<texture<<std::endl;
			}
			
			float verticalOffset(){
				return radius;
			}
	};

	class torus: public representation{
		public:
			float innerRadius,
			      outerRadius;
			
			torus(){
				this->innerRadius = DEFAULT_SIZE;
				this->outerRadius = DEFAULT_SIZE;
				
				CHECK_NULLSTRING;
				texture = nullString;
				
				position = new vector();
			}

			//initializes the size and texture of the cylinder
			//Note: the position must be initialized after the fact
			torus(float innerRadius, float outerRadius, char* textureName){
				this->innerRadius = innerRadius;
				this->outerRadius = outerRadius;
				texture = textureName;
				position = new vector();
			}

			void draw(){
				glPushMatrix();
					glTranslated(position->X(), position->Y(), position->Z());
					glutSolidTorus(innerRadius, outerRadius, SLICES, STACKS);
				glPopMatrix();
			}
			void preview(){
				std::cout<<"torus inner r="<<this->innerRadius<<", outer r="<<this->outerRadius<<" at ";	//endline will be put by position->preview
				position->preview();
				std::cout<<"\ttexture: "<<texture<<std::endl;
			}
			
			float verticalOffset(){
				return (outerRadius - innerRadius)/2; //radius of a cross-section of the torus
			}
	};

	class teapot: public representation{
		public:
			float size;

			teapot(){
				this->size = DEFAULT_SIZE;
				
				CHECK_NULLSTRING;
				texture = nullString;
				
				position = new vector();
			}

			teapot(float size, char* textureName){
				this->size = size;
				texture = textureName;
				position = new vector();
			}

			void draw(){
				glPushMatrix();
					glTranslated(position->X(), position->Y(), position->Z());
					glutSolidTeapot(this->size);
				glPopMatrix();
			}

			void preview(){
				std::cout<<"teapot of size "<<size<<" at ";//endline will be put by position->preview
				position->preview();
				std::cout<<"\ttexture: "<<texture<<std::endl;
			}
			
			float verticalOffset(){
				return size/2;
			}
	};

#endif