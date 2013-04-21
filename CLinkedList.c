/* Project:     Linked List for C
 * File:        CLinkedList.c
 * Coder:       FunctionGHW
 * Version:     0.1
 * Last Change: 2013-4-21
 * Description: an implementation of CLinkedList.h, and it's a doubly linked list.
 *
 */
#include "CLinkedList.h"

struct LinkedList
{
    size_t count;
    size_t elemt_size;

    LnkLstNode* header;
    LnkLstNode* rear;
    LnkLstNode* deleted_nodes;
};

struct LnkLstNode
{
    BYTE* data;

    LinkedList* owner;
    LnkLstNode* next;
    LnkLstNode* prev;
};
