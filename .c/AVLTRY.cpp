#include<stdio.h>
#include<stdlib.h>

typedef struct lista{
	int data;
	lista* left;
	lista* right;
	int hight;
}lista; 

typedef struct stacka{
	lista** arr;
	int cap;
	int len; 
}stacka;

int max(int a,int b){
	return a>b?a:b;
}

void init_stk(stacka* tarstk){
	tarstk->cap=10;
	tarstk->len=0;
	tarstk->arr = (lista**)(malloc(tarstk->cap * sizeof(lista*)));
}

void plustk(stacka *tarstk){
	lista** arrt=(lista**)realloc(tarstk->arr,(tarstk->len + 10) * (sizeof(lista*)));
	if(arrt){
		tarstk->arr=arrt;
		tarstk->cap+= 10;
	}else{
		fprintf(stderr, "realloc failed\n");
        exit(1);
	}
}

void insertstk(lista* tar,stacka *tarstk){
	if(tarstk->cap==tarstk->len)plustk(tarstk);
	tarstk->arr[tarstk->len]=tar;
	tarstk->len=tarstk->len + 1;
}

void destk(stacka* tarstk){
	free(tarstk->arr);
	tarstk->arr=NULL;
	tarstk->cap=0;
	tarstk->len=0;
}

void initnode(lista* tar){
	tar->data=0;
	tar->hight=0;
	tar->left=NULL;
	tar->right=NULL;
}

int gethight(lista* tar){
	if(tar==NULL)return -1;
	/*tar->hight=max(tar->left->hight,tar->right->hight)+1;*/
	return tar->hight;
}

void updatahight(lista* tar){
	tar->hight=max(gethight(tar->left),gethight(tar->right))+1;
}

int getbalance(lista* tar){
	if(tar==NULL)return 0;
	return gethight(tar->left) - gethight(tar->right);
}

lista* leftRo(lista* parent){
	if (parent == NULL || parent->right == NULL) return parent;
	lista* child=parent->right;
	parent->right=child->left;
	child->left=parent;
	parent->hight=max(gethight(parent->left),gethight(parent->right))+1;
	child->hight=max(gethight(child->left),gethight(child->right))+1;
	return child;
}

lista* rightRo(lista* parent){
	if (parent == NULL || parent->left == NULL) return parent;
	lista* child=parent->left;
	parent->left=child->right;
	child->right=parent;
	parent->hight=max(gethight(parent->left),gethight(parent->right))+1;
	child->hight=max(gethight(child->left),gethight(child->right))+1;
	return child;
}

lista* insert(lista* root,int value){
	lista* newnode=(lista*)malloc(sizeof(lista));
	initnode(newnode);
	newnode->data=value;
	if(root==NULL)return newnode; 
	lista* current=root;
	lista* parent;
	lista* grandpa;
	newnode->data=value;
	stacka stak;
	init_stk(&stak);
	while(1){
		insertstk(current,&stak);
		if(current->data > value){
			if(current->left==NULL){
				current->left=newnode;
				break;
			}
			current=current->left;
		}
		else if(current->data < value){
			if(current->right==NULL){
				current->right=newnode;
				break;
			}
			current=current->right;
		}else if(current->data==value){
			free(newnode);
			destk(&stak);
			return root;
		}
	}
	for(int i=stak.len;i>0;i--){
		lista* a=(lista*)(stak.arr[i-1]);
		updatahight(a);
	}
	current=NULL;
	for(int i=stak.len;i>0;i--){
		if(i>1){
			grandpa=(lista*)(stak.arr[i-2]);
			parent=(lista*)(stak.arr[i-1]);
			updatahight(parent);
			int a=getbalance(parent);
			if(a==2||a==-2){
				if(a==2&&(getbalance(parent->left)==1)){
					if(grandpa->left==parent)grandpa->left=rightRo(parent);
					else grandpa->right=rightRo(parent);
				}else if(a==2&&(getbalance(parent->left)==-1)){
					parent->left=leftRo(parent->left);
					if(grandpa->left==parent)grandpa->left=rightRo(parent);
					else grandpa->right=rightRo(parent);
				}else if(a==-2&&(getbalance(parent->right)==1)){
					parent->right=rightRo(parent->right);
					if(grandpa->left==parent)grandpa->left=leftRo(parent);
					else grandpa->right=leftRo(parent);
				}else if(a==-2&&(getbalance(parent->right)==-1)){
					if(grandpa->left==parent)grandpa->left=leftRo(parent);
					else grandpa->right=leftRo(parent);
				}
			}
		}else if(i==1){
			int a=getbalance(root);
			if(a==2||a==-2){
				if(a==2&&(getbalance(root->left)==1)){
					root=rightRo(root);
					break;
				}else if(a==2&&(getbalance(root->left)==-1)){
					root->left=leftRo(root->left);
					root=rightRo(root);
					break;
				}else if(a==-2&&(getbalance(root->right)==1)){
					root->right=rightRo(root->right);
					root=leftRo(root);
					break;
				}else if(a==-2&&(getbalance(root->right)==-1)){
					root=leftRo(root);
					break;
				}
			}
		}
	}
	destk(&stak);
	return root;
}

