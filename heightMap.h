#ifndef _heightMap
	#define _heightMap
	
	#include <iostream>	//std::cout
	#include "representation.h"
	#include "vector.h"
	
	class heightMap{
		public:
			char* file;
			double length,
			       width,
				   height;
			vector* position;	//position of the map's "floor"

			heightMap(){
				CHECK_NULLSTRING;
				this->file = nullString;
				this->length = 0;
				this->width  = 0;
				position = new vector();
			}

			heightMap(char* file, double length, double width, double maxHeight, double minHeight, double X, double Z){
				this->file = file;
				this->length = length;
				this->width  = width;
				this->height = maxHeight - minHeight;
				position = new vector(X, minHeight, Z, false);
			}

			void preview(){
				std::cout<<"height map \""<<file<<"\" sized at "<<length<<"x"<<width<<"x"<<height<<std::endl;
				position->preview();
			}
	};
#endif