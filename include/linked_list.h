/*
** EPITECH PROJECT, 2020
** NAME_OF_THE_PROJECT
** File description:
** header file for the linked list librairie
*/

#ifndef HEADER_LINKED_LIST_LIB
#define HEADER_LINKED_LIST_LIB

typedef struct list {
    void *data;
    struct list *next;
    struct list *previous;
} list_t;

list_t *add_element_list(list_t **begin, char const *element);
list_t *reverse_list(list_t **begin_p);
void clean_list(list_t *begin);

#endif
