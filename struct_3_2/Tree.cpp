#pragma once
#include"Tree.h"
#include "iostream"
/* структура, описывающая узел красно-черного дерева */

using namespace std;



struct rb_tree* tree_create()
{
    struct rb_tree* my_tree = (rb_tree*)malloc(sizeof(struct rb_tree));
    my_tree->root = NULL;
    my_tree->count = 0;
    return my_tree;
}

int is_red(struct rb_node* node)
{
    return node != NULL && node->red == 1;
}

/* функция для однократного поворота узла */
struct rb_node* rb_single(struct rb_node* root, int dir)
{
    struct rb_node* save = root->link[!dir];

    root->link[!dir] = save->link[dir];
    save->link[dir] = root;

    root->red = 1;
    save->red = 0;

    return save;
}

/* функция для двукратного поворота узла */
struct rb_node* rb_double(struct rb_node* root, int dir)
{
    root->link[!dir] = rb_single(root->link[!dir], !dir);
    return rb_single(root, dir);
}

struct rb_node* make_node(int data)
{
    struct rb_node* rn = (rb_node*)malloc(sizeof(struct rb_node));

    if (rn != NULL) {
        rn->data = data;
        rn->red = 1; /* -инициализация красным цветом */
        rn->link[0] = NULL;
        rn->link[1] = NULL;
    }
    return rn;
}

int rb_insert(struct rb_tree* tree, int data)
{
    /* если добавляемый элемент оказывается первым - то ничего делать не нужно*/
    if (tree->root == NULL) {
        tree->root = make_node(data);
        if (tree->root == NULL)
            return 0;
    }
    else {
        struct rb_node head = { 0 }; /* временный корень дерева*/
        struct rb_node* g, * t;     /* дедушка и родитель */
        struct rb_node* p, * q;     /* родитель и итератор */
        int dir = 0, last;

        /* вспомогательные переменные */
        t = &head;
        g = p = NULL;
        q = t->link[1] = tree->root;

        /* основной цикл прохода по дереву */
        for (; ; )
        {
            if (q == NULL) {
                /* вставка ноды */
                p->link[dir] = q = make_node(data);
                tree->count++;
                if (q == NULL)
                    return 0;
            }
            else if (is_red(q->link[0]) && is_red(q->link[1]))
            {
                /* смена цвета */
                q->red = 1;
                q->link[0]->red = 0;
                q->link[1]->red = 0;
            }
            /* совпадение 2-х красных цветов */
            if (is_red(q) && is_red(p))
            {
                int dir2 = t->link[1] == g;

                if (q == p->link[last])
                    t->link[dir2] = rb_single(g, !last);
                else
                    t->link[dir2] = rb_double(g, !last);
            }

            /* такой узел в дереве уже есть  - выход из функции*/
            if (q->data == data)
                break;

            last = dir;
            dir = q->data < data;

            if (g != NULL)
                t = g;
            g = p, p = q;
            q = q->link[dir];
        }

        /* обновить указатель на корень дерева*/
        tree->root = head.link[1];
    }
    /* сделать корень дерева черным */
    tree->root->red = 0;

    return 1;
}

