#include "ryanclient.h"

DR_EXPORT void
dr_client_main(client_id_t id, int argc, const char *argv[]) {
    drmgr_init();
    dr_register_exit_event(event_exit);
    drmgr_register_post_syscall_event(event_post_syscall);
    drmgr_register_pre_syscall_event(event_pre_syscall);
}

static void event_exit() {
    drmgr_exit();
}

static void event_post_syscall(void *drcontext, int sysnum) {
    reg_t result = dr_syscall_get_result(drcontext);
    dr_printf("syscall %d returned %d\n", sysnum, result);
}

static bool event_pre_syscall(void *drcontext, int sysnum) {
    if (sysnum == SYS_write && 
        dr_syscall_get_param(drcontext, 0) == (reg_t)STDERR)
        {
            dr_syscall_set_result(drcontext, 0);
            dr_printf("skip syscall %d\n", sysnum);
            return false;
        }
    return true;
    
    // dr_printf("pre syscall %d\n", sysnum);
    // return true;
}