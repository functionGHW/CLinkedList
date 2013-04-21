/* Project:     Linked List for C
 * File:        CLinkedList.h
 * Coder:       FunctionGHW
 * Version:     0.4
 * Last Change: 2013-4-21
 * Description: Interface of linked list using C.
 *              Note: We assume that user only operate the list by functions declared here.
 */

#ifndef CLINKEDLIST_BBA5D14C_DFCF_49D0_9C73_EBEB05E6DF8F
#define CLINKEDLIST_BBA5D14C_DFCF_49D0_9C73_EBEB05E6DF8F

#include <stddef.h>

#ifndef BYTE
#define BYTE unsigned char
#endif

struct LinkedList;
struct LnkLstNode;

typedef struct LinkedList LinkedList;
typedef struct LnkLstNode LnkLstNode;

//Create a new linked list;
LinkedList* new_lnklst(const size_t elemt_size);

//Get the number of nodes actually contained in the list;
size_t lnklst_count(const LinkedList* lst);
//Get the size of element that contained in the list;
size_t lnklst_elemt_size(const LinkedList* lst);

//Get the first element contained in the list;
BYTE* lnklst_first_elemt(const LinkedList* lst);
//Get the last element contained in the list;
BYTE* lnklst_last_elemt(const LinkedList* lst);

//Get the first node contained in the list;
LnkLstNode* lnklst_first_node(const LinkedList* lst);
//Get the last node contained in the list;
LnkLstNode* lnklst_last_node(const LinkedList* lst);

//Get the node contained in the list which has the specified position;
LnkLstNode* lnklst_node_at(const LinkedList* lst, const size_t index);

//Add an element to the header of the list;
void lnklst_add_first(LinkedList* lst, const BYTE* elemt);
//Add an element to the rear of the list;
void lnklst_add_last(LinkedList* lst, const BYTE* elemt);
//Add an element before the specified node which contained in the list;
void lnklst_add_before(LinkedList* lst, const BYTE* elemt);
//Add an element after the specific node which contained in the list;
void lnklst_add_after(LinkedList* lst, const BYTE* elemt);

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

//travel the list, perform the specified action on each node;
void lnklst_foreach(LinkedList* lst, void (*action)(LnkLstNode* node));
//Remove all nodes in the list;
void lnklst_empty(LinkedList* lst);
//Dispose the linked list;
void lnklst_dispose(LinkedList* lst);

#endif // CLINKEDLIST_BBA5D14C_DFCF_49D0_9C73_EBEB05E6DF8F
