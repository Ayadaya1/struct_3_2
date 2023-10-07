#include<iostream>
#include "List.h"

using namespace std;




void makenull(struct List* list)
{
    list->begin = list->end = NULL;
}

struct List add_begin(struct List list, DataType x) /*���������� � ������*/
{
    struct element* temp;
    temp = (struct element*)malloc(sizeof(struct element));
    temp->data = x;
    temp->next = list.begin;
    temp->prev = NULL;
    if (list.begin) /*���� ��������� � �������� ������*/
        list.begin->prev = temp;
    else /*���� ����������� ������� ������������ � ������*/
        list.end = temp;
    list.begin = temp;
    return list;
}

struct List add_end(struct List list, DataType x) /*���������� � �����*/
{
    struct element* temp;
    temp = (struct element*)malloc(sizeof(struct element));
    temp->data = x;
    temp->next = NULL;
    temp->prev = list.end;
    if (list.end) /*���� ��������� � �������� ������*/
        list.end->next = temp;
    else /*���� ����������� ������� ������������ � ������*/
        list.begin = temp;
    list.end = temp;
    return list;
}

void insert(struct element* cur, DataType x) /*������� ����� �������� (�� ����������!)*/
{
    struct element* temp;
    temp = (struct element*)malloc(sizeof(struct element));
    temp->data = x;
    temp->next = cur->next;
    temp->prev = cur;
    cur->next = temp;
    temp->next->prev = temp; /*��������� prev ���������� �������� ����������� ����� ������������*/
}

void del_list(struct List list) /*�������� ������*/
{
    struct element* temp;
    while (list.begin) /*���� � ������ ���� ��������*/
    {
        temp = list.begin;
        list.begin = list.begin->next; /*������������ ��������� �� ��������� �������*/
        free(temp); /*������ �������*/
    }
}

struct List del_begin(struct List list) /*�������� ������� ��������*/
{
    struct element* temp;
    if (list.begin) /*���� � ������ ���� ��������*/
    {
        temp = list.begin;
        list.begin = list.begin->next; /*������������ ��������� �� ��������� �������*/
        list.begin->prev = NULL; /*�������� ��������� �� ��������� �������*/
        free(temp); /*������ �������*/
    }
    if (list.begin == NULL) /*���� ��������� ������� ��� ������������*/
        list.end = NULL;
    return list;
}

struct List del_end(struct List list) /*�������� ������� ��������*/
{
    struct element* temp;
    if (list.end) /*���� � ������ ���� ��������*/
    {
        temp = list.end;
        list.end = list.end->prev; /*������������ ��������� �� ���������� �������*/
        list.end->next = NULL; /*�������� ��������� �� ��������� �������*/
        free(temp); /*������ �������*/
    }
    if (list.end == NULL) /*���� ��������� ������� ��� ������������*/
        list.begin = NULL;
    return list;
}

void del_element(struct element* cur) /*�������� �������� (�����(!) �� ������� � �� ����������)*/
{
    cur->next->prev = cur->prev; /*��������� prev ���������� �������� ����������� ����� ��������������� ����������*/
    cur->prev->next = cur->next; /*��������� next ����������� �������� ����������� ����� ���������� �� ���������*/
    free(cur);
}

void print_list(struct List list) /*������ ������*/
{
    while (list.begin) /*���� � ������ ���� ��������*/
    {
        printf("%d ", list.begin->data);
        list.begin = list.begin->next; /*������������ ��������� �� ��������� �������*/
    }
}

void print_list_back(struct List list) /*������ ������ � �������� �������*/
{
    while (list.end) /*���� � ������ ���� ��������*/
    {
        printf("%d ", list.end->data);
        list.end = list.end->prev; /*������������ ��������� �� ��������� �������*/
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