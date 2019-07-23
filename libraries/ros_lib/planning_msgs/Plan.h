#ifndef _ROS_planning_msgs_Plan_h
#define _ROS_planning_msgs_Plan_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "planning_msgs/Step.h"

namespace planning_msgs
{

  class Plan : public ros::Msg
  {
    public:
      uint32_t steps_length;
      typedef planning_msgs::Step _steps_type;
      _steps_type st_steps;
      _steps_type * steps;
      typedef float _score_type;
      _score_type score;
      uint32_t duration_length;
      typedef float _duration_type;
      _duration_type st_duration;
      _duration_type * duration;

    Plan():
      steps_length(0), steps(NULL),
      score(0),
      duration_length(0), duration(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->steps_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->steps_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->steps_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->steps_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->steps_length);
      for( uint32_t i = 0; i < steps_length; i++){
      offset += this->steps[i].serialize(outbuffer + offset);
      }
      union {
        float real;
        uint32_t base;
      } u_score;
      u_score.real = this->score;
      *(outbuffer + offset + 0) = (u_score.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_score.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_score.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_score.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->score);
      *(outbuffer + offset + 0) = (this->duration_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->duration_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->duration_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->duration_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->duration_length);
      for( uint32_t i = 0; i < duration_length; i++){
      union {
        float real;
        uint32_t base;
      } u_durationi;
      u_durationi.real = this->duration[i];
      *(outbuffer + offset + 0) = (u_durationi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_durationi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_durationi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_durationi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->duration[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t steps_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      steps_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      steps_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      steps_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->steps_length);
      if(steps_lengthT > steps_length)
        this->steps = (planning_msgs::Step*)realloc(this->steps, steps_lengthT * sizeof(planning_msgs::Step));
      steps_length = steps_lengthT;
      for( uint32_t i = 0; i < steps_length; i++){
      offset += this->st_steps.deserialize(inbuffer + offset);
        memcpy( &(this->steps[i]), &(this->st_steps), sizeof(planning_msgs::Step));
      }
      union {
        float real;
        uint32_t base;
      } u_score;
      u_score.base = 0;
      u_score.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_score.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_score.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_score.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->score = u_score.real;
      offset += sizeof(this->score);
      uint32_t duration_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      duration_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      duration_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      duration_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->duration_length);
      if(duration_lengthT > duration_length)
        this->duration = (float*)realloc(this->duration, duration_lengthT * sizeof(float));
      duration_length = duration_lengthT;
      for( uint32_t i = 0; i < duration_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_duration;
      u_st_duration.base = 0;
      u_st_duration.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_duration.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_duration.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_duration.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_duration = u_st_duration.real;
      offset += sizeof(this->st_duration);
        memcpy( &(this->duration[i]), &(this->st_duration), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "planning_msgs/Plan"; };
    const char * getMD5(){ return "4b01f5f5f81e029aa892db42087b5828"; };

  };

}
#endif