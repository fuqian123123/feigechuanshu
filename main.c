#include <stdio.h>
#include <unistd.h>
#include "./util/util.h"

int main(int argc,char* argv[]){
    username_get();
    main_init();
    while(1);
    return 0;
}    
