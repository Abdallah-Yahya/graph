#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <math.h>
using namespace std;
class graph1 {
private:
    int v1;
    int v2;
    float weight;
    int* parent;
    int nodes;
public:
    inline graph1() {
        v1 = 0;
        v2 = 0;
        weight = 0;
    }

    void setnodes(int n) {
        nodes = n;
    }
    void setparent() { parent = new int[nodes + 1]; }
    int getparent(int i) { return parent[i]; }
    int getnodes() { return nodes; }
    void set(int t1, int t2, float wt) {
        v1 = t1;
        v2 = t2;
        weight = wt;
    }
    int getv1()const {
        return v1;
    }
    int getv2()const {
        return v2;
    }
    int size()const {
        return nodes;
    }
    int getweight()const {
        return weight;
    }
    void MakeSet(int i) {
        parent[i] = -1;
    }
    int Find(int x)
    {
        int r, s, t;
        r = x;
        while (parent[r] > 0)
        {
            r = parent[r];
        }
        s = x;
        while (s != r)
        {
            t = s;
            s = parent[s];
            parent[t] = r;
        }
        return r;
    }

    void Union(int i, int j)
    {
        int x = Find(i);
        int y = Find(j);
        if (x != y)
        {
            if (abs(parent[x]) >= abs(parent[y]))
            {
                parent[x] = parent[x] + parent[y];
                parent[y] = x;
            }
            else
            {
                parent[y] = parent[x] + parent[y];
                parent[x] = y;
            }
        }
    }
    void printp()
    {
        cout << "The final parent array: ";
        for (int i = 1; i <= nodes; i++)
        {
            cout << parent[i] << " , ";
        }
        cout << endl;
    }

    void PrintSets()
    {
        static int count = 1;
        cout << "Step" << count << ": ";
        for (int i = 1; i < nodes + 1; i++)
        {
            if (parent[i] < -1)
            {
                cout << " { " << i;
                for (int j = 1; j < nodes + 1; j++)
                {
                    if (parent[j] == i)
                        cout << " , " << j;
                }
                cout << " } ";
            }
        }
        for (int i = 1; i < nodes + 1; i++)
        {
            if (parent[i] == -1)
                cout << " { " << i << " } ";
        }
        cout << endl;
        count++;
    }
};
void sort(graph1* a, int si)
{
    for (int i = 0; i < si; i++)
        for (int j = i; j < si; j++)
        {
            if (a[i].getweight() > a[j].getweight())
            {
                graph1 t;
                t.set(a[i].getv1(), a[i].getv2(), a[i].getweight());
                a[i].set(a[j].getv1(), a[j].getv2(), a[j].getweight());
                a[j].set(t.getv1(), t.getv2(), t.getweight());
            }
        }
}
int connect(graph1* l, int size, int& nodes) {
    sort(l, size);
    for (int i = 1; i <= nodes; i++) {
        l->MakeSet(i);
    }
    int x = 1;
    int count = 0;
    while (count < nodes - 1) {
        count++;
        l->Union(l[x].getv1(), l[x].getv2());
        x++;
    }

    int count1 = 0;
    for (int j = 1; j <= nodes; j++) {
        if (l->getparent(j) < 0) {
            count1++;
        }
    }
    return count1;
}

void mstKruskal(graph1* a, int ss) // more detailed
{
    sort(a, ss);
    for (int i = 1; i <= a->getnodes(); i++)
        a->MakeSet(i);


    int count = 0;
    int x = 1;
    int* s = new int[a->getnodes()];
    int tt = 1;
    int w = 0;
    while (count < a->getnodes() - 1) {

        if (a->Find(a[x].getv1()) != a->Find(a[x].getv2()))
        {
            //cout << "("<<a[i].getv1() << "," << a[i].getv2() << ") ,";
            s[tt] = a[x].getv1();
            tt++;
            s[tt] = a[x].getv2();
            tt++;
            count++;
            w += a[x].getweight();
            a->PrintSets();
            a->Union(a[x].getv1(), a[x].getv2());
        }
        x++;
    }

    a->PrintSets();
    cout << endl;
    a->printp();
    cout << "The MST edges:";
    for (int p = 1; p < tt; p++) {
        cout << "(" << s[p];
        p++;
        cout << "," << s[p] << ")";

    }
    cout << endl;
    cout << "The weight of the MST is:" << w << endl;

}

