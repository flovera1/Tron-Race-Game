#include "timer.h"

/*	Devuelve la cantidad de segundos que han pasado desde la fecha-hora dada,
 *	o la fecha-hora actual si startTime es NULL.
 *	Si el sistema no puede obtener la fecha-hora actual, devuelve 0.0
 *	e imprime un error en pantalla
 */
double secondsElapsed(SMTKU start){
	SMTKU current;
	
	#if defined(_WIN32) || defined(WINDOWS)
		current = GetTickCount();
		/*	GetTickCount mide los milisegundos desde que se encendi�
		 *	la m�quina pero hace overflow a los 50 d�as. Ya que DWORD
		 *	es un UNSIGNED INTEGER, es necesario verificar que
		 *	current < start y obligarlo a hacer overflow
		 *	en sentido inverso.
		 */
		if(current < start)
			return ((current-2147483647) - (start-2147483647))/1000.0;
			/*	Dos millardos (� 2.147.483.647 para ser exactos)
			 *	es la mitad del rango de un DWORD, equivalente a
			 *	unos 24 d�as y 21 horas.
			 *	N�tese que esta resta no arreglar� el problema si el
			 *	tiempo medido excede esos 24 d�as y 21 horas, pero se
			 *	espera que el programa llamador no lleve tanto tiempo
			 *	corriendo
			 */
		else
			return (current - start)/1000.0;
	#elif defined(__gnu_linux__) || defined(linux) || defined(UNIX)
		if(!gettimeofday(&current, NULL))
			//N�tese que tv_usec es un SIGNED INTEGER por lo que restarlos
			//no afecta la siguiente suma, si resulta que start.tv_usec
			//era mayor que current.tv_usec
			return current.tv_sec - start.tv_sec + (current.tv_usec - start.tv_usec)/1000000.0;
		else{
			//Nota: gettimeofday s�lo retorna false si recibe apuntadores
			//inv�lidos, o si su segundo argumento es no-nulo. Esto hace
			//innecesario el "if" pero se mantiene por completitud
			TIME_ERR;
			return 0.0;
		}
	#else
		current = time(NULL);
		if(current != -1)
			return difftime(current, start);
		else{
			TIME_ERR;
			return 0.0;
		}
	#endif
}
