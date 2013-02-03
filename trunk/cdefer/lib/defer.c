#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "defer.h"

extern struct defer_func_ctx ctx_stack[10];
int stack_top = 0;

void stack_push(struct defer_func_ctx *ctx) {
    if (stack_top == 10) {
        return;
    }

    ctx_stack[stack_top] = *ctx;
    stack_top++;
}

struct defer_func_ctx* stack_pop() {
    if (stack_top == 0) {
        return NULL;
    }

    stack_top--;
    return &ctx_stack[stack_top];
}

void defer(defer_func fp, ...) {
    va_list ap;
    va_list ap1; /* used to calculate the count of variant args */
    va_start(ap, fp);
    va_start(ap1, fp);

    int count = 0;

    while(va_arg(ap1, void*) != NULL) {
        count++;
    }

    struct defer_func_ctx ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.params_count = count - 1;

    if (count == 0) {
        ctx.ctx.zp.df = fp;

    } else if (count == 1) {
        ctx.ctx.op.df = fp;
        ctx.ctx.op.p1 = va_arg(ap, void*);

    } else if (count == 2) {
        ctx.ctx.tp.df = fp;
        ctx.ctx.tp.p1 = va_arg(ap, void*);
        ctx.ctx.tp.p2 = va_arg(ap, void*);
        ctx.ctx.tp.df(ctx.ctx.tp.p1, ctx.ctx.tp.p2);
    }

    stack_push(&ctx);
}

