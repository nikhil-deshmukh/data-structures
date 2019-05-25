#ifndef __TYPES_H__
#define __TYPES_H__

#define PRINT_ARRAY(arr, conv) do\
                              {\
                                 int   i = 0;\
                                 printf("The array " #arr " is:\n");\
                                 for (i = 0; i < ((sizeof (arr)) / (sizeof (arr[0]))); i++)\
                                 {\
                                    printf(conv, arr[i]);\
                                 }\
                                 putchar('\n');\
                              } while (0)

typedef enum eBool
{
   FALSE = 0,
   TRUE
} bool_t;

typedef enum eCompare
{
   CMP_LESSER = -1,
   CMP_EQUAL,
   CMP_GREATER,
   CMP_INVALID
} compare_t;

#endif /* __TYPES_H__ */
