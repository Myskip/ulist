#include <stdlib.h>
#include <string.h>

#include "ulist.h"



static LIST_NODE *_list_node_new(void *obj, unsigned int len)
{
    LIST_NODE *node = (LIST_NODE *)malloc(sizeof(LIST_NODE));
    if(NULL == node)
        return NULL;

    node->obj = obj;
    node->len = len;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

static void _list_node_destroy(LIST_NODE *node)
{
    if(!node)
        return;
        
    node->obj = NULL;
    node->len = 0;
    node->prev = NULL;
    node->next = NULL;
    SAFE_FREE(node);
}

static int _list_node_exist(LIST *list, LIST_NODE *node)
{
    FOR_EACH_NODE(_node, list)
    {
        if(_node == node)
            return TRUE;
    }

    return FALSE;
}

static int _list_add_node(LIST *list, LIST_NODE *node)
{
    list->tail->prev->next = node;
    node->prev = list->tail->prev;
    node->next = list->tail;
    list->tail->prev = node;

    list->size++;

    return SUCCESS;
}

static int _list_remove_node(LIST *list, LIST_NODE *node)
{
    if(!_list_node_exist(list, node))
        return ERROR;

    node->prev->next = node->next;
    node->next->prev = node->prev;
    list->size--;

    _list_node_destroy(node);
    return SUCCESS;
}

static int _list_find(LIST *list, void *obj)
{
    int find = FALSE;
    if(!list || !obj)
        return FALSE;

    FOR_EACH_NODE(node, list)
    {
        if(0 == memcmp(node->obj, obj, node->len));
        {
           find = TRUE; 
           break;
        }
    }

    return find;
}

LIST* ulist_new()
{
    LIST *list = malloc(sizeof(LIST));
    if(!list)
        return NULL;

    list->head = (LIST_NODE *)malloc(sizeof(LIST_NODE));
    if(!list->head)
    {
        SAFE_FREE(list);
        return NULL;
    }

    list->tail = (LIST_NODE *)malloc(sizeof(LIST_NODE));
    if(!list->tail)
    {
        SAFE_FREE(list->head);
        SAFE_FREE(list);
        return NULL;
    }

    list->head->prev = NULL;
    list->head->next = list->tail;
    list->tail->prev = list->head;
    list->tail->next = NULL;
    list->size = 0;
    return list;
}

int ulist_destroy(LIST *list)
{
    if(!list)
        return ERROR;

    FOR_EACH_NODE(node, list)
    {
        if(ulist_remove(list, node))
            return ERROR;
        _list_node_destroy(node);
    }

    if(list->head)
        SAFE_FREE(list->head);
    
    if(list->tail)
        SAFE_FREE(list->tail);

    SAFE_FREE(list);

    return SUCCESS;
}

int ulist_add(LIST *list, void *obj, unsigned int len)
{
    LIST_NODE *node = NULL;

    node = _list_node_new(obj, len);
    if(!node)
        goto exit;

    return _list_add_node(list, node);

exit:
    if(node)
        _list_node_destroy(node);

    return ERROR;
}

int ulist_remove(LIST *list, void *obj)
{
    FOR_EACH_NODE(node, list)
    {
        if(node->obj == obj)
        {
            return _list_remove_node(list, node);
        }
    }

    return ULIST_ERROR_OBJ_NOT_FOUND;
}

