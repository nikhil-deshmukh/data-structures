#include <stdlib.h>
#include "stack.h"
#include "sll.h"

struct sStack
{
   sll_t *p_list;
};

stack_t *
stack_create()
{
   stack_t  *p_stack = (stack_t *) malloc(sizeof (stack_t));

   if (p_stack)
   {
      p_stack->p_list = sll_create();

      if (NULL == p_stack->p_list)
      {
         /* ERROR */

         free(p_stack);
         p_stack = NULL;
      }
      /* No else */
   }
   /* No else */

   return p_stack;
}

void
stack_delete(stack_t *p_stack)
{
   if (p_stack)
   {
      /* Delete the list */
      sll_delete(p_stack->p_list);

      /* Delete the stack */
      free(p_stack);
   }
   /* No else */
}

bool_t
stack_push(stack_t *p_stack, void *p_data)
{
   bool_t   b_ret = TRUE;

   if (  (NULL == p_stack)
      || (NULL == p_data)
      )
   {
      /* ERROR */

      b_ret = FALSE;
   }
   else
   {
      b_ret = sll_insert_at_head(p_stack->p_list, p_data);
   }

   return b_ret;
}

void *
stack_pop(stack_t *p_stack)
{
   void  *p_data = NULL;

   if (p_stack)
   {
      p_data = sll_remove_from_head(p_stack->p_list);
   }
   /* No else */

   return p_data;
}
