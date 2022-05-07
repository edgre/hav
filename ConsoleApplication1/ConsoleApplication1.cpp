#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <vector>

using namespace std;

struct Node;

struct Node
{
    Node* r;
    Node* l;
    Node* next;
    int size;
    string key;
    Node(int n = 0, char k = '\0');
    Node(int n = 0, string k = NULL);

};

struct tree
{
    Node* first;
    Node* last;
    tree();
};

tree::tree() { first = NULL; last = NULL; }

Node::Node(int n, string k)
{
    size = n;
    key = k;
    r = NULL; l = NULL;
    next = NULL;
}

Node::Node(int n, char k)
{
    key = '\0';
    size = n;
    key[0] = k;
    cout << key << endl;
    r = NULL; l = NULL;
    next = NULL;
}

void Add(tree* b, int n, char key)
{
    Node* p = new Node(n, key);
    if (b->first == NULL)
    {
        b->first = p;
        b->last = p;
        return;

    }
    b->last->next = p;
    b->last = p;
};

void swap(Node* a, Node* b, tree* c)
{
    Node* pred = c->first;

    if (a != c->first) {
        while (pred->next != a)
            pred = pred->next;
        pred->next = b;
    }
    if (a == c->first) c->first = b;
    if (b != c->last) {
        a->next = b->next;
    }
    if (b == c->last)
    {
        c->last = a; a->next = NULL;
    }
    b->next = a;
}

void newnode(tree* b)
{
    Node* beg = b->first;
    Node* p = new Node(beg->size + beg->next->size, beg->key + beg->next->key);

    cout << endl;
    p->l = beg;
    p->r = beg->next;
    p->next = b->first->next->next;
    b->first = p;
}

void dec(tree* b, fstream& fd)
{
    int t;
    fd >> t;
    fstream fk("текст.txt", ios::out);
    Node* tmp = b->first;
    char buf, bu;
    fd >> buf;
    while (fd)
    {
        
        for (int i = 7; i >= 0; i--)
        {
            if (!(tmp->l))
            {
                cout << ' ' << tmp->key << endl; fk << tmp->key; tmp = b->first;
            }
            if (fd >> bu||i!=t) {
     
                if (buf & 1 << i) {
                    tmp = tmp->r; cout << '1';
                }
                else {
                    tmp = tmp->l; cout << '0';
                }
                fd.seekg(-1, ios::cur);
            }
        }
        fd >> buf; 
    }
    
    
}


void out(tree* b)
{
    int u = 0;
    Node* tmp;
    tmp = b->first;
    while (tmp)
    {
        cout << tmp->key << '-' << tmp->size << ' ';
        tmp = tmp->next;
    }
    cout << endl;
}

int main()
{
    tree* b = new tree;
    char key; int size;
    int n = 0;
    fstream fc("D:/Текст1.txt");
    fc >> key;
    while (key != '+')
    {
        fc >> size;
        n++;
        Add(b, size, key);
        fc >> key;
    }
    out(b);
    int t = 2 * n + 1;
    while (b->first->next != NULL) {

        for (int i = 0; i <= n - 2; i++)
        {

            Node* tmp = b->first;
            for (int j = 0; j <= n - 2; j++)
            {

                if (tmp->size > tmp->next->size)
                {
                    Node* t1 = tmp->next;
                    swap(tmp, tmp->next, b);
                    tmp = t1;
                }
                tmp = tmp->next;

            }
        } out(b);
        newnode(b);
        n--;
    };
    
    fc.seekg(t, ios::beg);
    dec(b, fc);
    
    

}