#ifndef _obstacle
	#define _obstacle
	#include "timer.h"
	#include "vector.h"
	#include "onStageElement.h"

	class obstacle: public onStageElement{
		public:
			representation* rep;
			int pathLength;
			vector** path;
			double speed;

			//constructors
			obstacle();
			obstacle(representation* rep, int pathLength, vector** path, double speed);

			//graphic
			void draw();
			void preview();

			//useful
			void Advance();	//moves this element the distance corresponding to the elapsed time, if need be
			void reset();	//make starting point current point
			void inic();	//start movement timers

		private:
			int nextPointIndex;
			bool indexIncreasing;
			SMTKU lastReestimate;
			double ETA;	//seconds after lastReestimate at which the object should reach the next point in the path

			void reestimateVelocity();	//adjusts velocity vector to better fit the path, redirecting the object to the next point on it
			void reverseDirection();	//changes the direction on the path this obstacle is heading down
	};
#endif
