/* Project:     Linked List for C
 * File:        CLinkedList.c
 * Coder:       FunctionGHW
 * Version:     1.0
 * Last Change: 2013-4-26
 * Description: an implementation of CLinkedList.h, and it's a doubly linked list.
 *
 */
#include <stdlib.h>
#include <string.h>
#include "CLinkedList.h"

//Create a node for the list; Only for this implementation；
LnkLstNode* _lnklst_new_node(LinkedList* lst)
{
    if (lst == NULL || lst->header == NULL || lst->rear == NULL)
    {
        return NULL;
    }
    if (lnklst_is_pool_empty(lst))
    {
        if (lst->elemt_size < 1)
        {
            return NULL;
        }
        LnkLstNode* newnode = (LnkLstNode*)malloc(sizeof(LnkLstNode));
        if (newnode == NULL)
        {
            return NULL;
        }
        newnode->data = (BYTE*)malloc(lst->elemt_size);
        if (newnode->data != NULL)
        {
            newnode->owner = lst;
            newnode->next = NULL;
            newnode->prev = NULL;
            return newnode;
        }
        else
        {
            free(newnode);
            return NULL;
        }
    }
    LnkLstNode* tmp = lst->nodes_pool;
    if (tmp->data == NULL)
    {
        if (lst->elemt_size < 1)
        {
            return NULL;
        }
        tmp->data = (BYTE*)malloc(lst->elemt_size);
        if (tmp->data == NULL)
        {
            return NULL;
        }
    }
    lst->nodes_pool = lst->nodes_pool->next;
    lst->pool_count--;
    tmp->next = NULL;
    tmp->prev = NULL;
    tmp->owner = lst;
    return tmp;
}
//================================================

//Create a new linked list;
LinkedList* new_lnklst(const size_t elemt_size,const size_t pool_size)
{
    if (elemt_size < 1)
    {
        return NULL;
    }
    LinkedList* lst = (LinkedList*)malloc(sizeof(LinkedList));
    if (lst == NULL)
    {
        return NULL;
    }
    //此处一次分配两个LnkLstNode节点的内存, 用于header和rear;
    LnkLstNode* header = (LnkLstNode*)malloc(sizeof(LnkLstNode) << 1);
    if (header == NULL)
    {
        free(lst);
        return NULL;
    }
    //rear和header位于同一个内存块相邻的位置
    LnkLstNode* rear = header + 1;
    header->data = NULL;
    header->owner = lst;
    header->prev = NULL;
    header->next = rear;

    rear->data = NULL;
    rear->owner = lst;
    rear->prev = header;
    rear->next = NULL;

    lst->elemt_size = elemt_size;
    lst->count = 0;
    lst->pool_size = pool_size;
    lst->pool_count = 0;
    lst->nodes_pool = NULL;
    lst->header = header;
    lst->rear = rear;

    return lst;
}

//Is the list empty?;
int lnklst_is_empty(const LinkedList* lst)
{
    if (lst != NULL&& lst->header != NULL && lst->count > 0)
        return 0;
    else
        return 1;
}
//Is the nodes pool empty?;
int lnklst_is_pool_empty(const LinkedList* lst)
{
    if (lst != NULL && lst->pool_count > 0)
        return 0;
    else
        return 1;
}
//Is the nodes pool full?;
int lnklst_is_pool_full(const LinkedList* lst)
{
    if (lst != NULL && lst->pool_count < lst->pool_size)
        return 0;
    else
        return 1;
}
//Get the number of nodes actually contained in the list;
size_t lnklst_count(const LinkedList* lst)
{
    if (lst != NULL)
        return lst->count;
    else
        return 0;
}
//Get the size of element that contained in the list;
size_t lnklst_elemt_size(const LinkedList* lst)
{
    if (lst != NULL)
        return lst->elemt_size;
    else
        return 0;
}
//Get maximum number of nodes that the pool could contain;
size_t lnklst_pool_size(const LinkedList* lst)
{
    if (lst != NULL)
        return lst->pool_size;
    else
        return 0;
}
//Get the number of nodes actually contained in nodes pool;
size_t lnklst_pool_count(const LinkedList* lst)
{
    if (lst != NULL)
        return lst->pool_count;
    else
        return 0;
}

