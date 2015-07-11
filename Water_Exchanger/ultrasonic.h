#ifndef ULTRASONIC_H
#define ULTRASONIC_H

namespace Ultrasonic
{
	float getDistance();
	float getDistance(float p_min, float p_max, int p_count, int p_max_loop);
}

#endif
