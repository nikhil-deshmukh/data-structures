#include <stdlib.h>
#include "bst.h"
#include "stack.h"

typedef struct sTreeNode
{
   void              *p_data;
   struct sTreeNode  *p_left;
   struct sTreeNode  *p_right;
} treenode_t;

struct sBst
{
   bst_nodecmp fp_nodecmp;
   treenode_t  *p_root;
};

static treenode_t *
bst_create_node(void *p_data)
{
   treenode_t  *p_node = (treenode_t *) malloc(sizeof (treenode_t));

   if (p_node)
   {
      p_node->p_data = p_data;
      p_node->p_left = NULL;
      p_node->p_right = NULL;
   }
   /* No else */

   return p_node;
}

static void
bst_delete_node(treenode_t *p_node)
{
   if (p_node)
   {
      p_node->p_data = NULL;
      p_node->p_left = NULL;
      p_node->p_right = NULL;
      free(p_node);
   }
   /* No else */
}

static void
bst_inorder_recursive(treenode_t *p_node, bst_node_accessed fp_node_accessed)
{
   if (p_node && fp_node_accessed)
   {
      bst_inorder_recursive(p_node->p_left, fp_node_accessed);
      fp_node_accessed(p_node->p_data);
      bst_inorder_recursive(p_node->p_right, fp_node_accessed);
   }
   /* No else */
}

static void
bst_preorder_recursive(treenode_t *p_node, bst_node_accessed fp_node_accessed)
{
   if (p_node && fp_node_accessed)
   {
      fp_node_accessed(p_node->p_data);
      bst_preorder_recursive(p_node->p_left, fp_node_accessed);
      bst_preorder_recursive(p_node->p_right, fp_node_accessed);
   }
   /* No else */
}

static void
bst_postorder_recursive(treenode_t *p_node, bst_node_accessed fp_node_accessed)
{
   if (p_node && fp_node_accessed)
   {
      bst_postorder_recursive(p_node->p_left, fp_node_accessed);
      bst_postorder_recursive(p_node->p_right, fp_node_accessed);
      fp_node_accessed(p_node->p_data);
   }
   /* No else */
}

static int32_t
bst_subtree_height(treenode_t *p_node)
{
   int32_t   height = 0;
   int32_t   tmp = 0;
   stack_t  *p_stack = NULL;
   void     *p_tmp = NULL;

   /* Any tree traversal algorithm will do. Pre-order chosen here */

   if (p_node)
   {
      /* Create the stack */
      p_stack = stack_create();

      if (p_stack)
      {
         while (p_node)
         {
            if (height == tmp++)
            {
               height = tmp;
            }
            /* No else */

            /* Store right child on stack */
            if (TRUE == stack_push(p_stack, p_node->p_right))
            {
               /* Store current height */
               stack_push(p_stack, (void *) (tmp));
            }

            /* Go to left child if available, else pop off stack */
            if (p_node->p_left)
            {
               p_node = p_node->p_left;
            }
            else
            {
               /* Restore saved height */
               if (p_tmp = (int32_t) stack_pop(p_stack))
               {
                  tmp = (size_t) p_tmp;

                  /* Restore right child */
                  p_tmp = stack_pop(p_stack);
               }
               /* No else */

               /* Restore right child */
               p_node = (treenode_t *) p_tmp;
            }
         }

         /* Delete the stack */
         stack_delete(p_stack);
      }
      /* No else */
   }
   /* No else */

   return height - 1;
}

static bool_t
bst_subtree_is_balanced(treenode_t *p_node)
{
   bool_t   b_ret = TRUE;
   int32_t  balance_factor = 0;

   if (p_node)
   {
      /* Calculate the balance factor */
      balance_factor = bst_subtree_height(p_node->p_left) - bst_subtree_height(p_node->p_right);

      if (  (1 < balance_factor)
         || (-1 >  balance_factor)
         )
      {
         /* Subtree unbalanced */

         b_ret = FALSE;
      }
      /* No else */
   }
   /* No else */

   return b_ret;
}

bst_t *
bst_create(bst_nodecmp fp_nodecmp)
{
   bst_t *p_bst = NULL;

   if (fp_nodecmp)
   {
      p_bst = (bst_t *) malloc(sizeof (bst_t));

      if (p_bst)
      {
         p_bst->fp_nodecmp = fp_nodecmp;
         p_bst->p_root = NULL;
      }
      /* No else */
   }
   /* No else */

   return p_bst;
}

void
bst_delete()
{
   /* TBD */
}

