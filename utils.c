#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void print(char *s) {
    int l = strlen(s);
    write(1, s, l);
}

void print_addr(void *ptr) {
    for (int i=0; i < (sizeof(ptr) - 2) * 2; i++) {
        char c = ((uint64_t)ptr >> (6*8-4)) & 0xf;
        if (c > 9) {
            c += 87;
        } else {
          c += 48;
        }
        write(1, &c, 1);
        ptr = (void*)((uint64_t)ptr << 4);
    }
}

void debug(char *s) {
#ifndef DEBUG
    print(s);
#endif
}

void fail(char *s) {
    print(s);
    exit(1);
}

