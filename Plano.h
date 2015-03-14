#ifndef _PLANO
	#define _PLANO
		
	#import <OpenGL/gl.h>
	#import <OpenGL/glu.h>
	#import <GLUT/glut.h>	
	//Valoes posibles de Plano.parallel
	#define XY '0'
	#define YZ '1'
	#define ZX '2'
	
	class Plano{ 
		public:
			//Class attributes
			char parallel;	//plano canónico al cual este plano es paralelo. Puede ser XY, YZ, ó ZX
			GLdouble w_inf;	//coordenada inferior de la anchura del plano
			GLdouble w_sup;	//coordenada superior de la anchura del plano
			GLdouble h_inf;	//coordenada inferior de la altura del plano
			GLdouble h_sup;	//coordenada superior de la altura del plano
			GLdouble coord;	//coordenada del plano en el eje al cual es
				     			//perpendicular el plano (eje y para el plano Z-X,
				     			//eje x para el plano Y-Z)
			
			//constructors
			Plano();	//crea un plano XY centrado en el origen de 10x10
			Plano(char parallel, GLdouble w_inf, GLdouble w_sup, GLdouble h_inf, GLdouble h_sup, GLdouble coord);
				//aborta si parallel no es XY, YZ ni ZX; ó si inf > sup
			
			//Information functions
			GLdouble width();	//anchura del plano
			GLdouble height();	//altura del plano
			char coordAxis();	//Eje a lo largo del cual se encuentra coord. Retorna 'x', 'y', ó 'z'.
			
			//graphic functions
			void draw();
	};
#endif
