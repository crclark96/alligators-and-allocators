#include <unistd.h>

int main() {
    int t;
    print("hello\n");
    print_addr(&t);
    t = sizeof(t);
    print("\n");
    print_addr(t);
    print("\n");
}
