#ifndef _ROS_planning_msgs_Step_h
#define _ROS_planning_msgs_Step_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "planning_msgs/Binding.h"

namespace planning_msgs
{

  class Step : public ros::Msg
  {
    public:
      typedef int32_t _id_type;
      _id_type id;
      typedef int32_t _parent_type;
      _parent_type parent;
      typedef const char* _type_type;
      _type_type type;
      typedef const char* _pattern_type;
      _pattern_type pattern;
      uint32_t call_pattern_length;
      typedef char* _call_pattern_type;
      _call_pattern_type st_call_pattern;
      _call_pattern_type * call_pattern;
      uint32_t bindings_length;
      typedef planning_msgs::Binding _bindings_type;
      _bindings_type st_bindings;
      _bindings_type * bindings;
      typedef float _score_type;
      _score_type score;
      uint32_t duration_length;
      typedef float _duration_type;
      _duration_type st_duration;
      _duration_type * duration;

    Step():
      id(0),
      parent(0),
      type(""),
      pattern(""),
      call_pattern_length(0), call_pattern(NULL),
      bindings_length(0), bindings(NULL),
      score(0),
      duration_length(0), duration(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.real = this->id;
      *(outbuffer + offset + 0) = (u_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->id);
      union {
        int32_t real;
        uint32_t base;
      } u_parent;
      u_parent.real = this->parent;
      *(outbuffer + offset + 0) = (u_parent.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_parent.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_parent.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_parent.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->parent);
      uint32_t length_type = strlen(this->type);
      varToArr(outbuffer + offset, length_type);
      offset += 4;
      memcpy(outbuffer + offset, this->type, length_type);
      offset += length_type;
      uint32_t length_pattern = strlen(this->pattern);
      varToArr(outbuffer + offset, length_pattern);
      offset += 4;
      memcpy(outbuffer + offset, this->pattern, length_pattern);
      offset += length_pattern;
      *(outbuffer + offset + 0) = (this->call_pattern_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->call_pattern_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->call_pattern_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->call_pattern_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->call_pattern_length);
      for( uint32_t i = 0; i < call_pattern_length; i++){
      uint32_t length_call_patterni = strlen(this->call_pattern[i]);
      varToArr(outbuffer + offset, length_call_patterni);
      offset += 4;
      memcpy(outbuffer + offset, this->call_pattern[i], length_call_patterni);
      offset += length_call_patterni;
      }
      *(outbuffer + offset + 0) = (this->bindings_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->bindings_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->bindings_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->bindings_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bindings_length);
      for( uint32_t i = 0; i < bindings_length; i++){
      offset += this->bindings[i].serialize(outbuffer + offset);
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
      union {
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.base = 0;
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->id = u_id.real;
      offset += sizeof(this->id);
      union {
        int32_t real;
        uint32_t base;
      } u_parent;
      u_parent.base = 0;
      u_parent.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_parent.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_parent.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_parent.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->parent = u_parent.real;
      offset += sizeof(this->parent);
      uint32_t length_type;
      arrToVar(length_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
      uint32_t length_pattern;
      arrToVar(length_pattern, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_pattern; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_pattern-1]=0;
      this->pattern = (char *)(inbuffer + offset-1);
      offset += length_pattern;
      uint32_t call_pattern_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      call_pattern_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      call_pattern_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      call_pattern_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->call_pattern_length);
      if(call_pattern_lengthT > call_pattern_length)
        this->call_pattern = (char**)realloc(this->call_pattern, call_pattern_lengthT * sizeof(char*));
      call_pattern_length = call_pattern_lengthT;
      for( uint32_t i = 0; i < call_pattern_length; i++){
      uint32_t length_st_call_pattern;
      arrToVar(length_st_call_pattern, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_call_pattern; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_call_pattern-1]=0;
      this->st_call_pattern = (char *)(inbuffer + offset-1);
      offset += length_st_call_pattern;
        memcpy( &(this->call_pattern[i]), &(this->st_call_pattern), sizeof(char*));
      }
      uint32_t bindings_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      bindings_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      bindings_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      bindings_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->bindings_length);
      if(bindings_lengthT > bindings_length)
        this->bindings = (planning_msgs::Binding*)realloc(this->bindings, bindings_lengthT * sizeof(planning_msgs::Binding));
      bindings_length = bindings_lengthT;
      for( uint32_t i = 0; i < bindings_length; i++){
      offset += this->st_bindings.deserialize(inbuffer + offset);
        memcpy( &(this->bindings[i]), &(this->st_bindings), sizeof(planning_msgs::Binding));
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

    const char * getType(){ return "planning_msgs/Step"; };
    const char * getMD5(){ return "006ef20f0b34b2893a05e6bfad4c98c7"; };

  };

}
#endif