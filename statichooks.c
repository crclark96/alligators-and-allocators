#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/auxv.h>
#include "utils.h"

static uint32_t patch_offset = 0x11e1;
static uint32_t entry_offset = 0x10a0;

void __cxa_finalize(void *p) {
    void *epoint = (void*)getauxval(AT_ENTRY);
    debug("[.] got entry point: 0x");
#ifndef DEBUG
    print_addr(epoint);
    debug("\n");
    print("[.] calculated base address:   0x");
    print_addr(epoint - entry_offset);
    print("\n");
#endif
    void *base_addr = epoint - entry_offset;

    debug("[+] __cxa_finalize called at:  0x");
    void *caller = __builtin_return_address(0);
#ifndef DEBUG
    print_addr(caller);
    print("\n");
#endif
    if (caller == base_addr + patch_offset + 5) {
        print("hello from static hooking lib\n");
    } else {
        void (*__cxa_finalize_original)(void *p) = dlsym(RTLD_NEXT, "__cxa_finalize");
        if (NULL == __cxa_finalize_original) {
            fail("[!] error locating original __cxa_finalize symbol\n");
        }
        __cxa_finalize_original(p);
    }
}
