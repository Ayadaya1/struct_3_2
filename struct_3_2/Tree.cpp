#pragma once
#include"Tree.h"
#include "iostream"
/* ���������, ����������� ���� ������-������� ������ */

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

/* ������� ��� ������������ �������� ���� */
struct rb_node* rb_single(struct rb_node* root, int dir)
{
    struct rb_node* save = root->link[!dir];

    root->link[!dir] = save->link[dir];
    save->link[dir] = root;

    root->red = 1;
    save->red = 0;

    return save;
}

/* ������� ��� ����������� �������� ���� */
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
        rn->red = 1; /* -������������� ������� ������ */
        rn->link[0] = NULL;
        rn->link[1] = NULL;
    }
    return rn;
}

int rb_insert(struct rb_tree* tree, int data)
{
    /* ���� ����������� ������� ����������� ������ - �� ������ ������ �� �����*/
    if (tree->root == NULL) {
        tree->root = make_node(data);
        if (tree->root == NULL)
            return 0;
    }
    else {
        struct rb_node head = { 0 }; /* ��������� ������ ������*/
        struct rb_node* g, * t;     /* ������� � �������� */
        struct rb_node* p, * q;     /* �������� � �������� */
        int dir = 0, last;

        /* ��������������� ���������� */
        t = &head;
        g = p = NULL;
        q = t->link[1] = tree->root;

        /* �������� ���� ������� �� ������ */
        for (; ; )
        {
            if (q == NULL) {
                /* ������� ���� */
                p->link[dir] = q = make_node(data);
                tree->count++;
                if (q == NULL)
                    return 0;
            }
            else if (is_red(q->link[0]) && is_red(q->link[1]))
            {
                /* ����� ����� */
                q->red = 1;
                q->link[0]->red = 0;
                q->link[1]->red = 0;
            }
            /* ���������� 2-� ������� ������ */
            if (is_red(q) && is_red(p))
            {
                int dir2 = t->link[1] == g;

                if (q == p->link[last])
                    t->link[dir2] = rb_single(g, !last);
                else
                    t->link[dir2] = rb_double(g, !last);
            }

            /* ����� ���� � ������ ��� ����  - ����� �� �������*/
            if (q->data == data)
                break;

            last = dir;
            dir = q->data < data;

            if (g != NULL)
                t = g;
            g = p, p = q;
            q = q->link[dir];
        }

        /* �������� ��������� �� ������ ������*/
        tree->root = head.link[1];
    }
    /* ������� ������ ������ ������ */
    tree->root->red = 0;

    return 1;
}

int rb_remove(struct rb_tree* tree, int data)
{
    if (tree->root != NULL)
    {
        struct rb_node head = { 0 }; /* ��������� ��������� �� ������ ������ */
        struct rb_node* q, * p, * g; /* ��������������� ���������� */
        struct rb_node* f = NULL;  /* ����, ���������� �������� */
        int dir = 1;

        /* ������������� ��������������� ���������� */
        q = &head;
        g = p = NULL;
        q->link[1] = tree->root;

        /* ����� � �������� */
        while (q->link[dir] != NULL) {
            int last = dir;

            /* ���������� �������� ����� �� ��������� ���������� */
            g = p, p = q;
            q = q->link[dir];
            dir = q->data < data;

            /* ���������� ���������� ���� */
            if (q->data == data)
                f = q;

            if (!is_red(q) && !is_red(q->link[dir])) {
                if (is_red(q->link[!dir]))
                    p = p->link[last] = rb_single(q, dir);
                else if (!is_red(q->link[!dir])) {
                    struct rb_node* s = p->link[!last];


                    if (s != NULL) {
                        if (!is_red(s->link[!last]) && !is_red(s->link[last])) {
                            /* ����� ����� ����� */
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

                            /* ������������� ����� ����� */
                            q->red = g->link[dir2]->red = 1;
                            g->link[dir2]->link[0]->red = 0;
                            g->link[dir2]->link[1]->red = 0;
                        }
                    }
                }
            }
        }

        /* �������� ���������� ���� */
        if (f != NULL) {
            f->data = q->data;
            p->link[p->link[1] == q] =
                q->link[q->link[0] == NULL];
            free(q);
        }

        /* ���������� ��������� �� ������ ������ */
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
        struct rb_node head = { 0 }; /* ��������� ��������� �� ������ ������ */
        struct rb_node* q, * p, * g; /* ��������������� ���������� */
        struct rb_node* f = NULL;  /* ����, ���������� �������� */
        int dir = 1;

        /* ������������� ��������������� ���������� */
        q = &head;
        g = p = NULL;
        q->link[1] = tree->root;

        /* ����� � �������� */
        while (q->link[dir] != NULL) {
            int last = dir;

            /* ���������� �������� ����� �� ��������� ���������� */
            g = p, p = q;
            q = q->link[dir];
            dir = q->data < data;
            counter++;

            /* ���������� ���������� ���� */
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
                            /* ����� ����� ����� */
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

                            /* ������������� ����� ����� */
                            q->red = g->link[dir2]->red = 1;
                            g->link[dir2]->link[0]->red = 0;
                            g->link[dir2]->link[1]->red = 0;
                        }
                    }
                }
            }
        }


        /* ���������� ��������� �� ������ ������ */
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