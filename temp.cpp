#include<bits/stdc++.h>

#define ERROR -99999
#define INF 999999

using namespace std;


enum Color
{
	WHITE,GREY,BLACK
};


//----------------------------------------------------------------Node Structures----------------------------------------------------

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

class IntStack
{
	IntLL L;
public:
	//IntStack();
	//~IntStack();
	void Push(int x);
	void Pop();
	int Top();
	bool isEmpty();
	int sizeStack();
	void freeStack();
};

//---------------------------------------------------------Function Declarations---------------------------------------------------
void DFS_VISIT(int u,int *TIME,Color *colour,int *pi,int *start,int *finish,int **Adj, int N,int *treeEdges,int *backEdges,int *forwardEdges,int *crossEdges,int D);
void BFS_VISIT(int s,Color *colour,int N,int **Adj,int *Level,int *level,int *pi,int* treeEdges, int* backEdges,int *crossEdges,int D);
void Function1();
void Function2();
void Function3();
void Function4();
void Function5();
void Function6();

//---------------------------------------------------------------Main-------------------------------------------------------------
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ofstream myfile;
    myfile.open("time.txt",ios::out);
    int t,q,i;
    cin>>t;
    for(i=0;i<t;i++)
    {
        cin>>q;
        clock_t begin = clock();
        if(q==1)
            Function1();
        else if(q==2)
            Function2();
        else if(q==3)
            Function3();
        else if(q==4)
            Function4();
        else if(q==5)
            Function5();
        else if(q==6)
            Function6();
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        myfile<<elapsed_secs<<" seconds"<<endl;
    }
    myfile.close();
    return 0;
}

//------------------------------------------------------------Function Definitions-------------------------------------------------

//-----------------------------------------------------------------BFS--------------------------------------------------------------

void Function1()
{
    int N,D,s,i,j,u,v;
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
        {
            cin>>Adj[i][j];
        }
        colour[i]=WHITE;
        countLevel[i]=0;
    }
    int treeEdges,backEdges,forwardEdges,crossEdges;
    treeEdges=backEdges=forwardEdges=crossEdges=0;
    //BFS Algorithm with modifications to calculate all required items.
    int level=0;
    Level[s]=level;
    BFS_VISIT(s,colour,N,Adj,Level,&level,pi,&treeEdges,&backEdges,&crossEdges,D);
    for(i=0;i<N;i++)
    {
        if(colour[i]==WHITE)
        {
            level++;
            Level[i]=level;
            BFS_VISIT(i,colour,N,Adj,Level,&level,pi,&treeEdges,&backEdges,&crossEdges,D); //---------------------------------------------------------------------------------------Calling BFS
        }
    }
    
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

void BFS_VISIT(int s,Color *colour,int N,int **Adj,int *Level,int *level,int *pi,int* treeEdges, int* backEdges,int *crossEdges,int D)
{
    int u,i,j;
    colour[s]=GREY;
    IntQueue Q;
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
                    Q.Enqueue(i);
                    Level[i]=Level[u]+1;
                    if(Level[i]>*level)
                        *level=Level[i];
                    (*treeEdges)++;
                    colour[i]=GREY; //Discovered
                    pi[i]=u;
                }
                else if(D==0 && colour[i]==GREY)
                    (*crossEdges)++;
                else if(D==1)
                {
                    bool parent = 0;
                    j=u;
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

//--------------------------------------------------------------DFS-----------------------------------------------------------------

void Function2()
{
    int N,D,s,TIME,i,j;
    cin>>N>>D>>s;
    TIME=0;
    s--;
    Color *colour=new Color[N];
    int *pi=new int[N];
    int *start=new int[N];
    int *finish=new int[N];
    int **Adj=new int*[N];
    for(i=0;i<N;i++)
        Adj[i]=new int[N];
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            cin>>Adj[i][j];
        }
        colour[i]=WHITE;
        pi[i]=-1;
    }
    int treeEdges,backEdges,forwardEdges,crossEdges;
    treeEdges=backEdges=forwardEdges=crossEdges=0;
    //DFS Algorithm
    i=s;
    pi[i]=-1;
    DFS_VISIT(i,&TIME,colour,pi,start,finish,Adj,N,&treeEdges,&backEdges,&forwardEdges,&crossEdges,D);
    for(i=0;i<N;i++)
    {
        if(colour[i]==WHITE)
        {
            pi[i]=-1;
            DFS_VISIT(i,&TIME,colour,pi,start,finish,Adj,N,&treeEdges,&backEdges,&forwardEdges,&crossEdges,D);
        }
    }
    if(D==1)
        cout<<finish[s]<<" "<<treeEdges<<" "<<backEdges<<" "<<forwardEdges<<" "<<crossEdges<<endl;
    else
    {
        backEdges=(backEdges-treeEdges)/2;
        cout<<finish[s]<<" "<<treeEdges<<" "<<backEdges<<endl;
    }
    //free memory from heap after completion
    delete[] pi;
    delete[] start;
    delete[] finish;
    for(i=0;i<N;i++)
        delete[] Adj[i];
    delete[] Adj;
}

