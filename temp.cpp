#include<bits/stdc++.h>

#define ERROR -99999

using namespace std;


//----------------------------------------------------------------Node Structures

struct Node
{
    int data;
    Node *next;
};

//----------------------------------------------------------------Classes------------------------------------------------------------

class IntLL //Integer Linked List
{
    Node *head;
    Node *tail;
    int size;
public:
    IntLL();
    //~IntLL();
    void Insert(int x,int pos=-1); //By Default Insert at end
    void Delete(int pos=0);  //By default delete at the beginning
    void Print();
    int SizeLL();
    void freeLL();
    int Element(int pos=0);
};

class IntQueue
{
    IntLL L;
public:
    //IntQueue();
    //~IntQueue();
    void Enqueue(int x);
    void Dequeue();
    int Front();
    bool isEmpty();
    int SizeQueue();
    void freeQueue();
    
};

//---------------------------------------------------------Function Declarations-----------------------------------------------------
void Function1();
void Function2();
void Function3();
void Function4();
void Function5();
void Function6();

//---------------------------------------------------------------Main----------------------------------------------------------------
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t,q;
    cin>>t;
    while(t--)
    {
        cin>>q;
        switch(q)
        {
            case 1: Function1();
                    break;
            case 2: Function2();
                    break;
            case 3: Function3();
                    break;
            case 4: Function4();
                    break;
            case 5: Function5();
                    break;
            case 6: Function6();
                    break;
            default: cout<<"Error"<<endl;
        }
    }
    return 0;
}

//------------------------------------------------------------Function Definitions----------------------------------------------------

//-----------------------------------------------------------------BFS

void Function1()
{
    int N,D,s,i,j;
    cin>>N>>D>>s;
    int **Adj=new int*[N];
    for(i=0;i<N;i++)
        Adj[i]=new int[N];
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            cin>>Adj[i][j];
        }
    }
}

void Function2()
{
    int N,D,s;
    cin>>N>>D>>s;
}

void Function3()
{

}

void Function4()
{
    int N,D,s;
    cin>>N>>D>>s;
}

void Function5()
{
    int N,D,s;
    cin>>N>>D>>s;
}

void Function6()
{

}

//--------------------------------------------------------Class IntLL Functions------------

IntLL::IntLL()
{
    head=tail=NULL;
    size=0;
    //cout<<"Head and Tail Initialized\n";
}

void IntLL::Insert(int x, int pos)
{
    //pos =-1 is insert at tail
    //pos = 0 is insert at head
    if(pos>size&&pos<-1)
    {
        cout<<"Invalid Postion of Insertion in Linked List.\n";
        return;
    }
    Node *newNode=new Node();
    newNode->data=x;
    if(size==0)  //Empty Linked List
    {
        head=tail=newNode;
        newNode->next=NULL;
    }
    else if(pos==0)  //Insert at Head
    {
        newNode->next=head;
        head=newNode;
    }
    else if(pos==size||pos==-1) //Insert at end;
    {
        tail=tail->next=newNode;
        newNode->next=NULL;
    }
    else //Insert in between
    {
        Node* temp=head;
        for(int i=0;i<pos-1;i++)
            temp=temp->next;
        newNode->next=temp->next;
        temp->next=newNode;
    }
    //cout<<head<<" "<<tail<<" Inserted location and value"<<newNode<<" "<<x<<endl;
    size++;
}

void IntLL::Print()
{
    Node *temp=head;
    while(temp!=NULL)
    {
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<"\n";
}

int IntLL::SizeLL()
{
    return size;
}

void IntLL::Delete(int pos)
{
    Node *temp=head;
    if(pos<0 && pos>=size)
    {
        cout<<"Invalid Delete Position in Linked List\n";
        return;
    }
    if(pos==0)
    {
        head=temp->next;
    }
    else
    {
        for(int i=0;i<pos-1;i++)
            temp=temp->next;
        Node *temp2=temp;
        temp=temp->next;
        temp2->next=temp->next;
        if(pos==size-1)
            tail=temp2;
    }
    temp->next=NULL;
    free(temp);
    size--;
}

void IntLL::freeLL()
{
    Node *temp=head;
    Node *temp2;
    head=tail=NULL;
    while(temp!=NULL)
    {
        temp2=temp;
        temp=temp->next;
        temp2->next=NULL;
        free(temp2);
    }
}
int IntLL::Element(int pos)
{
    if(pos>=size)
    {
        //cout<<"Invalid Position\n";
        return ERROR;
    }
    if(pos==0)
        return head->data;
    if(pos==size-1)
        return tail->data;
    Node *temp=head;
    for(int i=0;i<pos;i++)
        temp=temp->next;
    return temp->data;
}


//---------------------------------------------------- Class IntQueue Functions
void IntQueue::Enqueue(int x)
{
    L.Insert(x);
}
void IntQueue::Dequeue()
{
    if(!L.SizeLL())
        return;
    else
        L.Delete();
}
int IntQueue::Front()
{
    return L.Element();
}
bool IntQueue::isEmpty()
{
    return !L.SizeLL();
}
int IntQueue::SizeQueue()
{
    return L.SizeLL();
}
void IntQueue::freeQueue()
{
    L.freeLL();
}