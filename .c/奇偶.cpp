#include<stdio.h>
#include<stdlib.h>
#include <my_io.h>

typedef struct linklist{
	int data;
	linklist *next;
}linklist;

int dec_same(linklist* head1,linklist* head2);
linklist* creat(linklist* head,int size);
void printlist(linklist* head);
void insertlink(linklist** head,int position);
void freelist(linklist* head);
linklist* deletelink(linklist* head,int position);
linklist* optersys(linklist *headm);
linklist* delete_same(linklist* head);

linklist* creat(linklist* head,int size){
	linklist *tail;
	if(head==NULL)tail = NULL;
	else{
		tail=head;
		while(tail->next!=NULL){
			tail=tail->next;
		}
	}
	for(int i = 1;i<=size;i++){
		linklist *newone = (linklist*)malloc(sizeof(linklist));
		if(newone==NULL){
			fprintf(stderr,"malloc failed\n");
			exit(EXIT_FAILURE);
		}
		/*
			输入模块
		*/ 
		printf("input data for create data%d:",i);
		mscan("%d",&newone->data);
		
		/*
			输入模块
		*/ 
		
		if(head==NULL){
			head=newone;
			tail=newone;
			tail->next=NULL;
		}else{
			tail->next=newone;
			tail=newone;
			tail->next=NULL;
		}
	}
	return head;
}

void printlist(linklist* head){
	linklist* current;
	for(current=head;current!=NULL;current=current->next){
		printf("\t%d",current->data);
	}
	printf("\n");
}

void freelist(linklist* head){
	linklist* temp=head;linklist* temp1;
	for(temp;temp!=NULL;free(temp1)){
		temp1=temp;
		temp=temp->next;
	}
}

void insertlink(linklist** head,int position,int size){
	int i,j;
	linklist* current=*head;
	linklist* head1=NULL;
	head1=creat(head1,size);
	linklist* tail1=head1;
	for(i=0;tail1->next!=NULL;tail1=tail1->next);
	if(position==1){
		*head=head1;
		tail1->next=current;
	}else{
		for(i=1;i<position-1;i++){
			if(current->next==NULL){
				printf("position is not exist!!");
				return;
			}
			current=current->next;
		}
		if(current->next==NULL){
			current->next=head1;
			tail1->next=NULL;
		}else{
			tail1->next=current->next;
			current->next=head1;
		}
	}
} 

linklist* deletelink(linklist* head,int position,int size){
	int i,k;
	linklist* temp;
	linklist* current=head;
	if(position==1){
		for(i=0;i<size;i++){
			temp=head;
			head=head->next;
			free(temp);
		}
	}else{
		for(i=1;i<position-1;i++){
			if(current->next==NULL){
				printf("the positon of your enter is not exist!!");
				return head;
			}
			current=current->next;
		}
		for(i=0;i<size;i++){
			temp=current->next;
			current->next=current->next->next;
			free(temp);
		}
	}
	return head;
}

linklist* optersys(linklist *headm){
	linklist* head =headm;
	while(1){
		int i;
		char temp[20];
		printf("follow the prompts below to enter:\n\tcreatnew:    1\n\tprint:       2\n\tinsert:      3\n\tdelete:      4\n\tdelete same  5\n\tfree:        6\n\texit:        7\n:");
		mscan("%d",&i);
		if(i==1){
			int n;
			printf("input the number of list you wanna to creat:");
			if(mscan("%d",&n)!=1||n<=0)printf("\t\t\tvalue is error!\n");
			else head=creat(head,n);
		}
		if(i==2)printlist(head);
		if(i==3){
			int p,n;
			printf("input the position and size of the link you wanna to insert:(position##size)");
			if(mscan("%d##%d",&p,&n)!=2||p<=0||n<=0)
				printf("\t\t\tvalue is error!\n");
			else insertlink(&head,p,n);
		}
		if(i==4){
			int p,n;
			printf("input the position and size of the link you wanna to delete:(position##size)");
			if(mscan("%d##%d",&p,&n)!=2||p<=0||n<=0)printf("\t\t\tvalue is error!\n");
			else head=deletelink(head,p,n);
		}
		if(i==5)head=delete_same(head);
		if(i==6){
			freelist(head);
			head=NULL;
		}
		if(i==7)break;
	}
	return head;
}

linklist* delete_same(linklist* head){
	linklist *current1=head,*current2,*last=NULL,*temp=NULL;
	for(;current1!=NULL;current1=current1->next){
		for(current2=current1;current2!=NULL;current2=current2->next){
			if(temp!=NULL)free(temp);
			temp=NULL;
			if(current1!=current2&&current1->data==current2->data&&current2->next!=NULL){
				last->next=current2->next;
				temp=current2;
			}else if(current1!=current2&&current1->data==current2->data&&current2->next==NULL){
				last->next=NULL;
				temp=current2;
				current2=NULL;
				free(temp);
				temp=NULL;
				last=current2;
				break;
			}else last=current2;
			
		}
	}
	return head;
}

int dec_same(linklist* head1,linklist* head2){
	linklist *current1=head1,*current2=head2;
	for(;current1->next!=NULL&&current2->next!=NULL;){
		if(current1->data==current2->data);
		else return 1;
		current1=current1->next;
		current2=current2->next;
	}
	if(current1->next!=NULL||current2->next!=NULL)return 1;
	else return 0;
}

int main(){
	int i;
	linklist *head[10];
	for(i=0;i<10;i++){
		head[i]=NULL;
	}
	while(1){
		printf("What number of list you want to operate(exit=0,list=1-10,detect are two list the same=11):");
		mscan("%d",&i);
		if(i>0&&i<=10)head[i-1]=optersys(head[i-1]);
		else if(i==0)break;
		else if(i==11){
			int a,b;
			printf("enter a and b(concatenate using spaces):");
			mscan("%d %d",&a,&b);
			if(dec_same(head[a-1],head[b-1])==0)printf("list%d and list%d are the same\n",a,b);
			else printf("list%d and list%d are not the same\n",a,b);
		}
		else printf("value is error!");
	}
	return 0;
}


	
	
	












