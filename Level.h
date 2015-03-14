#ifndef _Level
	#define _Level
	
	#include "Stage.h"
	#include "vector.h"
	#include "parallelepiped.h"
	#include "heightMap.h"
	#include "obstacle.h"
	#include "player.h"
	
	class Level{
		public:
			Stage* terrain;
			vector* exit;
			char* sky;
			heightMap* map;
			int totalObstacles;
			obstacle** obs;
			int totalPlayers;
			player** players;

			//constructors
			Level();
			Level(Stage* terrain, vector* exit, char* sky, heightMap* map, int totalObstacles, obstacle** obs, int totalPlayers, player** players);

			//graphic functions
			void preview();
			void draw();

			//useful
			void Advance();	//move everything the distance corresponding to teh time elapsed
			void reset();	//put everything back wehre it was at the start of the level
			void inic();	//must be called when movement starts

		private:
			parallelepiped* exitMarker;

			void drawExit();
	};
#endif