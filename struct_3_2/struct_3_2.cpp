#include<iostream>
#include <fstream>
#include <locale.h>
#include "List.h"
#include "Tree.h"
#include "HashTable.h"
#define N 100;
#define CAPACITY 50000 // Размер хэш-таблицы

using namespace std;


int Fill(string filename, int* &Ar)
{
    int i;
    ifstream Test_File;
    Test_File.open(filename, ios_base::in);
    if (!Test_File)
    {
        cout << "File open Error" << endl;
        return -1;
    }
    int temp;
    int count = 0;
    do
    {
        count++;
    } while (Test_File >> temp);
    count--;
    Ar = new int[count];
    Test_File.close();
    Test_File.open(filename, ios_base::in);
    if (!Test_File)
    {
        cout << "File open Error" << endl;
        return -1;
    }
    for (i = 0; i < count; i++)
    {
        Test_File >> Ar[i];
    }
    Test_File.close();

    return count;
}

void FillKeys(int* array, int n, int* keys, int keyN)
{
    srand(time(0));
    int a = 0;
    for (int i = 0; i < keyN; i++)
    {
        int j = rand() % n;
        int key = array[j];
        cout << key << endl;
        switch (rand() % 5) 
        {
        case 1:
            key *= rand()%3+2;
            break;
        case 2:
            key /= rand()%3+2;
            break;
        default: 
            a++;
            break;
        }
        keys[i] = key;
    }
}

int  main()
{
    char* locale = setlocale(LC_ALL, "Russian");
    struct rb_tree* tree = tree_create();
    int* array = {0};
    int keys[100];

    int n = Fill("test_numbers.txt", array);
    if (n == -1)
    {
        return 1;
    }
    FillKeys(array, n, keys, 100);
    for (int i = 0; i < n; i++)
    {
        rb_insert(tree, array[i]);
    }
    int rbFound = 0;
    long long int rb_count = 0;
    cout << "Красно-чёрное дерево: " << endl << endl;
    for (int i = 0; i < 100; i++)
    {
        int key = keys[i];
        long long int counter = 0;
        int keyFound = find(tree, key, counter);
        if (keyFound)
        {
            cout << "Ключ " << key << " найден за " << counter << " сравнений" << endl;
        }
        else 
        {
            cout << "Ключ " << key << " НЕ найден за " << counter << " сравнений" << endl;
        }
        rbFound += keyFound;
        rb_count += counter;
    }
    HashTable* ht = create_table(CAPACITY);
    for (int i = 0; i < n; i++)
    {
        ht_insert(ht, array[i]);
    }
    int ht_counter = 0;
    int htFound = 0;
    cout << "Хеш-таблица: " << endl << endl;
    for (int i = 0; i < 100; i++)
    {
        int counter = 0;
        ht_counter += print_search(ht, keys[i], counter, htFound);
    }
    free_table(ht);
    cout << endl << "Ключей найдено с помощью красно-чёрного дерева: " << rbFound << endl;
    cout << endl << "Ключей найдено с помощью хеш-таблицы: " << htFound << endl;
    cout << endl << "Среднее количество сравнений для красно-чёрного дерева: " << (double)rb_count / 100 << endl;
    cout << "Среднее количество сравнений для хеш-таблицы: " << (double)ht_counter / 100 << endl;
    return 0;
    delete[] array;
    return 0;
}
