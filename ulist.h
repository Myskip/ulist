#ifndef __LIST_UTILS_H__
#define __LIST_UTILS_H__

#ifndef TRUE 
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef SUCESS
#define SUCCESS (0)
#endif

#ifndef ERROR
#define ERROR (-1)
#endif

#define SAFE_FREE(obj)   do{ if(obj) { free(obj); obj = NULL; } }while(0)

typedef struct _LIST_NODE
{
    void *obj;
    unsigned int len;
    struct _LIST_NODE *prev;
    struct _LIST_NODE *next;
}LIST_NODE;

typedef struct
{
    LIST_NODE *head;
    LIST_NODE *tail;
    unsigned int size;
}LIST;

typedef enum _ulist_error
{
    ULIST_ERROR_OBJ_NOT_FOUND = 0x01000001,
}ULIST_ERROR_E;

#define FOR_EACH_NODE(node, list) for(LIST_NODE *node = list->head->next; node != list->tail; node=node->next)
#define LIST_FIRST(list) (list->head->next)
#define LIST_LAST(list) (list->tail->prev)
#define LIST_SIZE(list) (list->size)
#define LIST_NODE_OBJ(node) (node->obj)
#define LIST_NODE_OBJ_LEN(node) (node->len)

/* create a ulist object, return NULL is create failed */
LIST* ulist_new();
int ulist_destroy(LIST *list);
int ulist_add(LIST *list, void *obj, unsigned int obj_len);
int ulist_remove(LIST *list, void *obj);
#endif