void DFS_VISIT(int u,int *TIME,Color *colour,int *pi,int *start,int *finish,int **Adj, int N,int *treeEdges,int *backEdges,int *forwardEdges,int *crossEdges,int D)
{
    colour[u]=GREY;
    (*TIME)++;
    start[u]=*TIME;
    int i,v;
    for(i=0;i<N;i++)
    {
        if(Adj[u][i])
        {
            if(colour[i]==WHITE)
            {
               (*treeEdges)++;
                pi[i]=u;
                DFS_VISIT(i,TIME,colour,pi,start,finish,Adj,N,treeEdges,backEdges,forwardEdges,crossEdges,D);
            }
            else if(D==1)
            {
                if(colour[i]==GREY)
                    (*backEdges)++;
                else if(colour[i]==BLACK && start[u]<start[i])
                    (*forwardEdges)++;
                else
                    (*crossEdges)++;
            }
            else if(D==0)
                (*backEdges)++;
        }
    }
    colour[u]=BLACK;
    (*TIME)++;
    finish[u]=*TIME;
}

//----------------------------------------------------------Topological Sort--------------------------------------------------------

void Function3()
{
    int N,i,j,p;
    cin>>N;
    int **Adj=new int*[N];
    for(i=0;i<N;i++)
        Adj[i]=new int[N];
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
            cin>>Adj[i][j];
    }
    IntQueue Q;
    int count=0;
    int x;
    while(1)
    {
        bool NoIncomingEdge=0;
        for(i=0;i<N;i++)
        {
            p=0;
            for(j=0;j<N;j++)
            {
                if(Adj[j][i]==1)
                {
                    p=1;
                    break;
                }
            }
            if(p==0)
            {
                NoIncomingEdge=1;
                break;
            }
        }
        if(NoIncomingEdge)
        {
            Q.Enqueue(i);
            for(j=0;j<N;j++)
                Adj[i][j]=Adj[j][i]=0;
            Adj[i][i]=1;
        }
        else
            break;
    }
    if(Q.SizeQueue()==N)
    {
        while(!Q.isEmpty())
        {
            cout<<Q.Front()+1<<" ";
            Q.Dequeue();
        }
        cout<<endl;
    }
    else
        cout<<-1<<endl;
    for(i=0;i<N;i++)
        delete[] Adj[i];
    delete[] Adj;
}

void Function4()
{
    int N,D,s,i,j,x,n;
    cin>>N>>D>>s;
    s--;
    IntLL *AdjWeight=new IntLL[N];
    IntLL *AdjNode=new IntLL[N];
    Color *colour=new Color[N];
    int *dist=new int[N];
    bool DijkstraPossible=1;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            cin>>x;
            if(x<0)
            {
                DijkstraPossible=0;
            }
            if(x!=INF && i!=j)
            {
                AdjWeight[i].Insert(x);
                AdjNode[i].Insert(j);
            }
        }
        colour[i]=WHITE;
        dist[i]=INF;
    }
    if(DijkstraPossible)
    {
        int k,len;
        dist[s]=0;
        for(k=0;k<N;k++)
        {
            colour[s]=GREY;
            len=AdjNode[s].SizeLL();
            for(i=0;i<len;i++)
            {
                x=AdjWeight[s].Element();
                AdjWeight[s].Delete();
                n=AdjNode[s].Element();
                AdjNode[s].Delete();
                if(x!=INF)
                {
                    if(dist[n]>dist[s]+x)
                        dist[n]=dist[s]+x;
                }
            }
            x=INF;
            for(i=0;i<N;i++)
            {
                if(colour[i]==WHITE && dist[i]<x)
                {
                    x=dist[i];
                    s=i;
                }
            }
        }
        for(i=0;i<N;i++)
            cout<<dist[i]<<" ";
        cout<<endl;
    }
    else
        cout<<-1<<endl;
    delete[] AdjWeight;
    delete[] AdjNode;
    delete[] colour;
    delete[] dist;
}

void Function5()
{
    //I have used a modified verion of Bellman Ford Algorithm called SPFA.
    //For detecting negative edge cycles, break condition used is if d[n]<minimum edge width => negative edge cycle.
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
                    return ;
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
}

void Function6()
{
    int N,D,i,j,k;
    cin>>N>>D;
    int **dist=new int*[N];
    for(i=0;i<N;i++)
        dist[i]=new int[N];
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            cin>>dist[i][j];
        }
    }
    for(k=0;k<N;k++)
    {
        for(i=0;i<N;i++)
        {
            if(dist[i][k]==INF)
                continue;
            for(j=0;j<N;j++)
            {
                if(dist[k][j]==INF)
                    continue;
                if(dist[i][j]>dist[i][k]+dist[k][j])
                    dist[i][j]=dist[i][k]+dist[k][j];
            }
        }
    }
    bool NegativeEdgeCycle=0;
    for(i=0;i<N;i++)
    {
        if(dist[i][i]<0)
        {
            NegativeEdgeCycle=1;
            break;
        }
    }
    if(NegativeEdgeCycle)
        cout<<-1<<endl;
    else
    {
        for(i=0;i<N;i++)
        {
            for(j=0;j<N;j++)
            {
                cout<<dist[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    for(i=0;i<N;i++)
        delete[] dist[i];
    delete[] dist;
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

//--------------------------------------------------- Class IntStack Functions
void IntStack::Push(int x)
{
	L.Insert(x,0);
}
void IntStack::Pop()
{
	if(!L.SizeLL())
		return;
	else
		L.Delete();
}
int IntStack::Top()
{
	return L.Element();
}
bool IntStack::isEmpty()
{
	return !L.SizeLL();
}
int IntStack::sizeStack()
{
	return L.SizeLL();
}
void IntStack::freeStack()
{
	L.freeLL();
}
