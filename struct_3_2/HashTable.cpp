#include "List.h"
#include <iostream>
#include "HashTable.h"
#define CAPACITY 50000
using namespace std;

unsigned long hash_function(int num) {
    return num % CAPACITY;
}


Ht_item* create_item(int value) {
    // Creates a pointer to a new hash table item
    Ht_item* item = (Ht_item*)malloc(sizeof(Ht_item));
    item->key = hash_function(value);
    makenull(&item->value);
    item->value = add_end(item->value, value);

    return item;
}

HashTable* create_table(int size) {
    // Creates a new HashTable
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**)calloc(table->size, sizeof(Ht_item*));
    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;

    return table;

}

void free_item(Ht_item* item) {

    free(item);
}

void free_table(HashTable* table) {
    // Frees the table
    for (int i = 0; i < table->size; i++) {
        Ht_item* item = table->items[i];
        if (item != NULL)
            free_item(item);
    }

    free(table->items);
    free(table);
}

void handle_collision(HashTable* table, unsigned long index, Ht_item* item) {
}

void ht_insert(HashTable* table, int value) {
    // Create the item
    int key = hash_function(value);
    Ht_item* item;
    if (table->items[key] == NULL)
        item = create_item(value);
    else {
        item = table->items[key];
        item->key = key;
        item->value = add_end(item->value, value);
    }


    // Compute the index
    unsigned long index = hash_function(value);

    Ht_item* current_item = table->items[index];

    if (current_item == NULL) {
        // Key does not exist.
        if (table->count == table->size) {
            // Hash Table Full
            printf("Insert Error: Hash Table is full\n");
            // Remove the create item
            free_item(item);
            return;
        }

        // Insert directly
        table->items[index] = item;
        table->count++;
    }

    else {
        // Scenario 1: We only need to update value
        if (current_item->key != key) {
            table->items[index]->value = add_end(table->items[index]->value, value);
            return;
        }

        else {
            // Scenario 2: Collision
            // We will handle case this a bit later
            handle_collision(table, index, item);
            return;
        }
    }
}

List* ht_search(HashTable* table, int key, int& counter) {
    // Searches the key in the hashtable
    // and returns NULL if it doesn't exist
    int index = hash_function(key);
    Ht_item* item = table->items[index];

    // Ensure that we move to a non NULL item
    if (item != NULL) {
        if (item->key == key)
        {
            return &item->value;
        }
    }
    return NULL;
}

int print_search(HashTable* table, int key, int &counter, int& found) {
    int val;
    int a = hash_function(key);
    List* list = ht_search(table, a, counter);
    counter++;
    if (list != NULL)
    {
        if ((listContains(*list, key, counter))) {
            cout << "Значение " << key << " найдено по ключу " << a << " за " << counter << " сравнений"<<endl;
            found++;
        }
        else {
            cout << "Значение " << key << " не найдено за " << counter << " сравнений" << endl;
        }
    }
    else {
        cout << "Значение " << key << " не найдено за " << counter << " сравнений" << endl;
        //found++;
    }
    return counter;
}

