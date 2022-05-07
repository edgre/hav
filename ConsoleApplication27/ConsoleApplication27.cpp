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

Node::Node(int n, char k)
{
    key = '\0';
    size = n;
    key[0] = k;
    cout << key << endl;
    r = NULL; l = NULL;
    next = NULL;
}

Node::Node(int n, string k)
{
    size = n;
    key = k;
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

void out(tree* b)
{
    int u = 0;
    Node* tmp;
    tmp = b->first;
    while (tmp)
    {
        cout <<tmp->key<<'-'<< tmp->size << ' ';
        tmp = tmp->next;
    }
    cout << endl;
}

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



void search(std::map<char, vector<bool>>& mp, char k, Node* tmp)
{
    if (tmp->l || tmp->r)
    {

        if (tmp->l&&tmp->l->key.find(k) != -1)
        {
            mp[k].push_back(0); tmp = tmp->l;
        };
        if (tmp->r&&tmp->r->key.find(k) != -1)
        {

            mp[k].push_back(1); tmp = tmp->r;
        }
        search(mp, k, tmp);
    }


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
    map <char, vector<bool>> mp;
    fstream fd("D:/Текст1.txt", ios::out|ios::binary);
    for (int i = 0; i < 256; i++)
    
    {
        if (asc[i] != 0)
        {
            vector <bool> vec;
            mp.insert(pair<char, vector<bool>>(char(i), vec));
            Add(b, asc[i], (char)i);
            fd << char(i); fd << asc[i];
            n++;
        }
    }
    fd << "+";
    cout << n << endl;
    out(b);
    int t = n * 2 + 1;
    cout << endl;
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
    cout << b->first->l->l->key << endl;

    map<char, vector<bool>>::iterator it = mp.begin();
    Node* tmp = b->first;
    while (it != mp.end())
    {
        cout << it->first << endl;
        search(mp, it->first, tmp);
        cout << it->first << '-';
        for (int i = 0; i < mp[it->first].size(); i++)
            cout << mp[it->first][i];
        cout << endl;
        it++;


    }
    char buf = 0;
    fc.close();
    fc.open("текст.txt", ios::in);
    
    it = mp.begin();
    int siz = 7;
    fc >> sim;
    buf = 0;
    while (fc)
    { 
        it = mp.find(sim);
        for (int i = 0; i < mp[it->first].size(); i++)
        {
            cout << mp[it->first][i];
            buf = buf | mp[it->first][i] << siz;
            siz--;
            if (siz < 0)
            {
                cout  <<'-'<< (int)buf << endl; siz = 7; fd << buf;
                buf = 0;
            } 
        } 
        fc >> sim; 
    }
    fd << buf;
    cout << endl;
    cout << (int)buf<<endl;
    fd.close();
    fd.open("D:/Текст1.txt");
    t = t;
    fd.seekp(t, ios::beg);
    cout << siz<<endl;
    fd << siz;
    fd.close();
}

