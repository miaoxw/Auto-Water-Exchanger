#include <Arduino.h>
#include "ports.h"

namespace Ultrasonic
{
	float getDistance();
	float getDistance(float p_min, float p_max, int p_count, int p_max_loop);
}

//下方繁复方法的简化调用版本
float Ultrasonic::getDistance()
{
	return getDistance(0.0, 10000.0, 15, 30);
}

/*
获取距离，返回值单位为厘米
参数解释：
p_min——最小距离(测的的距离小于该值将被丢弃),单位:厘米
p_max——最大距离(测的的距离大于该值将被丢弃),单位:厘米
p_count——统计次数(获得这么多次有效值后求均值)
p_max_loop——最大循环次数(包括丢弃的数据在内,最多测量多少次)
返回值：
距离，单位厘米
-1，如果出错
*/
float Ultrasonic::getDistance(float p_min, float p_max, int p_count, int p_max_loop)
{
	int t_count = 0;
	float t_total_distance = 0;
	while (p_max_loop--)
	{
		digitalWrite(Ports::ULTRASONIC_TRIG, LOW);
		delayMicroseconds(2);
		digitalWrite(Ports::ULTRASONIC_TRIG, HIGH);
		delayMicroseconds(10);
		digitalWrite(Ports::ULTRASONIC_TRIG, LOW);
		float t_time = pulseIn(Ports::ULTRASONIC_ECHO, HIGH);
		float t_distance = t_time / 58.8;
		if (t_distance<p_min || t_distance>p_max)
		{
			continue;
		}
		t_count++;
		t_total_distance += t_distance;
		if (t_count == p_count)
		{
			return t_total_distance / p_count;
		}
	}
	return -1;
}