bool_t
bst_insert(bst_t *p_bst, void *p_data)
{
   bool_t      b_ret = TRUE;
   treenode_t  *p_temp = NULL;
   treenode_t  *p_node = NULL;
   compare_t   cmp_result = CMP_INVALID;

   /* Validate the arguments */
   if (  (NULL == p_bst)
      || (NULL == p_bst->fp_nodecmp)
      || (NULL == p_data)
      )
   {
      /* ERROR */

      b_ret = FALSE;
   }
   else
   {
      /* Create a node */
      p_node = bst_create_node(p_data);

      if (p_node)
      {
         if (NULL == p_bst->p_root)
         {
            /* Root is empty */

            p_bst->p_root = p_node;
         }
         else
         {
            /* Intialise current node pointer */
            p_temp = p_bst->p_root;

            while (TRUE)
            {
               cmp_result = p_bst->fp_nodecmp(p_temp->p_data, p_node->p_data);

               if (CMP_LESSER == cmp_result)
               {
                  /* Check the left child */

                  if (NULL == p_temp->p_left)
                  {
                     /* Reached leaf node */

                     p_temp->p_left = p_node;
                     break;
                  }
                  else
                  {
                     p_temp = p_temp->p_left;
                  }
               }
               else if (CMP_GREATER == cmp_result)
               {
                  /* Check the right child */

                  if (NULL == p_temp->p_right)
                  {
                     /* Reached leaf node */

                     p_temp->p_right = p_node;
                     break;
                  }
                  else
                  {
                     p_temp = p_temp->p_right;
                  }
               }
               else
               {
                  /* ERROR */

                  b_ret = FALSE;

                  /* Delete the node */
                  bst_delete_node(p_node);

                  break;
               }
            }  /* End of loop */
         }
      }
      /* No else */
   }

   return b_ret;
}

bool_t
bst_remove(bst_t *p_bst, void *p_data, bst_node_accessed fp_node_deleted)
{
   bool_t      b_ret = TRUE;
   treenode_t  *p_delnode = NULL;
   treenode_t  *p_parent_delnode = NULL;
   treenode_t  *p_currnode = NULL;
   treenode_t  *p_parent_currnode = NULL;
   compare_t   cmp_result = CMP_INVALID;
   compare_t   prev_cmp_result = CMP_INVALID;

   /* Validate the arguments */
   if (  (NULL == p_bst)
      || (NULL == p_bst->fp_nodecmp)
      || (NULL == p_data)
      )
   {
      /* ERROR */

      b_ret = FALSE;
   }
   else
   {
      /* Initialise current node pointer and its parent */
      p_currnode = p_bst->p_root;

      while (p_currnode)
      {
         cmp_result = p_bst->fp_nodecmp(p_currnode->p_data, p_data);

         if (CMP_LESSER == cmp_result)
         {
            /* Store last compare result */
            prev_cmp_result = CMP_LESSER;

            /* Check left child */
            p_parent_currnode = p_currnode;
            p_currnode = p_currnode->p_left;
         }
         else if (CMP_GREATER == cmp_result)
         {
            /* Store last compare result */
            prev_cmp_result = CMP_GREATER;

            /* Check right child */
            p_parent_currnode = p_currnode;
            p_currnode = p_currnode->p_right;
         }
         else if (CMP_EQUAL == cmp_result)
         {
            /* Match found */

            break;
         }
      }  /* End of loop */

      if (NULL == p_currnode)
      {
         /* Element not found */

         b_ret = FALSE;
      }
      else
      {
         /* Save pointer to node to be deleted and its parent */
         p_delnode = p_currnode;
         p_parent_delnode = p_parent_currnode;

         /* Check sub-trees of node to be deleted */
         if ((NULL == p_delnode->p_left) && (NULL == p_delnode->p_right))
         {
            /* Node to be deleted is leaf */

            p_currnode = NULL;
         }
         else if ((NULL != p_delnode->p_left) && (NULL == p_delnode->p_right))
         {
            /* Node to be deleted has only left sub-tree */

            p_currnode = p_delnode->p_left;
         }
         else if ((NULL == p_delnode->p_left) && (NULL != p_delnode->p_right))
         {
            /* Node to be deleted has only right sub-tree */

            p_currnode = p_delnode->p_right;
         }
         else
         {
            /* Node to be deleted has both sub-trees */

            /* Initialise current node pointer and its parent */
            p_currnode = p_delnode->p_right;
            p_parent_currnode = p_delnode;

            /* Determine in-order successor */
            while (p_currnode->p_left)
            {
               p_parent_currnode = p_currnode;
               p_currnode = p_currnode->p_left;
            }

            /* Reassign left sub-tree of node to be deleted */
             p_currnode->p_left = p_delnode->p_left;

            if (p_delnode != p_parent_currnode)
            {
               /* Reassign right sub-tree of in-order successor */
               p_parent_currnode->p_left = p_currnode->p_right;

               /* Reassign right sub-tree of node to be deleted */
               p_currnode->p_right = p_delnode->p_right;
            }
            /* No else */
         }

         /* Delete the node */
         if (TRUE == b_ret)
         {
            if (CMP_LESSER == prev_cmp_result)
            {
               /* Node to be deleted is left child of parent */

               p_parent_delnode->p_left = p_currnode;
            }
            else if (CMP_GREATER == prev_cmp_result)
            {
               /* Node to be deleted is right child of parent */

               p_parent_delnode->p_right = p_currnode;
            }
            else if (CMP_INVALID == prev_cmp_result)
            {
               /* Node to be deleted is present root */

               p_bst->p_root = p_currnode;
            }
            else
            {
               /* ERROR */

               b_ret = FALSE;
            }

            /* Application callback */
            if (fp_node_deleted)
            {
               fp_node_deleted(p_delnode->p_data);
            }
            /* No else */

            bst_delete_node(p_delnode);
            p_delnode = NULL;
         }
         /* No else */
      }
   }

   return b_ret;
}

