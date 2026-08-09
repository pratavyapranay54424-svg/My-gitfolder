#include<iostream>
using namespace std;
class Node{
 public:
  int data;
  Node* next;
  Node(int d){
    data=d;
    next=NULL;
  }
};
void insertatbeginnning(Node * &head,int data){
Node*newnode=new Node(data);
if(head==NULL){
  head=newnode;
  return;
}
else{
newnode->next=head;
head=newnode;
return;
}
}
void insertatend(Node * &head,int data){
Node* newnode = new Node(data);
 
    Node* temp = head;
    while (temp->next != NULL) {  // Traverse to the last node
        temp = temp->next;
    }
    temp->next = newnode;  // Link last node to new node
}
int main(){
Node *head=new Node(10);
Node *second=new Node(12);
Node *third=new Node(15);
Node *fourth=new Node(17);
Node *fifth=new Node(19);
head->next=second;
second->next=third;
third->next=fourth;
fourth->next=fifth;
insertatbeginnning(head,20);
insertatbeginnning(head,21);
insertatbeginnning(head,22);
insertatbeginnning(head,23);
insertatend(head,27);
Node* temp=head;

 while(temp!=NULL){
    cout<<temp->data<<" ";
    temp=temp->next;
 }

return 0;
}