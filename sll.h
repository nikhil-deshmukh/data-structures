#include "types.h"

#ifndef __SLL_H__
#define __SLL_H__

typedef struct sSllNode sllnode_t;

typedef struct sSll sll_t;

sll_t * sll_create();

void sll_delete(sll_t *p_list);

bool_t sll_insert_at_head(sll_t *p_sll, void *p_data);

void * sll_remove_from_head(sll_t *p_sll);

#endif /* __SLL_H__ */
