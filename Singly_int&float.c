#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
int data;
float data2;
struct node *next;
};

typedef struct node Node;
Node *head= NULL;

void print(){
printf("Printing the linked list\n");
Node *p=head;
while(p != NULL){
    printf("%d",p->data);
    printf("\t%.2f\n",p->data2);
    p=p->next;
}
printf("\n");
}

void insertB(){
printf("Insert before head\n");
int data;
float data2;
Node *lk;
lk= (Node *)malloc(sizeof(Node));
printf("Enter integer data\n");
scanf("%d",&data);
printf("Enter float data\n");
scanf("%f",&data2);

lk->data=data;
lk->data2=data2;
lk->next=head;
head=lk;
}

void insertL(){
Node *ptr=head;
while(ptr ==  NULL){
    insertB();
    return ;
}
int data;
float data2;
printf("Inserting Last \n");
Node *new_node;
new_node=(Node*)malloc(sizeof(Node));
printf("Input int data\n");
scanf("%d",&data);
printf("Input float data\n");
scanf("%f",&data2);
new_node->data=data;
new_node->data2=data2;
new_node->next=NULL;

while (ptr-> next != NULL){
    ptr=ptr->next;
}
ptr->next =new_node;
}

void insertA(){
int data,key;
float data2;
printf("Where do you want to insert?\n");
scanf("%d",&key);
Node *ptr=head;
while(ptr != NULL){
    if(ptr->data==key){
        Node *new_node;
        new_node=(Node *)malloc(sizeof(Node));
        printf("Input int data\n");
        scanf("%d",&data);
        printf("Input float data\n");
        scanf("%f",&data2);
        new_node->data=data;
        new_node->data2=data2;
        new_node->next=ptr->next;
        ptr->next=new_node;
        return;
    }
    else {
        ptr=ptr->next;
    }
 }
insertL();
}

void deleteh(){
printf("Deleting head");
head= head->next;
}

void deleteL(){
printf("Deleting last");
Node *ptr= head;
while(ptr->next->next!=NULL)
    {
        ptr=ptr->next;
    }
    ptr->next=NULL;
}

int main(){
insertB();
print();
insertL();
print();
insertA();
print();
deleteh();
print();
deleteL();
print();
}

