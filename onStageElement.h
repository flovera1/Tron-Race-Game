#ifndef _onStageElement
	#define _onStageElement
	#include "timer.h"
	#include <iostream>
	#include "representation.h"
	#include "ray.h"
	#include "MATH.h"

	class onStageElement{
		public:
			representation* rep;	//cómo dibujar
			ray* velocity;	//vector velocidad
			bool alive;	//indica si el elemento ha sido destruido
		
			//graphic functions
			virtual void preview() = 0;	//text-only represntation of the element. Mmust be printed through standard out.
			virtual void draw() = 0;	//3D representation of the element

			//useful
			virtual void Advance() = 0;	//moves this element the distance corresponding to the elapsed time, if need be. The use of the "movement" method is strongly suggested to ensure the elapsed time is considered
			virtual void reset() = 0;	//make starting point current point
			virtual void inic() = 0;	//allows inheriting classes to define any variables they may need in "Advance"

		protected:
			SMTKU lastTranslation;

			//returns a new direction vector pointing from the current position to the target position
			static vector* headTo(vector* current, vector* target, double magnitude){
				std::cerr<<"\tentered headTo"<<std::endl;
				vector* newDirection = new vector();
				newDirection->subtract(target, current, newDirection);

				newDirection->unitary(newDirection);
				vector* result = newDirection->multiply(magnitude);

				free(newDirection);
				return result;
			}

			//Moves the element along the "velocity" vector, proportionate to the time that has elapsed
			void movement(vector* position, ray* velocity){
				double t = secondsElapsed(lastTranslation);

				if(t > EPSILON){
					position->_x += velocity->direction->_x* t;
					position->_y += velocity->direction->_y* t;
					position->_z += velocity->direction->_z* t;
					CURR_TIME(lastTranslation);
				}

				
				if(velocity->point != position){
					//free(velocity->point);
					velocity->point = position;
				}

				glutPostRedisplay();
			}

	};
#endif