void check(int v1, int v2, graph1* a, int i, int nodes, int* count)
{
    int s = 0;
    for (int r = 0; r < i; r++)
    {
        if (v1 == a[r].getv1() || v1 == a[r].getv2())
        {
            s++;

        }

    }
    if (s == 0)
    {
        *count = *count + 1;

    }
    s = 0;
    for (int r = 0; r < i; r++)
    {
        if (v2 == a[r].getv1() || v2 == a[r].getv2() || v2 == v1)
        {
            s++;
        }
    }
    if (s == 0)
    {
        *count = *count + 1;
    }
}
void matr(float** mat, int nodes, int v1, int v2, int weight, int* count)
{
    int s = 0;
    for (int r = 0; r <= nodes; r++)
        if (v1 == mat[0][r])
            s++;
    if (s == 0)
    {
        *count = *count + 1;
        mat[*count][0] = v1;
        mat[0][*count] = v1;
    }
    s = 0;
    for (int r = 0; r <= nodes; r++)
        if (v2 == mat[r][0])
            s++;
    if (s == 0)
    {
        *count = *count + 1;
        mat[*count][0] = v2;
        mat[0][*count] = v2;

    }




}
void storee(float** mat, int v1, int v2, float weight, int nodes)
{
    int i, j;
    for (i = 0; i < nodes + 1; i++)
        if (mat[0][i] == v1)
            break;

    for (j = 0; j < nodes + 1; j++)
        if (mat[j][0] == v2)
            break;
    mat[j][i] = weight;
    mat[i][j] = weight;
}
void printmat(float** mat, int nodes)
{
    int i, j;
    for (i = 1; i <= nodes; i++)
    {
        for (j = 1; j <= nodes; j++)
            if (mat[i][j] != 0)
            {
                cout << "Edge" << "(" << mat[0][i] << "," << mat[j][0] << ")" << "has the weight" << mat[i][j] << endl;
                //cout << "Edge" << "("<<mat[j][0]<<"," <<  mat[0][i]<<")"<< "has the weight" << mat [i][j] << endl;

            }

    }
}
class node
{
private:

public:
    int v;
    float weight;
    node* next;
    inline node() {
        v = 0;
        weight = 0;
        next = NULL;
    }
    /*
      ~node(){}
      void setv (int v1 )
      {
          v = v1 ;
      }
      void setw (float w )
      {
          weight = w ;
      }
      void setnext (node * p )
      {
          next = p ;
      }
      node * getnext ()
      {
          return  next;

      }
      int  getv ()
      {
          return  v;

      }
      float  getw ()
      {
          return  weight;

      }*/

};
class arrlin
{
private:

public:
    int v;
    node* next;
    inline arrlin() {
        v = 0;
        next = NULL;
    }
    /*  ~arrlin(){}
     node * getnext () const
      {return next;}
      int  getv () const
       {return v;}
      void setv (int v1 )
      {
          v = v1 ;
      }
      void setnext (node * r )
      {
          next = r ;
      }*/


};
void add(arrlin* lin, int v, float w)
{
    node* p;
    p = new node;
    p->v = v;
    p->weight = w;
    p->next = NULL;
    node* p1;
    p1 = lin->next;
    lin->next = p;
    p->next = p1;
    node* p3;
    p3 = lin->next;
}
int searchh(arrlin* lin, int nodes, int v1, int v2)
{
    int i;
    node* p = NULL;
    for (i = 0; i < nodes; i++)
        if (lin[i].v == v1)
        {
            p = lin[i].next;
            break;

        }
    for (; p != NULL; p = p->next)
        if (p->v == v2)
            return 0;

    return 1;

}
int check2(arrlin* lin, int nodes, int v1, int v2, int* count, float w)
{
    if (w == 0)
        return 0;
    if (searchh(lin, nodes, v1, v2) == 0)
        return 0;
    int s = 0;
    int rr = *count;
    int ch = 0;
    for (int i = 0; i < nodes; i++)
    {
        if (lin[i].v == v1)
        {
            add(&lin[i], v2, w);

            s++;

        }
    }
    if (s == 0)
    {
        *count = *count + 1;
        if ((*count <= nodes))
        {
            ch++;
            lin[*count - 1].v = (v1);
            add(&lin[*count - 1], v2, w);
        }

    }
    s = 0;

    for (int i = 0; i < nodes; i++)
    {
        if (lin[i].v == v2)
        {
            add(&lin[i], v1, w);

            s++;
        }
    }
    if (s == 0)
    {
        ch++;
        *count = *count + 1;
        if ((*count <= nodes))
        {
            lin[*count - 1].v = (v2);
            add(&lin[*count - 1], v1, w);
        }

    }
    if (*count > nodes)
    {
        if (ch == 2)
        {
            lin[*count - 2].next = NULL;
            lin[*count - 2].v = 0;
        }

        *count = rr;
        return 0;
    }

    return 1;

}
void print(arrlin  lin)
{
    node* p1 = lin.next;

    for (; p1->next != NULL; p1 = p1->next)
        cout << "Edge" << "(" << lin.v << "," << p1->v << ")" << "has the weight" << p1->weight << endl;
    cout << "Edge" << "(" << lin.v << "," << p1->v << ")" << "has the weight" << p1->weight << endl;


}
void inter(graph1* a, graph1* a1, int size, int size1)
{
    int v1, v2, weight;
    int ch = 0;
    for (int i = 0; i < size; i++)
    {
        for (int s = 0; s < size1; s++)
            if ((a[i].getv1() == a1[s].getv1() && a[i].getv2() == a1[s].getv2() && a[i].getweight() == a1[s].getweight()) || (a[i].getv1() == a1[s].getv2() && a[i].getv1() == a1[s].getv2() && a[i].getweight() == a1[s].getweight()))
            {
                ch = 1;
                v1 = a[i].getv1();
                v2 = a[i].getv2();
                weight = a[i].getweight();
                cout << "Edge" << "(" << v1 << "," << v2 << ")" << "has the weight" << weight << endl;
                cout << "Edge" << "(" << v2 << "," << v1 << ")" << "has the weight" << weight << endl;
            }

    }
    if (ch == 0)
        cout << "There no intersection between both graphs " << endl;
}
void union1(graph1* a, graph1* a1, int size, int size1)
{
    int v1, v2, weight;
    int flag = 0;
    int* p;
    p = new int[size1];
    int s1 = 0;
    for (int i = 0; i < size1; i++)
        p[i] = 0;
    for (int i = 0; i < size; i++)
    {
        flag = 0;

        for (int s = 0; s < size1; s++)
            if (((a[i].getv1() == a1[s].getv1() && a[i].getv2() == a1[s].getv2() && a[i].getweight() == a1[s].getweight()) || (a[i].getv1() == a1[s].getv2() && a[i].getv1() == a1[s].getv2() && a[i].getweight() == a1[s].getweight())))
            {
                p[s1] = 1;
                s1++;
                flag = 1;
                v1 = a1[s].getv1();
                v2 = a1[s].getv2();
                weight = a1[s].getweight();
                cout << "Edge" << "(" << v1 << "," << v2 << ")" << "has the weight" << weight << endl;
                cout << "Edge" << "(" << v2 << "," << v1 << ")" << "has the weight" << weight << endl;
            }

        if (flag == 0)
        {
            v1 = a[i].getv1();
            v2 = a[i].getv2();
            weight = a[i].getweight();
            cout << "Edge" << "(" << v1 << "," << v2 << ")" << "has the weight" << weight << endl;
            cout << "Edge" << "(" << v2 << "," << v1 << ")" << "has the weight" << weight << endl;
        }

    }
    for (int i = 0; i < size1; i++)
    {
        if (p[i] == 0)
        {
            v1 = a1[i].getv1();
            v2 = a1[i].getv2();
            weight = a1[i].getweight();
            cout << "Edge" << "(" << v1 << "," << v2 << ")" << "has the weight" << weight << endl;
            cout << "Edge" << "(" << v2 << "," << v1 << ")" << "has the weight" << weight << endl;
        }
    }
}
void highest(arrlin* lin, int nodes)
{
    node* p1;
    int* a;
    a = new int[nodes];
    for (int i = 0; i < nodes; i++)
    {
        p1 = lin[i].next;
        int s = 0;
        for (; p1 != NULL; p1 = p1->next, s++);
        a[i] = s;

    }
    int max = a[0];
    int index = 0;
    for (int i = 0; i < nodes; i++)
        if (a[i] > max)
        {
            max = a[i];
            index = i;
        }
    cout << lin[index].v << " with the degree of" << max << endl;




}
int supp(graph1* a, graph1* a1, int size, int size1)
{
    int ch = 0;
    for (int i = 0; i < size; i++)
    {
        for (int s = 0; s < size1; s++)
            if ((a[i].getv1() == a1[s].getv1() && a[i].getv2() == a1[s].getv2() && a[i].getweight() == a1[s].getweight()) || (a[i].getv1() == a1[s].getv2() && a[i].getv1() == a1[s].getv2() && a[i].getweight() == a1[s].getweight()))
            {
                ch++;
            }

    }
    return ch;
}

