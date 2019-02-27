#include<iostream>
#include<vector>
#include<sstream>
#include<string>
using namespace std;

typedef struct Node* Node_Pointer;
typedef struct Activity * Activity_Pointer;
typedef struct Header * Header_Pointer;

struct Header{
  int tail;
  int count;
  Node_Pointer Next;
};
struct Node{
  int head;
  int distance;
  Node_Pointer Next;
};
struct Activity{
  int index;
  int head;
  int tail;
  Activity_Pointer Next_Activity;
};

Activity_Pointer temp_Activity;
Activity_Pointer initial_Activity;
Header_Pointer temp_Header;
Node_Pointer temp_Node;
const char Split_Char=' ';
int no_Edge,no_Event;
vector <int> temp_string;
vector<int> Head;
vector <Header_Pointer>Header_Available;

void string_Split(string);
int Check_Header(int);
void  Check_Activity(int);
void Update_Count();
void Topological_Order();

int main (){
  cout<<"Please enter the number of activity"<<endl;
  cin>>no_Edge;
  cin.ignore();
  temp_Activity=new Activity;
  temp_Activity->Next_Activity=NULL;
  initial_Activity=temp_Activity;
  for(int i=0;i<no_Edge;i++){
    string temp;
    getline(cin,temp);
    string_Split(temp);
    //Initialising activity
    temp_Activity=new Activity;
    temp_Activity->index=temp_string.at(0);
    temp_Activity->tail=temp_string.at(1);
    temp_Activity->head=temp_string.at(2);
    temp_Activity->Next_Activity=initial_Activity->Next_Activity;
    initial_Activity->Next_Activity=temp_Activity;
    //End initialising acticity
    //intialising Header and Node
    unsigned int index=Check_Header(temp_string.at(1));
      if(index==Header_Available.size()){
        temp_Header=new Header;
        temp_Header->tail=temp_string.at(1);
        temp_Header->Next=NULL;
        temp_Header->count=0;
        Header_Available.push_back(temp_Header);
      }
      temp_Node=new Node;
      temp_Node->head=temp_string.at(2);
      temp_Node->distance=temp_string.at(3);
      temp_Node->Next=Header_Available.at(index)->Next;
      Header_Available.at(index)->Next=temp_Node;
      Head.push_back(temp_string.at(2));

      index=Check_Header(temp_string.at(2));
      if(index==Header_Available.size()){
        temp_Header=new Header;
        temp_Header->tail=temp_string.at(2);
        temp_Header->Next=NULL;
        temp_Header->count=0;
        Header_Available.push_back(temp_Header);
      }
    }
    //End intialising header and node
    Update_Count();
    no_Event=Header_Available.size();
    int ee[no_Event];
    int le[no_Event];
    for(int i=0;i<no_Event;i++){
      ee[i]=0;
      le[i]=10000;
    }
    Topological_Order();
    for(unsigned int i=0;i<Head.size();i++){
      int Current_tail=Head.at(i);
      int index=Check_Header(Current_tail);
      temp_Node=Header_Available.at(index)->Next;
      while(temp_Node){
        if(temp_Node->distance+ee[Current_tail]>ee[temp_Node->head]){
          ee[temp_Node->head]=temp_Node->distance+ee[Current_tail];
        }
        temp_Node=temp_Node->Next;
      }
    }
    le[Head.at(Head.size()-1)]=ee[Head.at(Head.size()-1)];

    for(int i=Head.size()-2;i>=0;i--){
      int Current_tail=Head.at(i);
      int index=Check_Header(Current_tail);
      temp_Node=Header_Available.at(index)->Next;
      while(temp_Node){
        if(le[temp_Node->head]-temp_Node->distance<le[Current_tail]){
          le[Current_tail]=le[temp_Node->head]-temp_Node->distance;
        }
        temp_Node=temp_Node->Next;
      }
    }
    int e[no_Edge],l[no_Edge],slack[no_Edge];
    cout<<"act.\t"<<"e\t"<<"l\t"<<"slack\t"<<"critical\n";
    for (int i=0;i<no_Edge;i++){
      Check_Activity(i+1);
      e[i]=ee[temp_Activity->tail];
      int index=Check_Header(temp_Activity->tail);
      temp_Node=Header_Available.at(index)->Next;
      while(temp_Node->head!=temp_Activity->head){
        temp_Node=temp_Node->Next;
      }
      l[i]=le[temp_Activity->head]-temp_Node->distance;
      slack[i]=l[i]-e[i];
      cout<<i+1<<"\t"<<e[i]<<"\t"<<l[i]<<"\t"<<slack[i]<<"\t";
      if(slack[i]==0){
        cout<<"Yes"<<endl;
      }
      else{
        cout<<"NO"<<endl;
      }
    }


}
void Check_Activity(int index){
  temp_Activity=initial_Activity;
  while(temp_Activity){
    if(temp_Activity->index==index){
      return;
    }
    temp_Activity=temp_Activity->Next_Activity;
  }
}

void Topological_Order(){
  Head.erase(Head.begin(),Head.end());
  int top=-1;
  unsigned int length=Header_Available.size();
  for(unsigned int i=0;i<length;i++){
    if(Header_Available.at(i)->count==0){
      Header_Available.at(i)->count=top;
      top=i;
    }
  }
  for(unsigned int i=0;i<length;i++){
    int j=Header_Available.at(top)->tail;
    Head.push_back(j);
    temp_Node=Header_Available.at(top)->Next;
    top=Header_Available.at(top)->count;
    while(temp_Node){
      int index=(Check_Header(temp_Node->head));
      Header_Available.at(index)->count--;
      if(Header_Available.at(index)->count==0){
        Header_Available.at(index)->count=top;
        top=index;
      }
      temp_Node=temp_Node->Next;
    }
  }
}
void Update_Count(){
  unsigned int length=Header_Available.size();
  for(unsigned int i=0;i<length;i++){
    int count=0;
    for (unsigned int j=0;j<Head.size();j++){
      if(Head.at(j)==Header_Available.at(i)->tail){
        count++;
      }
    }
    Header_Available.at(i)->count=count;
  }
}

int Check_Header(int key){
  unsigned int length=Header_Available.size();
  for (unsigned int i=0;i<length;i++){
    if(Header_Available.at(i)->tail==key){
      return i;
    }
  }
  return length;
}

void string_Split(string ss){
  temp_string.erase(temp_string.begin(),temp_string.end());
  istringstream s(ss);
  string temp;
  while(getline(s,temp,Split_Char)){
    temp_string.push_back(stoi(temp));
  }
}
