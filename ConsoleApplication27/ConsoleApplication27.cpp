#include <iostream>
#include <fstream>
using namespace std;

struct Node;
struct Node
{   Node* r;
    Node* l;
    Node* next;
    int size;
    char* key;
    Node(int n = 0, char key = NULL);
};

struct tree
{
    Node* first;
    Node* last;
    tree();
};

tree::tree() { first = NULL; last = NULL; }

Node::Node(int n, char k)
{
    size = n; key = (char*)k;
    r = NULL; l = NULL; 
    next = NULL;
}

void Add(tree*b, int n, char key)
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

void out(tree* b)
{
    int u = 0;
    Node* tmp;
    tmp = b->first;
    while (tmp)
    {
        cout << tmp->size << ' ';
        tmp = tmp->next;
    }
}

void swap(Node* a, Node* b, tree* c)
{
    Node* pred = c->first;

    if (a!=c->first) {
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
    Node* p = new Node;
    Node* beg = b->first;
    p->size = beg->size + beg->next->size;
    p->key = strcat(beg->key, beg->next->key);
    p->l = beg;
    p->r = beg->next;
    p->next = beg->next->next;
    b->first = p;
}

int main()
{
    int asc[256];
    int n = 0;
    for (int i = 0; i < 256; i++) asc[i] = 0;
    fstream fc("текст.txt");
    char sim;
    fc >> sim;
    while (fc)
    {
        asc[(int)sim]++;
        fc >> sim;
    };
    tree* b = new tree;
    for (int i = 0; i < 256; i++)
    {
        cout << asc[i] << ' ';
    }
    cout << endl;
     n = 0;
     for (int i = 0; i < 256; i++)
     {
         if (asc[i] != 0)
         {
             Add(b, asc[i], (char)i);
             n++;
         }
     }
     cout << n << endl;
     out(b);
     cout << endl;
for (int i = 0; i <= n - 2; i++)
{
    Node* tmp = b->first;
    for (int j = 0; j <= n - 2; j++)
    { 
        
        if (tmp->size > tmp->next->size)
        {
            
            swap(tmp, tmp->next, b);
        }

       }

   }
out(b); cout << endl;
newnode(b); out(b);
}
