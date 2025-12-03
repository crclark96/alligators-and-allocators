#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdint.h>
#include "utils.h"


__attribute__((constructor))
void library_init(void) {
    print("[.] allocator.so loaded\n");
}

__attribute__((destructor))
void library_fini(void) {
    print("[.] allocator.so unloaded\n");
}

void *malloc(size_t size) {
    void *ret = NULL;
    debug("[+] malloc called at:    0x");
    void *caller = __builtin_return_address(0);
#ifndef DEBUG
    print_addr(caller);
    print("\n");
#endif
    void *(*_malloc)(size_t size) = dlsym(RTLD_NEXT, "malloc");

    if (NULL == _malloc) {
        fail("[!] error locating original malloc symbol\n");
    }

    ret = _malloc(size);

    if (NULL == ret) {
        fail("[!] _malloc failed\n");
    }
    return ret;
}

void free(void *ptr) {
    debug("[+] free called at:      0x");
    void *caller = __builtin_return_address(0);
#ifndef DEBUG
    print_addr(caller);
    print("\n");
#endif
    void *(*_free)(void *ptr) = dlsym(RTLD_NEXT, "free");

    if (NULL == _free) {
      fail("[!] error locating original free symbol\n");
    }

    _free(ptr);
    return;
}
