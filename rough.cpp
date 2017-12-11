#include<bits/stdc++.h>

#define ERROR -99999999
#define INF 999999

using namespace std;

enum Color
{
	WHITE,GREY,BLACK
};
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
//---------------------------------------------------------------------Main function-------------------------------------------------
int main()
{
	int N,D,s,i,j,x,n,u,len;
	int MIN=INF;
    cin>>N>>D>>s;
    s--;
    IntQueue *AdjWeight=new IntQueue[N];
    IntQueue *AdjNode=new IntQueue[N];
    Color *colour=new Color[N];
    int *dist=new int[N];
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            cin>>x;
            if(x<MIN)
            	MIN=x;
            if(x!=INF && i!=j)
            {
                AdjWeight[i].Enqueue(x);
                AdjNode[i].Enqueue(j);
            }
        }
        dist[i]=INF;
        colour[i]=WHITE;
    }
    int countRelax,countModification;
    countRelax=countModification=0;
    IntQueue Q;
    dist[s]=0;
    Q.Enqueue(s);
    colour[s]=GREY;
    while(!Q.isEmpty())
    {
    	u=Q.Front();
    	Q.Dequeue();
    	colour[u]=WHITE;
    	len=AdjNode[u].SizeQueue();
    	for(i=0;i<len;i++)
    	{
    		x=AdjWeight[u].Front();
    		AdjWeight[u].Dequeue();
    		n=AdjNode[u].Front();
    		AdjNode[u].Dequeue();
    		countRelax++;
    		if(dist[u]!=INF && dist[n]>dist[u]+x)
    		{
    			countModification++;
    			dist[n]=dist[u]+x;
    			if(dist[n]<MIN)                    //And hence graph has negative edge cycle.
    			{
    				cout<<-1<<endl;
    				delete[] AdjWeight;
    				delete[] AdjNode;
    				delete[] colour;
    				delete[] dist;
    				return 0;
    			}
    			if(colour[n]==WHITE)
    			{
    				colour[n]=GREY;
    				Q.Enqueue(n);
    			}
    		}
    		AdjWeight[u].Enqueue(x);
    		AdjNode[u].Enqueue(n);
    	}
    }
    for(int i=0;i<N;i++)
    	cout<<dist[i]<<" ";
    cout<<countRelax<<" "<<countModification<<endl;
    delete[] AdjWeight;
    delete[] AdjNode;
    delete[] colour;
    delete[] dist;
    return 0;
}


//-----------------------------------------------------Class IntLL functions-----------------------------------------------------
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
    cout<<endl;
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


//---------------------------------------------------- Class IntQueue Functions-----------------------------------------------------
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
