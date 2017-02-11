# Tron-Race-Game
There is an archive with all the specifications needed about the game and the files. Nevertheless following is a small introduction:
[SPANISH]
Especificación oficial de archivos de juego
Los archivos de juego consisten de texto plano. Cada dato ocupa una línea.
Estructura del archivo
Cada archivo comienza 
declarando las constantes universales:

	el número de vidas y
	el número de niveles

De ahí en adelante, el programa lee tantos niveles como se hayan declarado. 
Cada nivel tiene la siguiente estructura:

	Datos del área de juego
	
		Datos del terreno
		Obstáculos
	
	Datos de los jugadores
		Datos del jugador humano
		Datos de los contrincantes
Área de juego
Terreno
Los datos del terreno se componen de:

	las dimensiones del área de juego (ancho por alto)
	la posición de la salida (coordenadas X-Z)
	la textura del cielo (el nombre de archivo de una imagen perfectamente 
	cuadrada, cuyas dimensiones sean potencias de 2)
	el mapa de alturas
	
		archivo de textura
		tamaño que debe tener el terreno que éste genera
		posición del mismo en el área de juego
	


Obstáculos
Los obstáculos deben precederse de un número que indica cuántos obstáculos 
tiene el nivel. Cada obstáculo se compone de:

	Representación del obstáculo
	Camino del obstáculo
	Rapidez de movimiento

Estos caminos se constituyen de una lista de coordenadas en XYZ, precedidos 
del número de coordenadas. El origen de estas coordenadas se encuentra en el 
centro del terreno de juego (el piso de la escena). Para objetos estacionarios, 
colóquese un sólo punto.
Jugadores
Humano
Los datos del jugador humano son los primeros datos de jugador que se deben 
dar. Los datos del jugador humano vienen dados por:

	su representación 
	su posición inicial en el nivel (coordenadas X-Z)
	su rapidez máxima a través de aceleración ordinaria, en unidades por 
	segundo (single-precision float)
	su rapidez máxima a través de aceleración por impulso adicional, en 
	unidades por segundo (single-precision float)
	La duración, en segundos, de este impulso adicional (single-precision 
	float)
	El tiempo, en segundos, antes del próximo impulso (single-precision 
	float)

Contrincantes
Cada contrincante colocado en el escenario intentará interceptar al jugador 
usando una trayectoria de línea recta. Para contrincantes que siguen una 
trayectoria fija, considere representarlos como obstáculos con un camino.

	Representación 
	su posición inicial en el nivel (coordenadas X-Z)
	su rapidez máxima, en unidades por segundo (single-precision float)


Las representaciones de todos los elementos siguen la siguiente estructura 
uniformemente:

	Tipo
	Tamaño
	Textura

El tipo debe ser uno de los siguientes caracteres: c, y, s, d ó m. Este 
caracter dicta los contenidos de tamaño de la siguiente manera

	
		Símbolo
		Significado
		Parámetros de &quot;tamaño&quot;
		Coordenadas indican
	
	
		p
		paralelepípedo
		ancho, alto, profundidad
		esquina inferior-izquierda posterior
	
	
		y
		cilindro
		radio de base, radio de tapa superior, altura
		centro de tapa inferior
	
	
		s
		esfera
		radio
		centro
	
	
		d
		disco
		radio
		centro
	
	
		u
		tetera de Utah
		tamaño
		centro?
	
	
		t
		toro (dona)
		radio interno, radio externo
		centro!
