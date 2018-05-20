#ifndef ROUTE_MAP_H_
#define ROUTE_MAP_H_
#include "m_type.h"
#include "handle_data_package.h"
typedef struct route{
    char *bus_type;
    char *bus_lid;
    char *RT_lid;
}route;
char* get_route_bus_type(route r);
char* get_route_bus_lid(route r);
char* get_route_RT_lid(route r);
void get_RT_route_map(char* RT_lid,route *r);
void get_dev_route_map(char* dev_lid,route *r);
#endif
