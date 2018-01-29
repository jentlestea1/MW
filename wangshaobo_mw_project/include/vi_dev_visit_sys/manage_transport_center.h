#ifndef MANAGE_TRANSPORT_CENTER_H_
#define MANAGE_TRANSPORT_CENTER_H_
#include "m_type.h"
#include "control_data_stream.h"
/*
 * 初始化内容：初始化文件解析存储结构，初始化包转发规则表，初始化索引表及转存区域,初始化事件库及扫描线程,
 * 初始化1553配置(包含初始化交通灯库)，创建交通灯库扫描线程，创建所有的1553的RT_section的扫描线程，初始化
 * 所有1553b与RT的socket通信端口。
 */
void init_vi_dev_visit_sys(void); 

/*
 *以下为主控层封装的数据接口和控制接口
 *前两个分别是应用层的读和写数据接口，
 *vi_set_bus_enable和vi_set_bus_disable
 *分别是激活所选总线和使所选总线失效，
 *vi_set_RT_enable和vi_set_RT_disable
 *分别是对RT激活和禁用。
 *
 */
void vi_app_read_data(char* dev_lid,unsigned char* buffer,UINT buffer_size,UINT*size,void* time,AUTO_SET auto_set,UINT set_size);
void vi_app_write_data(char* dev_lid,unsigned char* buffer,UINT buffer_size,UINT* size);
void vi_set_bus_enable(char* bus_lid);
void vi_set_bus_disable(char* bus_lid);
void vi_set_RT_enable(char* bus_lid,char* RT_lid);
void vi_set_RT_disable(char* bus_lid,char* RT_lid);
#endif
