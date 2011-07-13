#include <stdio.h>

int main(int argc, const char *argv[]);

struct addr_name_map_t {
    unsigned int addr;
    char buf[64];
};


static void foo2() {
}

void foo1() {
    foo2();
}

void foo(){
    chdir("/export/home/baim");
    foo1();
}

struct addr_name_map_t maps[20] = {
    {(unsigned int)&main, "main"},
    {(unsigned int)&foo, "foo"},
    {(unsigned int)&foo1, "foo1"},
    {(unsigned int)&foo2, "foo2"}
};

int main(int argc, const char *argv[])
{
//    printf("main addr = %p\n", main);
//    printf("foo addr = %p\n", foo);
//    printf("foo1 addr = %p\n", foo1);
//    printf("foo2 addr = %p\n", foo2);
    foo();    
    return 0;
}
