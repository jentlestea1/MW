/*
 *control_traffic_light.h,声明操作交通灯数据结构的各种操作函数。
 */
#ifndef CONTROL_TRAFFIC_LIGHT_H_
#define CONTROL_TRAFFIC_LIGHT_H_
#include "m_type.h"
#include "traffic_light.h"
#define TRAFFIC_REPOS_ARRAY_MAX_LEN 10
void* get_traffic_repos_node(UINT traffic_repos_id);
UINT  config_traffic_repos(char* bus_type,char* bus_lid);
void config_traffic(void);
void  traffic_repos_scan_func(UINT traffic_repos_id);
void* traffic_repos_scan_pthread_func(void* argc);
void create_traffic_repos_scan_unit(void);
void  set_traffic_light(UINT traffic_repos_id,UINT light_pos,TRAFFIC_STATUS traffic_status,IS_LOADED is_loaded,IS_BACK is_back);

void set_traffic_repos_disable(UINT traffic_repos_id);
void set_traffic_repos_enable(UINT traffic_repos_id);
void set_traffic_light_list_enable(UINT traffic_repos_id,UINT light_pos);
void set_traffic_light_list_disable(UINT traffic_repos_id,UINT light_pos);
UINT get_dev_light_pos(UINT traffic_repos_id,char* dev_lid);
UINT get_light_pos(UINT traffic_repos_id,char* RT_lid);
void reset_traffic_repos_light(UINT traffic_repos_id,UINT light_pos);
bool is_RT_section_readable(UINT traffic_repos_id,UINT light_pos);
bool is_RT_section_writeable(UINT traffic_repos_id,UINT light_pos);
bool is_dev_readable(UINT traffic_repos_id,UINT light_pos,UINT dev_pos);
bool is_red_light(UINT traffic_repos_id,UINT light_pos,char* dev_lid);
UINT scan_RT_section(UINT traffic_repos_id);
//UINT get_traffic_repos_list_len(UINT traffic_repos_id);
UINT get_scan_pos(UINT traffic_repos_id);
//char* get_light_dev_lid_t(UINT traffic_repos_id,UINT light_pos,UINT dev_pos);
char* get_RT_section_RT_lid(UINT traffic_repos_id,UINT light_pos);
#endif
