#ifndef _stage
	#define _stage
	
	#import <OpenGL/gl.h>
	#import <OpenGL/glu.h>
	#import <GLUT/glut.h>
	#include "Plano.h"	//Plano
	
	class Stage{
		public:
			Plano *northWall,
			      *southWall,
			      *eastWall,
			      *westWall,
			      *floor;
			
			/* Los constructores crean un escenario con
			 * cuatro paredes semitransparentes y un piso, centrado
			 * en el origen
			 * id est: el centro del piso se coloca en (0,0,0)
			 * El color de escenario es especificado
			 * al llamar drawStage
			 */
			Stage();
			Stage(GLdouble length, GLdouble width, GLdouble height);
			
			//Dibuja el piso y las paredes de la escena del color especificado
			//Este método cambia glColor por lo que debe ser vuelto a fijar si se va a dibujar algo adicional luego de dibujar la escena
			void draw(GLdouble R, GLdouble G, GLdouble B);
			
			void preview();	//imprime las coordenadas de las esquinas del plano dispuestos en la pantalla en forma de cruz

			//intenta estimar el parámetro "length" originalmente pasado al constructor
			GLdouble length();
			//intenta estimar el parámetro "width" originalmente pasado al constructor
			GLdouble width();
			//intenta estimar el parámetro "length" originalmente pasado al constructor
			GLdouble height();
	};
#endif
