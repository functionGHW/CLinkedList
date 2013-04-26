#include <stdio.h>
#include <stdlib.h>

#include "CLinkedList.h"

void show_lnklst(LinkedList* lst)
{
    if (lst == NULL || lst->header == NULL)
    {
        printf("  NULL list\n");
        return;
    }
    printf("{\n");
    printf("  count: %d\n", lnklst_count(lst));
    printf("  elemt size: %d\n", lnklst_elemt_size(lst));
    printf("  pool size: %d\n", lnklst_pool_size(lst));
    printf("  pool count: %d\n", lnklst_pool_count(lst));
    printf("}\n");
}

int cmp(const BYTE* x, const BYTE* y)
{
    int num1 = *((int*)x);
    int num2 = *((int*)y);
    if (num1 > num2)
    {
        return 1;
    }
    if (num1 == num2)
    {
        return 0;
    }
    return -1;
}

void print_elemt(const BYTE* elemt)
{
    printf("  val = %d\n", *elemt);
}

int main()
{
    int arr[] = {0, 1, 2, 3,  4, 5, 6, 7, 8};
    puts(">>>Create a linked list:");
    LinkedList* the_list = new_lnklst(sizeof(arr[0]), 3);
    show_lnklst(the_list);
    puts(">>> add last:");
    lnklst_add_last(the_list, (BYTE*)(arr + 1));
    lnklst_foreach(the_list, print_elemt);
    puts(">>> add last again:");
    lnklst_add_last(the_list, (BYTE*)(arr + 2));
    puts(">>> add last again:");
    lnklst_add_last(the_list, (BYTE*)(arr + 3));
    show_lnklst(the_list);
    lnklst_foreach(the_list, print_elemt);
    puts(">>> add first:");
    lnklst_add_first(the_list, (BYTE*)(arr + 0));
    show_lnklst(the_list);
    lnklst_foreach(the_list, print_elemt);

    puts("======search and remove test:");
    puts(">>>lnklst_find:");
    LnkLstNode* ret = lnklst_find_last(the_list, (BYTE*)(arr + 2), cmp);
    printf("find: ");
    print_elemt(ret->data);
    puts(">>>then remove it:");
    lnklst_remove(ret);
    show_lnklst(the_list);
    lnklst_foreach(the_list, print_elemt);
    puts(">>> remove_first:");
    lnklst_remove_first(the_list);
    show_lnklst(the_list);
    lnklst_foreach(the_list, print_elemt);

    puts("== add element to last:");
    lnklst_add_last(the_list, (BYTE*)(arr + 5));
    show_lnklst(the_list);
    lnklst_foreach(the_list, print_elemt);
    puts("== add element to last:");
    lnklst_add_last(the_list, (BYTE*)(arr + 6));
    show_lnklst(the_list);
    lnklst_foreach(the_list, print_elemt);
    puts("== add element to last:");
    lnklst_add_last(the_list, (BYTE*)(arr + 7));
    show_lnklst(the_list);
    lnklst_foreach(the_list, print_elemt);

    puts(">>> empty list:");
    lnklst_empty(the_list);
    show_lnklst(the_list);
    lnklst_foreach(the_list, print_elemt);

    printf("> > > dispose list\n");
    lnklst_dispose(the_list);
    the_list = NULL;

    printf("disposed\n");
    show_lnklst(the_list);
    lnklst_foreach(the_list, print_elemt);

    getchar();
    return 0;
}
