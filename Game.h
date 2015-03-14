#ifndef _gameClass
#define _gameClass
	#include "Level.h"

	class Game{
		public:
			int totalLives;
			int totalLevels;
			Level** levels;
			bool badBit;	//indicates game contains illegal data.

			Game();
			Game(int lives, int levels);
			void preview();
	};
#endif
