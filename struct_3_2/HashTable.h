#pragma once
#include "List.h"

typedef struct Ht_item Ht_item;

// Define the Hash Table Item here
struct Ht_item {
    int key;
    List value;
};

typedef struct HashTable HashTable;

// Define the Hash Table here
struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    int size;
    int count;
};
Ht_item* create_item(int value);
HashTable* create_table(int size);
void free_table(HashTable* table);
void ht_insert(HashTable* table, int value);
int print_search(HashTable* table, int key, int& counter, int& found);