void
bst_traverse_inorder_rec(bst_t *p_bst, bst_node_accessed fp_node_accessed)
{
   if (p_bst && fp_node_accessed)
   {
      bst_inorder_recursive(p_bst->p_root, fp_node_accessed);
   }
   /* No else */
}

void
bst_traverse_inorder_itr(bst_t *p_bst, bst_node_accessed fp_node_accessed)
{
   stack_t     *p_stack = NULL;
   treenode_t  *p_node = NULL;

   if (p_bst && fp_node_accessed)
   {
      /* Create the stack */
      p_stack = stack_create();

      if (p_stack)
      {
         p_node = p_bst->p_root;

         while (TRUE)
         {
            if (p_node)
            {
               /* Store current node on stack */
               stack_push(p_stack, p_node);

               /* Go to left child */
               p_node = p_node->p_left;
            }
            else
            {
               /* Retrieve node from stack */
               p_node = stack_pop(p_stack);

               if (NULL == p_node)
               {
                  /* Stack is empty */

                  break;
               }
               else
               {
                  /* Call appliations node-accessed function */
                  fp_node_accessed(p_node->p_data);

                  /* Go to right child */
                  p_node = p_node->p_right;
               }
            }
         }

         /* Delete the stack */
         stack_delete(p_stack);
      }
      /* No else */
   }
   /* No else */
}

void
bst_traverse_preorder_rec(bst_t *p_bst, bst_node_accessed fp_node_accessed)
{
   if (p_bst && fp_node_accessed)
   {
      bst_preorder_recursive(p_bst->p_root, fp_node_accessed);
   }
   /* No else */
}

void
bst_traverse_preorder_itr(bst_t *p_bst, bst_node_accessed fp_node_accessed)
{
   stack_t     *p_stack = NULL;
   treenode_t  *p_node = NULL;

   if (p_bst && fp_node_accessed)
   {
      /* Create the stack */
      p_stack = stack_create();

      if (p_stack)
      {
         p_node = p_bst->p_root;

         while (p_node)
         {
            /* Call application's node-accessed function */
            fp_node_accessed(p_node->p_data);

            /* Store right child on stack */
            stack_push(p_stack, p_node->p_right);

            /* Go to left child if available, else pop off stack */
            p_node = (p_node->p_left) ? (p_node->p_left) : (stack_pop(p_stack));
         }

         /* Delete the stack */
         stack_delete(p_stack);
      }
      /* No else */
   }
   /* No else */
}

void
bst_traverse_postorder_rec(bst_t *p_bst, bst_node_accessed fp_node_accessed)
{
   if (p_bst && fp_node_accessed)
   {
      bst_postorder_recursive(p_bst->p_root, fp_node_accessed);
   }
   /* No else */
}

void
bst_traverse_postorder_itr(bst_t *p_bst, bst_node_accessed fp_node_accessed)
{
   stack_t     *p_stack = NULL;
   treenode_t  *p_node = NULL;
   treenode_t  *p_temp = NULL;

   if (p_bst && fp_node_accessed)
   {
      /* Create the stack */
      p_stack = stack_create();

      if (p_stack)
      {
         p_node = p_bst->p_root;

         while (TRUE)
         {
            if (p_node)
            {
               /* Store current node on stack */
               stack_push(p_stack, p_node);

               /* Go to left child */
               p_node = p_node->p_left;
            }
            else
            {
               p_temp = NULL;

               while (p_node = stack_pop(p_stack))
               {
                  if (  (p_node)
                     && (p_temp != p_node->p_right)
                     )
                  {
                     /* Push current node on stack again */
                     stack_push(p_stack, p_node);

                     /* Go to right child */
                     p_node = p_node->p_right;

                     break;
                  }
                  /* No else */

                  /* Call application's node-accessed function */
                  fp_node_accessed(p_node->p_data);

                  /* Save pointer to current node */
                  p_temp = p_node;
               }

               if (NULL == p_node)
               {
                  break;
               }
               /* No else */
            }
         }

         /* Delete the stack */
         stack_delete(p_stack);
      }
      /* No else */
   }
   /* No else */
}

int32_t
bst_height(bst_t *p_bst)
{
   int32_t  height = 0;

   if (p_bst)
   {
      height = bst_subtree_height(p_bst->p_root);
   }
   /* No else */

   return height;
}
