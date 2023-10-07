#pragma once

struct rb_node
{
    int red;
    int data;
    struct rb_node* link[2];
};

struct rb_tree
{
    struct rb_node* root; // указатель на корневой узел
    int count; // количество узлов в дереве
};

struct rb_tree* tree_create();
int is_red(struct rb_node* node);
struct rb_node* rb_single(struct rb_node* root, int dir);
struct rb_node* rb_double(struct rb_node* root, int dir);
struct rb_node* make_node(int data);
int rb_insert(struct rb_tree* tree, int data);
int rb_remove(struct rb_tree* tree, int data);
void del_rb_tree(struct rb_node* node);
void print_sim(struct rb_node* node, int tbl);
bool find(struct rb_tree* tree, int data, long long int& counter);