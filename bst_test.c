#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

compare_t
compare_items(void *p_refdata, void *p_cmpdata)
{
   int   refdata = *((int *) p_refdata);
   int   cmpdata = *((int *) p_cmpdata);

   if (cmpdata < refdata)
      return CMP_LESSER;
   else if (cmpdata > refdata)
      return CMP_GREATER;
   else
      return CMP_EQUAL;
}

void
node_accessed(void *p_data)
{
   printf("%d ", *((int *) p_data));
}

void
node_deleted(void *p_data)
{
   printf("Removed data element \'%d\'\n", *((int *) p_data));
   free(p_data);
}

void menu_bst_ops(bst_t *p_bst)
{
   int   choice = 0;
   int   data_element = 0;
   int   *p_data = NULL;

   do
   {
      fflush(stdin);
      putchar('\n');
      printf(  "1. Insert elements (integers only) \n"
               "2. Remove elements (integers only)\n"
               "3. In-order traversal (Recursive)\n"
               "4. In-order traversal (Iterative)\n"
               "5. Pre-order traversal (Recursive)\n"
               "6. Pre-order traversal (Iterative)\n"
               "7. Post-order traversal (Recursive)\n"
               "8. Post-order traversal (Iterative)\n"
               "9. Height\n"
               "Please enter choice or 'x' to exit: ");
      choice = getchar();
      if (('x' == choice) || ('X' == choice))
      {
         break;
      }
      else
      {
         ungetc(choice, stdin);
      }

      scanf("%d", &choice);
      fflush(stdin);

      switch (choice)
      {
         case 1:
            {
               printf("Enter the elements: ");
               fflush(stdout);
               while (EOF != scanf("%d", &data_element))
               {
                  p_data = malloc(sizeof (int));
                  *p_data = data_element;
                  bst_insert(p_bst, p_data);
               }
               break;
            }

         case 2:
            {
               printf("\nEnter the elements to be deleted: ");
               fflush(stdout);
               while (EOF != scanf("%d", &data_element))
               {
                  bst_remove(p_bst, &data_element, node_deleted);
               }
               break;
            }

         case 3:
            {
               printf("\nThe in-order traversal is: ");
               fflush(stdout);
               bst_traverse_inorder_rec(p_bst, node_accessed);
               putchar('\n');
               break;
            }

         case 4:
            {
               printf("\nThe in-order traversal is: ");
               fflush(stdout);
               bst_traverse_inorder_itr(p_bst, node_accessed);
               putchar('\n');
               break;
            }

         case 5:
            {
               printf("\nThe pre-order traversal is: ");
               fflush(stdout);
               bst_traverse_preorder_rec(p_bst, node_accessed);
               putchar('\n');
               break;
            }

         case 6:
            {
               printf("\nThe pre-order traversal is: ");
               fflush(stdout);
               bst_traverse_preorder_itr(p_bst, node_accessed);
               putchar('\n');
               break;
            }

         case 7:
            {
               printf("\nThe post-order traversal is: ");
               fflush(stdout);
               bst_traverse_postorder_rec(p_bst, node_accessed);
               putchar('\n');
               break;
            }

         case 8:
            {
               printf("\nThe post-order traversal is: ");
               fflush(stdout);
               bst_traverse_postorder_itr(p_bst, node_accessed);
               putchar('\n');
               break;
            }

         case 9:
            {
               printf("\nThe height of the tree is: %d\n", bst_height(p_bst));
               break;
            }

         default:
            {
               break;
            }
      }
   } while (('x' != choice) && ('X' != choice));
}

int
main()
{
   bst_t *p_bst = bst_create(compare_items);

   if (p_bst)
   {
      menu_bst_ops(p_bst);
   }
   /* No else */

   return 0;
}
