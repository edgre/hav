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
        tmp = tmp->next;
        cout << tmp->key << ' ' << tmp->size;
    }
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


/*функция проходит формирует код символа по дереву*/
void search(std::map<char, vector<bool>>& mp, char k, Node* tmp)
{
    if (tmp->l || tmp->r)
    {

        if (tmp->l&&tmp->l->key.find(k) != -1)
        {
            mp[k].push_back(0); tmp = tmp->l;
        };
        if (tmp->r && tmp->r->key.find(k) != -1)
        {

            mp[k].push_back(1); tmp = tmp->r;
        }
        search(mp, k, tmp);
        
    }


}

void newnode(tree* b)
{   // создаем предка для двух узлов с наименьшим весом
    Node* beg = b->first;
    Node* p = new Node(beg->size + beg->next->size,
        beg->key + beg->next->key);
    
    p->l = beg;
    p->r = beg->next;
    
    Node *tmp = b->first->next;
   // помещаем его на нужную позицию
            while (tmp != b->last && tmp->next->size < p->size)
                tmp = tmp->next;
            p->next = tmp->next; tmp->next = p;
            if (tmp == b->last) b->last = p;
            if (!(b->first->next->next)) b->first = p;
            else 
            b->first = b->first->next->next;
} 

int main()
{
    int asc[256];
    int n = 0;
    for (int i = 0; i < 256; i++) asc[i] = 0;
    fstream fc("исходный текст.txt");
    char sim;
    fc >> sim;
    while (fc) // заполняем ассоциированный массив
    {
        asc[(int)sim]++; 
        fc.get(sim);
    };
    tree* b = new tree;
    n = 0;
    map <char, vector<bool>> mp;
    fstream fd("C:/Users/Дима и Егор/Source/repos/edgre/hav/код.txt", ios::out);
    // файл для записи частот исходнго текста
    fstream fd1("C:/Users/Дима и Егор/Source/repos/edgre/hav/частоты.txt", ios::out);
    /* ненулевые элементы заносим в листья дерева, в ключи мапы и в файл*/ 
    fd1 << ' ';
    for (int i = 0; i < 256; i++) 
 
    {
        if (asc[i] != 0)
        {
            vector <bool> vec;
            mp.insert(pair<char, vector<bool>>(char(i), vec));
            Add(b, asc[i], (char)i); 
            fd1 << ' '; fd1 << char(i); fd1 << asc[i];
            n++;
        }
    }
    
    for (int i = 0; i <= n - 2; i++)
    {

        Node* tmp = b->first;
        for (int j = 0; j <= n - 2; j++) // сортируем листья дерева
        {

            if (tmp->size > tmp->next->size)
            {
                Node* t1 = tmp->next;
                swap(tmp, tmp->next, b);
                tmp = t1;
            }
            tmp = tmp->next;

        }
    } 
    while (b->first->next != NULL)
    {   
        newnode(b);
    }


    map<char, vector<bool>>::iterator it = mp.begin();
    Node* tmp = b->first;
    // заполняем мапу кодами символов
    while (it != mp.end())
    {
        search(mp, it->first, tmp);
        /*cout << it->first<<'-';
        for (int i =0 ; i < mp[it->first].size(); i++)
            cout << mp[it->first][i];
        cout << endl;*/
        it++;

    }
    char buf = 0;
    fc.close();
    fc.open("исходный текст.txt", ios::in);

    it = mp.begin();
    int siz = 7;
    fc.get(sim);
    buf = 0; // начиная справа, формируем символ из получившихся кодов
    
    while (fc)
    {   
        it = mp.find(sim);
        for (int i = 0; i < mp[it->first].size(); i++)
        {
            buf = buf | mp[it->first][i] << siz;
            /*cout << mp[it->first][i];*/
            siz--;
            if (siz < 0)
            {
                siz = 7; /*cout << (int)buf << endl;*/ fd << buf; buf = 0;
                
            }
        }
        fc.get(sim); 
    }
    if (siz != 7) {
        fd << buf; /*cout << (int)buf<<endl;*/
    } // заносим последний (неполный) символ
    
    else siz = -1; //если неполных нет, то незначащие нули в конце не учитываем
    fd.close();
    fd1.seekp(0, ios::beg);
    fd1 << siz+1;//заносим в файл количество незначащих нулей
    fd1.close(); fd.close();
    
    
}

