/* Project:     Linked List for C
 * File:        CLinkedList.h
 * Coder:       FunctionGHW
 * Version:     1.1
 * Last Change: 2013-5-9
 * Description: Interface of linked list using C.
 *              Finally, I decide to write a doubly linked list.
 *              Note: We assume that users only operate the list by functions declared here.
 */

#ifndef CLINKEDLIST_BBA5D14C_DFCF_49D0_9C73_EBEB05E6DF8F
#define CLINKEDLIST_BBA5D14C_DFCF_49D0_9C73_EBEB05E6DF8F

#include <stddef.h>

#ifndef TYPEDEF_BYTE
#define TYPEDEF_BYTE
typedef unsigned char BYTE;
#endif

struct LinkedList;
struct LnkLstNode;

typedef struct LinkedList LinkedList;
typedef struct LnkLstNode LnkLstNode;

struct LnkLstNode
{
    BYTE* data;

    LinkedList* owner;//which linked list the node was contained;
    LnkLstNode* next;
    LnkLstNode* prev;
};

struct LinkedList
{
    size_t count;
    size_t elemt_size;
    LnkLstNode* header;
    LnkLstNode* rear;

    /* a nodes pool is used for
     * storeing nodes temporarily,
     * which were removed;*/
    size_t pool_size;
    // maximum number of nodes that the pool could contain;
    size_t pool_count;
    //the number of nodes actually contained in nodes pool;
    LnkLstNode* nodes_pool;
};

//==========================================

//Create a new linked list;
LinkedList* new_lnklst(const size_t elemt_size, const size_t pool_size);

//Is the list empty?;
int lnklst_is_empty(const LinkedList* lst);
//Is the nodes pool empty?;
int lnklst_is_pool_empty(const LinkedList* lst);
//Is the nodes pool full?;
int lnklst_is_pool_full(const LinkedList* lst);
//Get the number of nodes actually contained in the list;
size_t lnklst_count(const LinkedList* lst);
//Get the size of element that contained in the list;
size_t lnklst_elemt_size(const LinkedList* lst);
//Get maximum number of nodes that the pool could contain;
size_t lnklst_pool_size(const LinkedList* lst);
//Get the number of nodes actually contained in nodes pool;
size_t lnklst_pool_count(const LinkedList* lst);

//Get the first element contained in the list;
BYTE* lnklst_first_elemt(const LinkedList* lst);
//Get the last element contained in the list;
BYTE* lnklst_last_elemt(const LinkedList* lst);

//Get the first node contained in the list;
LnkLstNode* lnklst_first_node(const LinkedList* lst);
//Get the last node contained in the list;
LnkLstNode* lnklst_last_node(const LinkedList* lst);

//Get the node contained in the list which has the specified position;
LnkLstNode* lnklst_node_at(const LinkedList* lst, size_t index);

//Add an element to the header of the list;
void lnklst_add_first(LinkedList* lst, const BYTE* elemt);
//Add an element to the rear of the list;
void lnklst_add_last(LinkedList* lst, const BYTE* elemt);
//Add an element before the specified node;
void lnklst_add_before(LnkLstNode* node, const BYTE* elemt);
//Add an element after the specific node;
void lnklst_add_after(LnkLstNode* node, const BYTE* elemt);

//Remove node from the header of the list;
void lnklst_remove_first(LinkedList* lst);
//Remove node from the rear of the list;
void lnklst_remove_last(LinkedList* lst);
//Remove a node contained in the list using its pointer;
void lnklst_remove(LnkLstNode* node);

//Find the first node that contains the specified value;
LnkLstNode* lnklst_find(const LinkedList* lst, const BYTE* elemt, int (*cmp)(const BYTE*, const BYTE*));
//Find the last node that contains the specified value;
LnkLstNode* lnklst_find_last(const LinkedList* lst, const BYTE* elemt, int (*cmp)(const BYTE*, const BYTE*));

//Travel the list, perform the specified action on each node;
//Like in java or C#, we assume that 'foreach' should not change the elemt;
void lnklst_foreach(LinkedList* lst, void (*action)(const BYTE* elemt));
//Remove all nodes in the list;
void lnklst_empty(LinkedList* lst);
//Empty the nodes pool of the list;
void lnklst_empty_pool(LinkedList* lst);
//Dispose the linked list;
void lnklst_dispose(LinkedList* lst);

#endif // CLINKEDLIST_BBA5D14C_DFCF_49D0_9C73_EBEB05E6DF8F
