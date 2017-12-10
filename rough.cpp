#include<bits/stdc++.h>

#define ERROR -99999999

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
//------------------------------------------------------------------------------------------------------------------------------
void BFS(int s,int N,int D,Color* colour,int* Level,int* pi,int** Adj,int *treeEdges,int *backEdges,int *crossEdges,int* level);
int main()
{
	int N,D,s,i,j;
	cin>>N>>D>>s;
	s--;
	Color *colour=new Color[N];
    int *Level=new int[N];
    int *pi=new int[N];
    int *countLevel=new int[N];
    int **Adj=new int*[N];
    for(i=0;i<N;i++)
        Adj[i]=new int[N];
    for(i=0;i<N;i++)
    {
    	for(j=0;j<N;j++)
    		cin>>Adj[i][j];
    	colour[i]=WHITE;
    	countLevel[i]=0;
    }
    int treeEdges,backEdges,forwardEdges,crossEdges;
    treeEdges=backEdges=forwardEdges=crossEdges=0;
    int level=0;
    BFS(s,N,D,colour,Level,pi,Adj,&treeEdges,&backEdges,&crossEdges,&level);
    // cout<<level<<endl;
    // for(i=0;i<N;i++)
    // 	cout<<colour[i]<<" ";
    // cout<<endl;
    for(i=0;i<N;i++)
    {
    	if(colour[i]==WHITE)
    	{
    		level++;
    		BFS(i,N,D,colour,Level,pi,Adj,&treeEdges,&backEdges,&crossEdges,&level);
    	}
    }
    // cout<<level<<endl;
    // for(i=0;i<N;i++)
    // 	cout<<colour[i]<<" ";
    // cout<<endl;
    for(i=0;i<N;i++)
    	countLevel[Level[i]]++;
    for(i=1;i<N;i++)
    {
    	cout<<countLevel[i]<<" ";
    	if(countLevel[i]==0)
    		break;
    }
    if(i==N&&countLevel[i-1]!=0)
    	cout<<0<<" ";
    if(D)
    	cout<<treeEdges<<" "<<backEdges<<" "<<forwardEdges<<" "<<crossEdges<<endl;
    else
    	cout<<treeEdges<<" "<<crossEdges<<endl;
    delete[] colour;
    delete[] Level;
    delete[] countLevel;
    for(i=0;i<N;i++)
        delete[] Adj[i];
    delete[] Adj;
    delete[] pi;
}

void BFS(int s,int N,int D,Color* colour,int* Level,int* pi,int** Adj,int *treeEdges,int *backEdges,int *crossEdges,int* level)
{
	int u,i,j;
	Level[s]=(*level);
	IntQueue Q;
	colour[s]=GREY;
	Q.Enqueue(s);
	while(!Q.isEmpty())
	{
		u=Q.Front();
		Q.Dequeue();
		for(i=0;i<N;i++)
		{
			if(Adj[u][i])
			{
				if(colour[i]==WHITE)
				{
					colour[i]==GREY;
					Level[i]=Level[u]+1;
					(*level)=max((*level),Level[i]);
					Q.Enqueue(i);
					pi[i]=u;
				}
				else if(D==0 && colour[i]==GREY)
                    (*crossEdges)++;
				else if(D==1)
                {
                    bool parent = 0;
                    j=pi[u];
                    while(1)
                    {
                        if(i==j)
                        {
                            parent=1;
                            break;
                        }
                        if(j==s)
                            break;
                        j=pi[j];
                    }
                    if(parent)
                        (*backEdges)++;
                    else (*crossEdges)++;
                }
			}
		}
		colour[u]=BLACK;
	}

}

//---------------------------------------------------------------------------------------------------------------------------------
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
