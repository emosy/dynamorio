#include "dr_api.h"
#include "drmgr.h"
#include "syscall.h"

static void event_exit();
static void event_post_syscall(void *drcontext, int sysnum);
static bool event_pre_syscall(void *drcontext, int sysnum);
