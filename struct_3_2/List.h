#pragma once

typedef int DataType;

struct element
{
    DataType data;
    struct element* next, * prev;
};
struct List
{
    struct element* begin, * end;
};
typedef struct List List;

void makenull(List* list);
struct List add_begin(List list, DataType x);
struct List add_end(List list, DataType x);

void insert(element* cur, DataType x);
void del_list(List list);
struct List del_begin(List list);

struct List del_end(List list);
void del_element(element* cur);
void print_list(List list);
void print_list_back(List list);
bool listContains(List list, DataType data, int& counter);
