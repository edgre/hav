#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <vector>
#include <locale.h>

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

    p->l = beg;
    p->r = beg->next;

    Node* tmp = b->first->next;

    while (tmp != b->last && tmp->next->size < p->size) tmp = tmp->next;
    p->next = tmp->next; tmp->next = p;
    if (tmp == b->last) b->last = p;
    if (!(b->first->next->next)) b->first = p;
    else
        b->first = b->first->next->next;
    
}

void dec(tree* b, int t, int &weigh)
{
        
        fstream fk("итог.txt", ios::out);
        ifstream fd("C:/Users/Дима и Егор/Source/repos/edgre/hav/код.txt", ios::binary);
        Node* tmp = b->first;
        char buf, bu;
        fd.get(buf); weigh++;
        int pr = 0;
        bu = 0;
        while (fd)
        {
            if (!(fd.get(bu)))  pr = 1;// проверяем является ли текущий символ последним
            
            
            for (int i = 7; i >= 0; i--)
            {
                if (((int)buf!=13||(int)bu!=10)&&(pr == 0 || i >= t)) 
                    // в последнем остананвливаемся на незначащих нулях 
                {
                    if (buf & 1 << i) {
                        tmp = tmp->r; /*cout << '1';*/
                    }
                    else {
                        tmp = tmp->l; /*cout << '0';*/
                    }
                    if (!(tmp->l))
                    {
                        fk << tmp->key; tmp = b->first;/*cout << endl*/
                    }

                }
            }
            buf = bu;
            /*cout << (int)  buf << endl;*/ weigh++;

           
           
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
    
}

bool proof()
{
    fstream fc("итог.txt");
    fstream fs("C:/Users/Дима и Егор/Source/repos/edgre/hav/ConsoleApplication27/исходный текст.txt");
    char sim, sim1;
    fc.get(sim); fs.get(sim1);
    while (fs || fc)
    { 
      if (sim != sim1) return false;
        fc.get(sim); fs.get(sim1);
        
        
    }
    return true;
}

void weigh(int t)
{
    fstream fs("C:/Users/Дима и Егор/Source/repos/edgre/hav/ConsoleApplication27/исходный текст.txt");
    char buf; int r = 0;
    
    while (fs) 
    {
        r++; fs.get(buf);
    }
    cout << "исходный файл -" << r * 8 << endl;
    cout << "сжатый файл -" << t * 8 << endl;

}

int main()
{
    setlocale(LC_ALL, "Russian");
    tree* b = new tree;
    char key; int size;
    int n = 0;
    fstream fc("C:/Users/Дима и Егор/Source/repos/edgre/hav/частоты.txt");
    fc.get(key);
    fc>>size;
    // считываем символы исходного текста и их частоты
    while (key != '|'&&size!='|')
    {   
        n++;
        Add(b, size, key);
        fc.get(key);
        fc>>size;
    }
    int t = n * 2 + 2;
    // формируем дерево
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
        } 
        while (b -> first->next!= NULL)
        {
            newnode(b);
        
        }
        fc.close();
        fc.open("C:/Users/Дима и Егор/Source/repos/edgre/hav/частоты.txt");
        fc.seekg(-1, ios::end);
        fc >> t; // считываем количество незначащих нулей
        /*cout << t << endl;*/
        fc.close(); int mas = 0;
        dec(b,t, mas);// декодируем текст
    
    fc.close();
    if (proof()) cout << "совпали" << endl;// проверяем  правильность декодирования
    else cout << "не совпали";
    weigh(mas);
    
    

}