int main() {
    cout << "Please enter the number of nodes in A:" << endl;
    int nodes;
    cin >> nodes;
    cout << "Please enter the number of edges in A: " << endl;
    int size;
    cin >> size;
    arrlin* lin;
    lin = new arrlin[nodes];
    int v1, v2;
    float weight;
    int count = 0;

    float** mat;
    int y = nodes + 1;
    mat = new float* [y];
    for (int i = 0; i < y; i++)
        mat[i] = new float[y];

    for (int i = 0; i < y; i++)//1
        for (int r = 0; r < y; r++)
        {
            mat[i][r] = 0;
        }

    int count1 = 0;

    graph1* a;
    a = new graph1[size];
    a->setnodes(nodes);
    a->setparent();

    int count2 = 0;
    for (int i = 1; i <= size; i++)
    {
        cout << "Please enter  edge " << i + 1 << " and it is weight in the order " << " ( vertax1 ,vertax2 , weight ) :" << endl;
        cin >> v1 >> v2 >> weight;

        while (check2(lin, nodes, v1, v2, &count, weight) == 0)
        {
            cout << "Please renter  edge " << i + 1 << " and it is weight in the order " <<
                " ( vertax1 ,vertax2 , weight ) :" << endl;
            cin >> v1 >> v2 >> weight;

        }
        matr(mat, nodes, v1, v2, weight, &count1);
        storee(mat, v1, v2, weight, nodes);

        (check(v1, v2, a, i, nodes, &count2));
        a[i].set(v1, v2, weight);
    }

    int cc = connect(a, size, nodes);
    if (cc == 1) {
        cout << "The graph is connected, it has one connected component." << endl;
        mstKruskal(a, size);

    }
    else
        cout << "The graph is not connected, it has 2 connected components.The graph does not have a spanning tree because it is not connected.";



    /*cout << "Please enter the number of nodes in B:" << endl;
    int node;
    cin >> node;
    cout << "Please enter the number of edges in B: " << endl;
    int size1;
    cin >> size1;
    arrlin* lin1;
    lin1 = new arrlin[node];
    int v11, v22;
    float weigh;
    int count3 = 0;
    float** matt;
    int ys = node + 1;
    matt = new float* [ys];
    for (int i = 0; i < ys; i++)
        matt[i] = new float[ys];

    for (int i = 0; i < ys; i++)//1
        for (int r = 0; r < ys; r++)
        {
            matt[i][r] = 0;
        }

    int count4 = 0;
    graph1* a1;
    a1 = new graph1[size1];
    int count5 = 0;

    for (int i = 0; i < size1; i++)
    {
        cout << "Please enter  edge " << i + 1 << " and it is weight in the order " << " ( vertax1 ,vertax2 , weight ) :" << endl;
        cin >> v11 >> v22 >> weigh;
        while (check2(lin1, node, v11, v22, &count3, weigh) == 0)
        {
            cout << "Please renter  edge " << i + 1 << " and it is weight in the order " << " ( vertax1 ,vertax2 , weight ) :" << endl;
            cin >> v11 >> v22 >> weigh;

        }
        matr(matt, node, v11, v22, weigh, &count4);
        storee(matt, v11, v22, weigh, node);
        check(v11, v22, a1, i, node, &count5);
        a1[i].set(v11, v22, weigh);

        for (int i = 0; i < size; i++)
        {
            v1 = a[i].getv1();
            v2 = a[i].getv2();
            weight = a[i].getweight();
            cout << "Edge" << "(" << v1 << "," << v2 << ")" << "has the weight" << weight << endl;
            cout << "Edge" << "(" << v2 << "," << v1 << ")" << "has the weight" << weight << endl;
        }
    }*/

    /* int cho;
     cho = 0;
     while (cho != 14)
     {
         cout << "Please select one of the following:" << endl;

         cout << "1- Output graph A from the array of lists " << endl

             << "2- Output graph A from the matrix" << endl
             << "3- Output graph A from the array of structures/objects." << endl

             << "4- Output graph B from the array of lists" << endl

             << "5- Output graph B from the matrix " << endl

             << "6- Output graph B from the array of structures/objects. " << endl

             << "7- The intersection between both graphs " << endl

             << "8- The union of the two graphs" << endl

             << "9- Is graph (A) a subgraph of graph (B)?" << endl
             << "10- Is graph (B) a subgraph of graph (A)? " << endl
             << "11- Display the vertex (vertices) with the highest degree from graph A." << endl

             << "12- Display the vertex (vertices) with the highest degree from graph B." << endl

             << "13- Are the graphs equal (the same graph)? " << endl

             << "14- Exit program" << endl;
         cin >> cho;
         if (cho == 1)
         {
             for (int i = 0; i < size; i++)
             {
                 v1 = a[i].getv1();
                 v2 = a[i].getv2();
                 weight = a[i].getweight();
                 cout << "Edge" << "(" << v1 << "," << v2 << ")" << "has the weight" << weight << endl;
                 cout << "Edge" << "(" << v2 << "," << v1 << ")" << "has the weight" << weight << endl;
             }
         }

         if (cho == 2)
         {
             printmat(mat, nodes);

         }
         if (cho == 3)
         {
             for (int i = 0; i < nodes; i++)
                 print(lin[i]);

         }
         if (cho == 4)
         {
             for (int i = 0; i < size1; i++)
             {
                 v11 = a1[i].getv1();
                 v22 = a1[i].getv2();
                 weigh = a1[i].getweight();
                 cout << "Edge" << "(" << v11 << "," << v22 << ")" << "has the weight" << weigh << endl;
                 cout << "Edge" << "(" << v22 << "," << v11 << ")" << "has the weight" << weigh << endl;
             }
         }
         if (cho == 5)
         {
             printmat(matt, node);

         }
         if (cho == 6)
         {
             for (int i = 0; i < node; i++)
                 print(lin1[i]);
         }
         if (cho == 7)
         {
             inter(a, a1, size, size1);
         }

         if (cho == 8)
         {
             union1(a, a1, size, size1);
         }
         if (cho == 9)
         {
             if (supp(a, a1, size, size1) >= size)
                 cout << "yes" << endl;
             else
                 cout << "no" << endl;

         }
         if (cho == 10)
         {
             if (supp(a, a1, size, size1) >= size1)
                 cout << "yes" << endl;
             else
                 cout << "no" << endl;

         }
         if (cho == 11)
         {
             cout << "The vertex (vertices) with the highest degree in graph A:";
             highest(lin, nodes);

         }
         if (cho == 12)
         {
             cout << "The vertex (vertices) with the highest degree in graph B:";
             highest(lin1, node);
         }
         if (cho == 13)
         {
             if (supp(a, a1, size, size1) >= size1 && supp(a, a1, size, size1) >= size)
                 cout << "yes" << endl;
             else
                 cout << "no" << endl;
         }*/
}