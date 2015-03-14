#ifndef _parallelepiped
	#define _parallelepiped
	/*
	* Estructura que representa las dimensiones de un paralelepipedo
	*mis intenciones son tener una estructura que tenga
	*un centro y unas dimensiones.
	*porque los algoritmos que funcionan para calcular las colisiones requieren
	*que las figuras en cuestion tengan un "centro"
	*/
	#include "representation.h"
	#include "Stage.h"

	class parallelepiped: public representation { 
		//NOTICE: position here denotes the point at the back bottom-left corner
		public:
		    float length;//dim x
			float width;//dim z
		    float height;//dim y
				
		        
			//raw constructors
			parallelepiped();
			parallelepiped(float length, float width, float height, char*texture);

			float verticalOffset();

			//graphic
			void preview();
			void draw();

			//bounding box constructors
			parallelepiped(parallelepiped* toCopy);
			parallelepiped(cylinder* toEnvelop);
			parallelepiped(sphere* toEnvelop);
			parallelepiped(disk* toEnvelop);
			parallelepiped(torus* toEnvelop);
			parallelepiped(teapot* toEnvelop);
			parallelepiped(Stage* toEnvelop);
	};
	
#endif