//Get the first element contained in the list;
BYTE* lnklst_first_elemt(const LinkedList* lst)
{
    if (lst->elemt_size < 1 || lnklst_is_empty(lst))
    {
        return NULL;
    }
    BYTE* tmp = (BYTE*)malloc(lst->elemt_size);
    if (tmp != NULL)
    {
        memcpy(tmp, lst->header->next->data, lst->elemt_size);
        return tmp;
    }
    else
    {
        return NULL;
    }
}
//Get the last element contained in the list;
BYTE* lnklst_last_elemt(const LinkedList* lst)
{
    if (lst->elemt_size < 1 || lnklst_is_empty(lst))
    {
        return NULL;
    }
    BYTE* tmp = (BYTE*)malloc(lst->elemt_size);
    if (tmp != NULL)
    {
        memcpy(tmp, lst->rear->prev->data, lst->elemt_size);
        return tmp;
    }
    else
    {
        return NULL;
    }
}

//Get the first node contained in the list;
LnkLstNode* lnklst_first_node(const LinkedList* lst)
{
    if ( !lnklst_is_empty(lst) )
    {
        return lst->header->next;
    }
    else
    {
        return NULL;
    }
}
//Get the last node contained in the list;
LnkLstNode* lnklst_last_node(const LinkedList* lst)
{
    if ( !lnklst_is_empty(lst) )
    {
        return lst->rear->prev;
    }
    else
    {
        return NULL;
    }
}

//Get the node contained in the list which has the specified position;
LnkLstNode* lnklst_node_at(const LinkedList* lst, size_t index)
{
    if (lnklst_is_empty(lst) || index >= lst->count)
    {
        return NULL;
    }
    LnkLstNode* node;
    if (index < (lst->count >> 1))
    {
        node = lst->header->next;
        while (index > 0)
        {
            node = node->next;
            index--;
        }
    }
    else
    {
        index = lst->count - index - 1;
        node = lst->rear->prev;
        while (index > 0)
        {
            node = node->prev;
            index--;
        }
    }
    return node;
}

//Add an element to the header of the list;
void lnklst_add_first(LinkedList* lst, const BYTE* elemt)
{
    if (elemt == NULL)
    {
        return;
    }
    LnkLstNode* node = _lnklst_new_node(lst);
    if (node == NULL)
    {
        return;
    }
    memcpy(node->data, elemt, lst->elemt_size);

    node->next = lst->header->next;
    node->prev = lst->header;
    node->prev->next = node;
    node->next->prev = node;
    lst->count++;
}
//Add an element to the rear of the list;
void lnklst_add_last(LinkedList* lst, const BYTE* elemt)
{
    if (elemt == NULL)
    {
        return;
    }
    LnkLstNode* node = _lnklst_new_node(lst);
    if (node == NULL)
    {
        return;
    }
    memcpy(node->data, elemt, lst->elemt_size);

    node->next = lst->rear;
    node->prev = lst->rear->prev;
    node->prev->next = node;
    node->next->prev = node;
    lst->count++;
}
//Add an element before the specified node;
void lnklst_add_before(LnkLstNode* node, const BYTE* elemt)
{
    if (node == NULL || elemt == NULL)
    {
        return;
    }
    LnkLstNode* newnode = _lnklst_new_node(node->owner);
    if (newnode == NULL)
    {
        return;
    }
    memcpy(newnode->data, elemt, node->owner->elemt_size);

    newnode->next = node;
    newnode->prev = node->prev;
    newnode->prev->next = newnode;
    newnode->next->prev = newnode;
    newnode->owner->count++;
}
//Add an element after the specific node which contained in the list;
void lnklst_add_after(LnkLstNode* node, const BYTE* elemt)
{
    if (node == NULL || elemt == NULL)
    {
        return;
    }
    LnkLstNode* newnode = _lnklst_new_node(node->owner);
    if (newnode == NULL)
    {
        return;
    }
    memcpy(newnode->data, elemt, node->owner->elemt_size);

    newnode->next = node->next;
    newnode->prev = node;
    newnode->prev->next = newnode;
    newnode->next->prev = newnode;
    newnode->owner->count++;
}

