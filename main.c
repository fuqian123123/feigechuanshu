#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./util/util.h"

int main(int argc,char* argv[]){
    my_info_init();
    username_get();
    main_init();
    while(1);
    return 0;
}    
