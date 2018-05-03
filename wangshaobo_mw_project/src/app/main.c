#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "manage_transport_center.h"
#include "app.h"
#include "RT_socket.h"
#include "file.h"
int main(){
    init_vi_dev_visit_sys();
    app_read();
    while(1)
        sleep(100000);
}
