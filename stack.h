#include "types.h"

#ifndef __STACK_H__
#define __STACK_H__

typedef struct sStack stack_t;

stack_t * stack_create();

void stack_delete(stack_t *p_stack);

bool_t stack_push(stack_t *p_stack, void *p_data);

void * stack_pop(stack_t *p_stack);

#endif /* __STACK_H__ */
