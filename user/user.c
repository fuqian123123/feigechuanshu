#include "user.h"

static IPMSG_USER* ul_head_addr;
static IPMSG_USER* ul_cur_addr;

void userlist_init(void){
    ul_head_addr = uListInit();
    ul_cur_addr = ul_head_addr;
    
}
void userlist_print(void){

}