int rb_remove(struct rb_tree* tree, int data)
{
    if (tree->root != NULL)
    {
        struct rb_node head = { 0 }; /* временный указатель на корень дерева */
        struct rb_node* q, * p, * g; /* вспомогательные переменные */
        struct rb_node* f = NULL;  /* узел, подлежащий удалению */
        int dir = 1;

        /* инициализация вспомогательных переменных */
        q = &head;
        g = p = NULL;
        q->link[1] = tree->root;

        /* поиск и удаление */
        while (q->link[dir] != NULL) {
            int last = dir;

            /* сохранение иерархии узлов во временные переменные */
            g = p, p = q;
            q = q->link[dir];
            dir = q->data < data;

            /* сохранение найденного узла */
            if (q->data == data)
                f = q;

            if (!is_red(q) && !is_red(q->link[dir])) {
                if (is_red(q->link[!dir]))
                    p = p->link[last] = rb_single(q, dir);
                else if (!is_red(q->link[!dir])) {
                    struct rb_node* s = p->link[!last];


                    if (s != NULL) {
                        if (!is_red(s->link[!last]) && !is_red(s->link[last])) {
                            /* смена цвета узлов */
                            p->red = 0;
                            s->red = 1;
                            q->red = 1;
                        }
                        else {
                            int dir2 = g->link[1] == p;

                            if (is_red(s->link[last]))
                                g->link[dir2] = rb_double(p, last);
                            else if (is_red(s->link[!last]))
                                g->link[dir2] = rb_single(p, last);

                            /* корректировка цвета узлов */
                            q->red = g->link[dir2]->red = 1;
                            g->link[dir2]->link[0]->red = 0;
                            g->link[dir2]->link[1]->red = 0;
                        }
                    }
                }
            }
        }

        /* удаление найденного узла */
        if (f != NULL) {
            f->data = q->data;
            p->link[p->link[1] == q] =
                q->link[q->link[0] == NULL];
            free(q);
        }

        /* обновление указателя на корень дерева */
        tree->root = head.link[1];
        if (tree->root != NULL)
            tree->root->red = 0;
    }

    return 1;
}

void del_rb_tree(struct rb_node* node)
{
    if (node->link[1]) del_rb_tree(node->link[1]);
    if (node->link[0]) del_rb_tree(node->link[0]);
    free(node);
}

void print_sim(struct rb_node* node, int tbl)
{
    if (node->link[1]) print_sim(node->link[1], tbl + 5);
    printf("%*d_%d\n", tbl, node->data, node->red);
    if (node->link[0]) print_sim(node->link[0], tbl + 5);
}

bool find(struct rb_tree* tree, int data, long long int& counter)
{
    if (tree->root != NULL)
    {
        struct rb_node head = { 0 }; /* временный указатель на корень дерева */
        struct rb_node* q, * p, * g; /* вспомогательные переменные */
        struct rb_node* f = NULL;  /* узел, подлежащий удалению */
        int dir = 1;

        /* инициализация вспомогательных переменных */
        q = &head;
        g = p = NULL;
        q->link[1] = tree->root;

        /* поиск и удаление */
        while (q->link[dir] != NULL) {
            int last = dir;

            /* сохранение иерархии узлов во временные переменные */
            g = p, p = q;
            q = q->link[dir];
            dir = q->data < data;
            counter++;

            /* сохранение найденного узла */
            if (q->data == data)
            {
                f = q;
                counter++;
            }

            if (!is_red(q) && !is_red(q->link[dir])) {
                if (is_red(q->link[!dir]))
                    p = p->link[last] = rb_single(q, dir);
                else if (!is_red(q->link[!dir])) {
                    struct rb_node* s = p->link[!last];


                    if (s != NULL) {
                        if (!is_red(s->link[!last]) && !is_red(s->link[last])) {
                            /* смена цвета узлов */
                            p->red = 0;
                            s->red = 1;
                            q->red = 1;
                        }
                        else {
                            int dir2 = g->link[1] == p;

                            if (is_red(s->link[last]))
                                g->link[dir2] = rb_double(p, last);
                            else if (is_red(s->link[!last]))
                                g->link[dir2] = rb_single(p, last);

                            /* корректировка цвета узлов */
                            q->red = g->link[dir2]->red = 1;
                            g->link[dir2]->link[0]->red = 0;
                            g->link[dir2]->link[1]->red = 0;
                        }
                    }
                }
            }
        }


        /* обновление указателя на корень дерева */
        tree->root = head.link[1];
        if (tree->root != NULL)
            tree->root->red = 0;
        if (f != NULL) {
            return true;
        }
        return false;
    }
    return false;
}