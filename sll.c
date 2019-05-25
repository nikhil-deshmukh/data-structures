#include <stdlib.h>
#include "sll.h"

struct sSllNode
{
   void              *p_data;
   struct sSllNode   *p_next;
};

struct sSll
{
   sllnode_t   *p_head;
};

static sllnode_t *
sll_create_node(void *p_data)
{
   sllnode_t   *p_node = (sllnode_t *) malloc(sizeof (sllnode_t));

   if (p_node)
   {
      p_node->p_data = p_data;
      p_node->p_next = NULL;
   }
   /* No else */

   return p_node;
}

static void
sll_delete_node(sllnode_t *p_node)
{
   if (p_node)
   {
      p_node->p_data = NULL;
      p_node->p_next = NULL;
      free(p_node);
   }
   /* No else */
}

sll_t *
sll_create()
{
   sll_t *p_list = (sll_t *) malloc(sizeof (sll_t));

   if (p_list)
   {
      p_list->p_head = NULL;
   }
   /* No else */

   return p_list;
}

void
sll_delete(sll_t *p_list)
{
   if (p_list)
   {
      /* Remove all elements from the list */
      while (sll_remove_from_head(p_list));

      /* Delete the list */
      free(p_list);
   }
   /* No else */
}

bool_t
sll_insert_at_head(sll_t *p_sll, void *p_data)
{
   bool_t      b_ret = TRUE;
   sllnode_t   *p_sllnode = NULL;

   if (  (NULL == p_sll)
      || (NULL == p_data)
      )
   {
      /* ERROR */

      b_ret = FALSE;
   }
   else
   {
      p_sllnode = sll_create_node(p_data);

      if (NULL == p_sllnode)
      {
         /* ERROR */

         b_ret = FALSE;
      }
      else
      {
         if (NULL == p_sll->p_head)
         {
            p_sll->p_head = p_sllnode;
         }
         else
         {
            p_sllnode->p_next = p_sll->p_head;
            p_sll->p_head = p_sllnode;
         }
      }
   }

   return b_ret;
}

void *
sll_remove_from_head(sll_t *p_sll)
{
   void        *p_data = NULL;
   sllnode_t   *p_delnode = NULL;

   if (  (p_sll)
      && (p_sll->p_head)
      )
   {
      /* Save pointer to node to be deleted */
      p_delnode = p_sll->p_head;

      /* Save pointer to data of node to be deleted */
      p_data = p_sll->p_head->p_data;

      /* Make next node the head */
      p_sll->p_head = p_delnode->p_next;

      /* Delete the node */
      sll_delete_node(p_delnode);
   }
   /* No else */

   return p_data;
}
