/* Project:     Linked List for C
 * File:        CLinkedList.h
 * Coder:       FunctionGHW
 * Version:     0.1
 * Last Change: 2013-4-21
 * Description: Interface of linked list using C, this is a singly-linked list.
 *              Note: We assume that user only operate the list by functions declared here.
 */

#ifndef CLINKEDLIST_BBA5D14C_DFCF_49D0_9C73_EBEB05E6DF8F
#define CLINKEDLIST_BBA5D14C_DFCF_49D0_9C73_EBEB05E6DF8F

#include <stddef.h>

#ifndef BYTE
#define BYTE unsigned char
#endif

typedef struct LinkedList LinkedList;
typedef struct LnkLstNode LnkLstNode;

struct LinkedList
{
    size_t nodes_count;
    size_t elemt_size;

    LnkLstNode* header;
    LnkLstNode* rear;
    LnkLstNode* deleted_nodes;
}

struct LnkLstNode
{
    BYTE* data;

    LnkLstNode* next;
}


#endif // CLINKEDLIST_BBA5D14C_DFCF_49D0_9C73_EBEB05E6DF8F
