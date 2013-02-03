#include <stdio.h>
#include "defer.h"

int main() {
    FILE *fp = NULL;
    fp = fopen("main.c", "r");
    if (!fp) return;

    defer(fclose, fp);
    return 0;
}

