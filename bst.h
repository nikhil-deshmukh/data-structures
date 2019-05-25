#include "types.h"

#ifndef __BST_H__
#define __BST_H__

typedef compare_t (*bst_nodecmp)(void *p_refdata, void *p_cmpdata);

typedef void (*bst_node_accessed)(void *p_data);

typedef struct sBst bst_t;

bst_t * bst_create(bst_nodecmp fp_nodecmp);

void bst_delete();

bool_t bst_insert(bst_t *p_bst, void *p_data);

bool_t bst_remove(bst_t *p_bst, void *p_data, bst_node_accessed fp_node_deleted);

void bst_traverse_inorder_rec(bst_t *p_bst, bst_node_accessed fp_node_accessed);

void bst_traverse_inorder_itr(bst_t *p_bst, bst_node_accessed fp_node_accessed);

void bst_traverse_preorder_rec(bst_t *p_bst, bst_node_accessed fp_node_accessed);

void bst_traverse_preorder_itr(bst_t *p_bst, bst_node_accessed fp_node_accessed);

void bst_traverse_postorder_rec(bst_t *p_bst, bst_node_accessed fp_node_accessed);

void bst_traverse_postorder_itr(bst_t *p_bst, bst_node_accessed fp_node_accessed);

int32_t bst_height(bst_t *p_bst);

#endif /* __BST_H__ */
