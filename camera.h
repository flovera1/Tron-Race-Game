#ifndef _camera
#define _camera

#include "vector.h"

/*
 * La clase camara es una que toma como un eje fijo 
 * el que esta centrado en el centro de la escena
 * es decir, la camara siempre estara viendo al centro de
 * la escena, por lo que los parametros de 'eye' de la camara
 * siempre estaran fijos
 * 
 * movimientos:: los movimientos de la camara seran con las flechas direccionales
 * 				 la flecha <- mueve la camara a la izquierda(la rota negativamente en el eje y)
 * 				 la flecha -> mueve la camara a la derecha(la rota en positivamente en el eje y)
 * 				 la flecha hacia arriba, eleva la camara
 * 				 la flecha hacia abajo, dismiune la elevacion de la camara
 * Fin
 * */
 
class camera
{
public:
	vector *eye,	//coordenadas de la cámara
	       *center,	//coordenadas del objetivo al que apunta la cámara 
	       *up;	//vector perpendicular a la cámra
	GLdouble radius,	//distancia de la cámara de su objetivo
	         aspectratio;	//proporción de las imágenes producidas


	camera();

	void Rotate ( GLfloat Angle );

	void MoveForward ( GLfloat Distance ); //mueve la camara en la posicion z
	void MoveUpward ( GLfloat Distance ); 
	void StrafeRight ( GLfloat Distance );
	void StrafeLeft ( GLfloat Distance );
	void focus();	//fija el punto de vista del observador como originando en esta cámara

private:
	GLdouble camera_angle;	//ángulo de la cámara con respecto al plano XY (círculo descrito sobre el plano XZ)

};

#endif
