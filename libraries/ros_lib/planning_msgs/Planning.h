#ifndef _ROS_SERVICE_Planning_h
#define _ROS_SERVICE_Planning_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "planning_msgs/Plan.h"
#include "planning_msgs/Binding.h"

namespace planning_msgs
{

static const char PLANNING[] = "planning_msgs/Planning";

  class PlanningRequest : public ros::Msg
  {
    public:
      typedef const char* _pattern_type;
      _pattern_type pattern;
      uint32_t bindings_length;
      typedef planning_msgs::Binding _bindings_type;
      _bindings_type st_bindings;
      _bindings_type * bindings;
      uint32_t scoring_methods_length;
      typedef char* _scoring_methods_type;
      _scoring_methods_type st_scoring_methods;
      _scoring_methods_type * scoring_methods;
      enum { OSPT = "ospt" };
      enum { PSPT = "pspt" };
      enum { LPFO = "lpfo" };

    PlanningRequest():
      pattern(""),
      bindings_length(0), bindings(NULL),
      scoring_methods_length(0), scoring_methods(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_pattern = strlen(this->pattern);
      varToArr(outbuffer + offset, length_pattern);
      offset += 4;
      memcpy(outbuffer + offset, this->pattern, length_pattern);
      offset += length_pattern;
      *(outbuffer + offset + 0) = (this->bindings_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->bindings_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->bindings_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->bindings_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bindings_length);
      for( uint32_t i = 0; i < bindings_length; i++){
      offset += this->bindings[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->scoring_methods_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->scoring_methods_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->scoring_methods_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->scoring_methods_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->scoring_methods_length);
      for( uint32_t i = 0; i < scoring_methods_length; i++){
      uint32_t length_scoring_methodsi = strlen(this->scoring_methods[i]);
      varToArr(outbuffer + offset, length_scoring_methodsi);
      offset += 4;
      memcpy(outbuffer + offset, this->scoring_methods[i], length_scoring_methodsi);
      offset += length_scoring_methodsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_pattern;
      arrToVar(length_pattern, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_pattern; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_pattern-1]=0;
      this->pattern = (char *)(inbuffer + offset-1);
      offset += length_pattern;
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
      uint32_t scoring_methods_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      scoring_methods_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      scoring_methods_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      scoring_methods_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->scoring_methods_length);
      if(scoring_methods_lengthT > scoring_methods_length)
        this->scoring_methods = (char**)realloc(this->scoring_methods, scoring_methods_lengthT * sizeof(char*));
      scoring_methods_length = scoring_methods_lengthT;
      for( uint32_t i = 0; i < scoring_methods_length; i++){
      uint32_t length_st_scoring_methods;
      arrToVar(length_st_scoring_methods, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_scoring_methods; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_scoring_methods-1]=0;
      this->st_scoring_methods = (char *)(inbuffer + offset-1);
      offset += length_st_scoring_methods;
        memcpy( &(this->scoring_methods[i]), &(this->st_scoring_methods), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return PLANNING; };
    const char * getMD5(){ return "df3573d1c696fbd0479c044049b5e3a0"; };

  };

  class PlanningResponse : public ros::Msg
  {
    public:
      uint32_t plans_length;
      typedef planning_msgs::Plan _plans_type;
      _plans_type st_plans;
      _plans_type * plans;
      uint32_t unused_bindings_length;
      typedef char* _unused_bindings_type;
      _unused_bindings_type st_unused_bindings;
      _unused_bindings_type * unused_bindings;

    PlanningResponse():
      plans_length(0), plans(NULL),
      unused_bindings_length(0), unused_bindings(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->plans_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->plans_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->plans_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->plans_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->plans_length);
      for( uint32_t i = 0; i < plans_length; i++){
      offset += this->plans[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->unused_bindings_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->unused_bindings_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->unused_bindings_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->unused_bindings_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->unused_bindings_length);
      for( uint32_t i = 0; i < unused_bindings_length; i++){
      uint32_t length_unused_bindingsi = strlen(this->unused_bindings[i]);
      varToArr(outbuffer + offset, length_unused_bindingsi);
      offset += 4;
      memcpy(outbuffer + offset, this->unused_bindings[i], length_unused_bindingsi);
      offset += length_unused_bindingsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t plans_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      plans_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      plans_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      plans_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->plans_length);
      if(plans_lengthT > plans_length)
        this->plans = (planning_msgs::Plan*)realloc(this->plans, plans_lengthT * sizeof(planning_msgs::Plan));
      plans_length = plans_lengthT;
      for( uint32_t i = 0; i < plans_length; i++){
      offset += this->st_plans.deserialize(inbuffer + offset);
        memcpy( &(this->plans[i]), &(this->st_plans), sizeof(planning_msgs::Plan));
      }
      uint32_t unused_bindings_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      unused_bindings_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      unused_bindings_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      unused_bindings_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->unused_bindings_length);
      if(unused_bindings_lengthT > unused_bindings_length)
        this->unused_bindings = (char**)realloc(this->unused_bindings, unused_bindings_lengthT * sizeof(char*));
      unused_bindings_length = unused_bindings_lengthT;
      for( uint32_t i = 0; i < unused_bindings_length; i++){
      uint32_t length_st_unused_bindings;
      arrToVar(length_st_unused_bindings, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_unused_bindings; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_unused_bindings-1]=0;
      this->st_unused_bindings = (char *)(inbuffer + offset-1);
      offset += length_st_unused_bindings;
        memcpy( &(this->unused_bindings[i]), &(this->st_unused_bindings), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return PLANNING; };
    const char * getMD5(){ return "6dbce147047db5e837c94aabe63a5256"; };

  };

  class Planning {
    public:
    typedef PlanningRequest Request;
    typedef PlanningResponse Response;
  };

}
#endif
