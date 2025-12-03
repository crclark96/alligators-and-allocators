#include <unistd.h>
#include <stdlib.h>

void hello(int num) {
    int i = 0;
    for (;i<num;i++) {
        write(1, "hello\n", 6);
    }
}

int main(int argc, char** argv) {
    hello(2);
    void *p = malloc(512);
    free(p);
}