//Remove node from the header of the list;
void lnklst_remove_first(LinkedList* lst)
{
    if (lnklst_is_empty(lst))
    {
        return;
    }
    LnkLstNode* tmp = lst->header->next;
    lnklst_remove(tmp);
}
//Remove node from the rear of the list;
void lnklst_remove_last(LinkedList* lst)
{
    if (lst == NULL || lst->count < 1)
    {
        return;
    }
    LnkLstNode* tmp = lst->rear->prev;
    lnklst_remove(tmp);
}
//Remove a node contained in the list using its pointer;
void lnklst_remove(LnkLstNode* node)
{
    if (node == NULL)
    {
        return;
    }
    LinkedList* lst = node->owner;
    if (lnklst_is_empty(lst) || node == lst->header || node == lst->rear)
    {
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    lst->count--;

    if (lnklst_is_pool_full(lst))
    {
        free(node->data);
        free(node);
    }
    else
    {
        node->owner = NULL;
        node->prev = NULL;
        node->next = lst->nodes_pool;
        lst->nodes_pool = node;
        lst->pool_count++;
    }
}

//Find the first node that contains the specified value;
LnkLstNode* lnklst_find(const LinkedList* lst, const BYTE* elemt, int (*cmp)(const BYTE*, const BYTE*))
{
    if (lnklst_is_empty(lst) || cmp == NULL)
    {
        return NULL;
    }
    LnkLstNode* tmp = lst->header;
    while (tmp->next != lst->rear)
    {
        tmp = tmp->next;
        if ((*cmp)(elemt, tmp->data) == 0)
        {
            return tmp;
        }
    }
    return NULL;
}
//Find the last node that contains the specified value;
LnkLstNode* lnklst_find_last(const LinkedList* lst, const BYTE* elemt, int (*cmp)(const BYTE*, const BYTE*))
{
    if (lnklst_is_empty(lst) || cmp == NULL)
    {
        return NULL;
    }
    LnkLstNode* tmp = lst->rear;
    while (tmp->prev != lst->header)
    {
        tmp = tmp->prev;
        if ((*cmp)(elemt, tmp->data) == 0)
        {
            return tmp;
        }
    }
    return NULL;
}
//travel the list, perform the specified action on each node;
//Like in java or C#, we assume that 'foreach' should not change the elemt;
void lnklst_foreach(LinkedList* lst, void (*action)(const BYTE* elemt))
{
    if (lnklst_is_empty(lst) || action == NULL)
    {
        return;
    }
    LnkLstNode* tmp = lst->header->next;
    while (tmp != lst->rear)
    {
        (*action)(tmp->data);
        tmp = tmp->next;
    }
}
//Remove all nodes in the list;
void lnklst_empty(LinkedList* lst)
{
    if ( !lnklst_is_empty(lst) )
    {
        LnkLstNode* tmp = lst->header->next;
        LnkLstNode* p;
        while (tmp != lst->rear)
        {
            p = tmp;
            tmp = tmp->next;
            lnklst_remove(p);
        }
    }
}
//Empty the nodes pool of the list;
void lnklst_empty_pool(LinkedList* lst)
{
    if ( !lnklst_is_pool_empty(lst) )
    {
        LnkLstNode* tmp = lst->nodes_pool;
        LnkLstNode* p;
        while (tmp != NULL)
        {
            p = tmp;
            tmp = tmp->next;
            free(p->data);
            p->data = NULL;
            free(p);
        }
        lst->pool_count = 0;
        lst->nodes_pool = NULL;
    }
}
//Dispose the linked list;
void lnklst_dispose(LinkedList* lst)
{
    if ( !lnklst_is_empty(lst) )
    {
        LnkLstNode* tmp = lst->header->next;
        LnkLstNode* p;
        while (tmp != lst->rear)
        {
            p = tmp;
            tmp = tmp->next;
            free(p->data);
            p->data = NULL;
            free(p);
        }
        lst->count = 0;
    }
    if ( !lnklst_is_pool_empty(lst) )
    {
        lnklst_empty_pool(lst);
    }
    free(lst->header);
    lst->header = NULL;
    lst->rear = NULL;
    lst->elemt_size = 0;
    lst->pool_size = 0;
    free(lst);
}
