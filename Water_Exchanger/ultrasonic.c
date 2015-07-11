/*
获取距离，返回值单位为厘米
参数解释：
p_trig——模块输入引脚
p_echo——模块输出引脚
p_min——最小距离(测的的距离小于该值将被丢弃),单位:厘米
p_max——最大距离(测的的距离大于该值将被丢弃),单位:厘米
p_count——统计次数(获得这么多次有效值后求均值)
p_max_loop——最大循环次数(包括丢弃的数据在内,最多测量多少次)
返回值：
距离，单位厘米
-1，如果出错
*/

float get_distance(int p_trig,int p_echo,float p_min,float p_max,int p_count,int p_max_loop)
{
  int t_count=0;
  float t_total_distance=0;
  while(p_max_loop--)
  {
    digitalWrite(p_trig,LOW);
    delayMicroseconds(2);
    digitalWrite(p_trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(p_trig,LOW);
    float t_time=pulseIn(p_echo,HIGH);
    float t_distance=t_time/58.8;
    if(t_distance<p_min||t_distance>p_max)
    {
      continue;
    }
    t_count++;
    t_total_distance+=t_distance;
    if(t_count==p_count)
    {
      return t_total_distance/p_count;
    }
  }
  return -1;
}
