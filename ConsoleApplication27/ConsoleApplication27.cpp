#include <iostream>
#include <fstream>
using namespace std;

struct Node;

struct tree
{
    Node* a;
    tree* next;
};

struct Node
{
    tree* l;
    tree* r;
    int size;
    char key;
};

void Add(tree*& head, int n, char key)
{
    tree* tmp, * p;
    tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    p = new tree;
    tmp->next = p;
    tmp->a->key = key;
    tmp->a->size = n;
};

void swap(tree* m1, tree* m2, tree*& head)

{
    m2->next = m1;
    m1->next = m2->next;
}


int main()
{
    int asc[256];
    int n = 0;
    for (int i = 0; i < 256; i++) asc[i] = 0;
    fstream fc("c.txt");
    char sim;
    fc >> sim;
    while (fc)
    {
        asc[(int)sim]++;
        fc >> sim;
    };
    tree* b = NULL;
    for (int i = 0; i < 256; i++)
    {
        cout << asc[i] << ' ';
    }

    for (int i = 0; i < 256; i++)
    {
        if (asc[i] != 0)
        {
            Add(b, asc[i], (char)i);
        }

    }

    while (b->next != NULL)
    {
        tree*& head = b;
        while (head->next != NULL)
        {
            tree*& headl = b;
            while (head->next != NULL)
            {
                if (headl > headl->next) swap(headl, headl->next, b);
                headl = headl->next;
            }
            head = head->next;
        }

    }

}