lista* del(lista *root,int value){
	lista* current=root;
	stacka stak;
	stacka stakb;
	init_stk(&stakb);
	init_stk(&stak);
	while(current->data!=value){
		insertstk(current,&stak);       //从根节点到删除点父节点 
		if(current->data > value)current=current->left;
		else current=current->right;
		if(current==NULL){
			printf("%d is not exist\n",value);
			destk(&stak);
			destk(&stakb);
			return root;
		}
	}
	if(current->left==NULL && current->right==NULL){
		if(current==root){
			free(root);
			return NULL;
		}else{
			lista* parent=stak.arr[stak.len-1];
			if(parent->left==current)parent->left=NULL;
			else parent->right=NULL;
			free(current);
		}	
	}else if(current->left==NULL || current->right==NULL){
		if(current==root){
			if(root->left){
				lista* rootl=root;
				root=root->left;
				free(rootl);
			}else{
				lista* rootr=root;
				root=root->right;
				free(rootr);
			}
		}else if(current->left){
			lista* parent=stak.arr[stak.len-1];
			if(parent->left==current) parent->left=current->left;
			else parent->right=current->left;
			free(current);
		}else{
			lista* parent=stak.arr[stak.len-1];
			if(parent->left==current) parent->left=current->right;
			else parent->right=current->right;
			free(current);
		}
	}else{
		if(current==root){
			lista* temp=current->left;
			while(temp->right){
				insertstk(temp,&stakb);     
				temp=temp->right;
			}
			if(!current->left->right){
				temp->right=current->right;
				root=temp;
			}else{
				stakb.arr[stakb.len-1]->right=temp->left;
				temp->left=current->left;
				temp->right=current->right;
				root=temp;
			}
			insertstk(temp,&stak);
			free(current);
			for(int i=0;i<stakb.len;i++)insertstk(stakb.arr[i],&stak);
			destk(&stakb);
		}else{
			lista* parent_current=stak.arr[stak.len-1];
			lista* temp=current->left;
			while(temp->right){
				insertstk(temp,&stakb);     //从删除点左孩子开始到删除后最右端 
				temp=temp->right;
			}
			if(!current->left->right){
				if(parent_current->left==current)parent_current->left=temp;
				else parent_current->right=temp;
				temp->right=current->right;
			}else{
				stakb.arr[stakb.len-1]->right=temp->left;
				if(parent_current->left==current)parent_current->left=temp;
				else parent_current->right=temp;
				temp->left=current->left;
				temp->right=current->right;
			}
			insertstk(temp,&stak);
			free(current);
			for(int i=0;i<stakb.len;i++)insertstk(stakb.arr[i],&stak);
			destk(&stakb);
		}
			
	}
	for(int i=stak.len-1;i>0;i--){
		lista* grandpa=stak.arr[i-1];
		lista* parent=stak.arr[i];
		updatahight(parent);
		int a=getbalance(parent);
		if(a<-1||a>1){
			if(a<-1){
				if(getbalance(parent->right)==-1){
					if(grandpa->left==parent)grandpa->left=leftRo(parent);
					else grandpa->right=leftRo(parent);
				}else{
					parent->right=rightRo(parent->right);
					if(grandpa->left==parent)grandpa->left=leftRo(parent);
					else grandpa->right=leftRo(parent);
				}
			}else{
				if(getbalance(parent->left)==1){
					if(grandpa->left==parent)grandpa->left=rightRo(parent);
					else grandpa->right=rightRo(parent);
				}else{
					parent->left=leftRo(parent->left);
					if(grandpa->left==parent)grandpa->left=rightRo(parent);
					else grandpa->right=rightRo(parent);
				}
			}
		}
	}
	updatahight(root);
	int b=getbalance(root);
	if(b<-1||b>1){
			if(b<-1){
				if(getbalance(root->right)==-1)root=leftRo(root);
				else{
					root->right=rightRo(root->right);
					root=leftRo(root);
				}
			}else{
				if(getbalance(root->left)==1)root=rightRo(root);
				else{
					root->left=leftRo(root->left);
					root=rightRo(root);
				}
			}
		}
	return root;
}

void orderprint(lista* root){
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    
    stacka stack;
    init_stk(&stack);
    lista* current = root;
    
    printf("Inorder traversal: \n");
    
    while (current != NULL || stack.len > 0) {
        // 1. 将所有左子节点压入栈中
        while (current != NULL) {
            insertstk(current, &stack);
            current = current->left;
        }
        
        // 2. 弹出栈顶节点并访问
        current = stack.arr[stack.len - 1];
        stack.len--;  // 出栈操作（无需真正释放内存，只需减少长度）
        printf("%d ", current->data);
        
        // 3. 转向右子树
        current = current->right;
    }
    
    printf("\n");
    destk(&stack);  // 释放栈内存

	
}

void find(int value){
	
	
}

int main(){
	lista *node=NULL;
	node=insert(node,3);
	node=insert(node,7);
	node=insert(node,15);
	node=insert(node,1);
	node=insert(node,3);
	
	orderprint(node);
	
	node = del(node, 10);
	node = del(node, 7);
	
	orderprint(node);
	
	node = del(node, 3);
	
	orderprint(node);
	
	
} 







