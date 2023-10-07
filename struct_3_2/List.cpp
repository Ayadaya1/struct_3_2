#include<iostream>
#include "List.h"

using namespace std;




void makenull(struct List* list)
{
    list->begin = list->end = NULL;
}

struct List add_begin(struct List list, DataType x) /*добавление в начало*/
{
    struct element* temp;
    temp = (struct element*)malloc(sizeof(struct element));
    temp->data = x;
    temp->next = list.begin;
    temp->prev = NULL;
    if (list.begin) /*если добавляем в непустой список*/
        list.begin->prev = temp;
    else /*если добавляемый элемент единственный в списке*/
        list.end = temp;
    list.begin = temp;
    return list;
}

struct List add_end(struct List list, DataType x) /*добавление в конец*/
{
    struct element* temp;
    temp = (struct element*)malloc(sizeof(struct element));
    temp->data = x;
    temp->next = NULL;
    temp->prev = list.end;
    if (list.end) /*если добавляем в непустой список*/
        list.end->next = temp;
    else /*если добавляемый элемент единственный в списке*/
        list.begin = temp;
    list.end = temp;
    return list;
}

void insert(struct element* cur, DataType x) /*вставка после текущего (не последнего!)*/
{
    struct element* temp;
    temp = (struct element*)malloc(sizeof(struct element));
    temp->data = x;
    temp->next = cur->next;
    temp->prev = cur;
    cur->next = temp;
    temp->next->prev = temp; /*указателю prev следующего элемента присваиваем адрес добавляемого*/
}

void del_list(struct List list) /*удаление списка*/
{
    struct element* temp;
    while (list.begin) /*пока в списке есть элементы*/
    {
        temp = list.begin;
        list.begin = list.begin->next; /*переставляем указатель на следующий элемент*/
        free(temp); /*первый удаляем*/
    }
}

struct List del_begin(struct List list) /*удаление первого элемента*/
{
    struct element* temp;
    if (list.begin) /*если в списке есть элементы*/
    {
        temp = list.begin;
        list.begin = list.begin->next; /*переставляем указатель на следующий элемент*/
        list.begin->prev = NULL; /*обнуляем указатель на удаляемый элемент*/
        free(temp); /*первый удаляем*/
    }
    if (list.begin == NULL) /*если удаляемый элемент был единственным*/
        list.end = NULL;
    return list;
}

struct List del_end(struct List list) /*удаление первого элемента*/
{
    struct element* temp;
    if (list.end) /*если в списке есть элементы*/
    {
        temp = list.end;
        list.end = list.end->prev; /*переставляем указатель на предыдущий элемент*/
        list.end->next = NULL; /*обнуляем указатель на удаляемый элемент*/
        free(temp); /*первый удаляем*/
    }
    if (list.end == NULL) /*если удаляемый элемент был единственным*/
        list.begin = NULL;
    return list;
}

void del_element(struct element* cur) /*удаление текущего (важно(!) не первого и не последнего)*/
{
    cur->next->prev = cur->prev; /*указателю prev следующего элемента присваиваем адрес предшествующего удаляемому*/
    cur->prev->next = cur->next; /*указателю next предыдущего элемента присваиваем адрес следующего за удаляемым*/
    free(cur);
}

void print_list(struct List list) /*печать списка*/
{
    while (list.begin) /*пока в списке есть элементы*/
    {
        printf("%d ", list.begin->data);
        list.begin = list.begin->next; /*переставляем указатель на следующий элемент*/
    }
}

void print_list_back(struct List list) /*печать списка в обратном порядке*/
{
    while (list.end) /*пока в списке есть элементы*/
    {
        printf("%d ", list.end->data);
        list.end = list.end->prev; /*переставляем указатель на следующий элемент*/
    }
}

bool listContains(struct List list, DataType data, int& counter)
{
        while (list.begin)
        {
            counter++;
            if (data == list.begin->data)
                return true;
            list.begin = list.begin->next;
        }
   
    return false;
}