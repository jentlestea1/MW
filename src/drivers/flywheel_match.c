#include "flywheel_match.h"
#include "flywheel.h"
#include "fill_command_sequence.h"
#include "fill_bytes_array_assembly_scheme.h"
#include "collect_code_block.h"
//#include "config_info_collect.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
 
//将具体的匹配方法分割开来
static int global_match(void){ return MATCH; }
static int open_match_template0(void) { return MATCH; }


static int set_speed_match_template0(void)
{
   static struct command_sequence* set_speed_data_template0;

   int exec_status;

   set_speed_data_template0 = malloc(sizeof(struct command_sequence));

   exec_status = fill_command_sequence("flywheel_set_speed", 
                                       "flywheel_set_speed_template0",
                                        set_speed_data_template0);
 
   collect_code_block("flywheel_set_speed",
                      "compute_function",
                       GROUP,
                       set_speed_data_template0->compute_funcs); 
  

   // TODO 后面有时间的话将check_match重构一下
   return check_match(exec_status,
                      FLYWHEEL_SET_SPEED_INDEX,
                      0, //template_id 
                      (void*)set_speed_data_template0);
}


static int receive_match_template0(void)
{
    struct bytes_array_assembly_scheme* receive_data_template0;
    int exec_status;

    receive_data_template0 = malloc(sizeof(struct bytes_array_assembly_scheme));

    exec_status = fill_bytes_array_assembly_scheme("flywheel_receive", 
                                                   "flywheel_receive_template0",
                                                    receive_data_template0);
    
    collect_code_block("flywheel_receive",
                       "postprocess_function",
                        GROUP,
                        receive_data_template0->postprocess_funcs); 

    collect_code_block("flywheel_receive",
                       "precondition",
                        SINGLE,
                        receive_data_template0->precondition); 

    //返回不匹配或者匹配
    return check_match(exec_status, FLYWHEEL_RECEIVE_INDEX, 0, 
                                    (void*)receive_data_template0);
}


//模板匹配函数表
//作为一个整体存在
static struct template_match match_funcs_table[FLYWHEEL_TEMPLATE_NUM] = {
    {"global", global_match},
    {"flywheel_open_template0", open_match_template0},
    {"flywheel_set_speed_template0", set_speed_match_template0},
    {"flywheel_receive_template0", receive_match_template0},

    //
    //下一个模板号的匹配函数写在下面
    //
    //
    //
}; 


//整体的一个配置
static struct match_info flywheel_match_info = {
   (FLYWHEEL_OP_NUM+1),
   match_funcs_table,
   MATCH_FUNCS_NUM,
   NULL,
   NULL
};


int flywheel_match(void)
{
    return  do_match(&flywheel_match_info);
}