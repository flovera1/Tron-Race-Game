#ifndef __RAY
#define __RAY
	#include <iostream>//cout
	#include "vector.h"

	class ray{

		public:
			vector* point; //point of a line(ray)
			vector* direction; //direction of a line(ray)
			ray(){
				this->point = new vector();
				this->direction = new vector();
			}
			
			ray(vector* p, vector* d){
				this->point = new vector(p->_x, p->_y, p->_z, false);
				this->direction = new vector(d->_x, d->_y, d->_z, false);
			};
			
			//getters:
			vector* _point(){return point;}
			vector* _direction(){return direction;}
						
			ray* unitary(ray* r);/* calculate the unitary vector of a ray(direction unitary)*/
			bool adjacentPoint(ray* ray1, vector* point1);
			ray* invert(ray* y, ray* result);//calculate the inverse of a ray

		
			double dist2(vector* point1, vector* point2);
			double dist(ray* r, vector* point1, vector* point2);

			void preview();
	};
	

	
#endif
