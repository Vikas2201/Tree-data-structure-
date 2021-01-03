#include<stdio.h>
#include<stdlib.h> 
typedef struct node
{
	int data;
	struct node *left,*right;
	int ht;
}node;
int height(node *T)
{
	int lh,rh;
	if(T==NULL)
	{
		return(0);
    }
	if(T->left==NULL)
	{
	    lh=0;
    }
	else
	{
		lh=1+T->left->ht;
    }
	if(T->right==NULL)
	{
		rh=0;
    }
	else
	{
		rh=1+T->right->ht;
    }
	if(lh>rh)
	{
		return(lh);
    }
	else
	{
	    return(rh);
    }
}
node * rotateright(node *x)
{
	node *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}
node * rotateleft(node *x)
{
	node *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}
node * RR(node *T)
{
	T=rotateleft(T);
	return(T);
} 
node * LL(node *T)
{
	T=rotateright(T);
	return(T);
}
node * LR(node *T)
{
	T->left=rotateleft(T->left);
	T=rotateright(T);	
	return(T);
} 
node * RL(node *T)
{
	T->right=rotateright(T->right);
	T=rotateleft(T);
	return(T);
}
int BF(node *T)
{
	int lh,rh;
	if(T==NULL)
	{
		return(0);
    }
	if(T->left==NULL)
	{
		lh=0;
    }
	else
	{
		lh=1+T->left->ht;
    }
	if(T->right==NULL)
	{
		rh=0;
    }
	else
	{
		rh=1+T->right->ht;
    }
	return(lh-rh);
}
node * insert(node *T,int x)
{
	if(T==NULL)
	{
		T=(node*)malloc(sizeof(node));
		T->data=x;
		T->left=NULL;
		T->right=NULL;
	}
	else
	{
		if(x > T->data)		// insert in right subtree
		{
			T->right=insert(T->right,x);
			if(BF(T)==-2)
			{
				if(x>T->right->data)
				{
					T=RR(T);
			    }
				else
				{
					T=RL(T);
				}
			}
		}
		else
		{
			if(x<T->data)
			{
				T->left=insert(T->left,x);
				if(BF(T)==2)
				{
					if(x < T->left->data)
					{
						T=LL(T);
				    }
					else
					{
						T=LR(T);
			        }
			    }
			}
		}
		T->ht=height(T);
		return(T);
    }   
}
void inorder(node *T)
{
	if(T==NULL)
	{
		return ;
	}
	inorder(T->left);
	printf("%d(Bf=%d)  ",T->data,BF(T));
	inorder(T->right);
}
void preorder(node *T)
{
	if(T==NULL)
	{
		return ;
	}
	printf("%d(Bf=%d)  ",T->data,BF(T));
	preorder(T->left);
	preorder(T->right);
}
void postorder(node *T)
{
	if(T==NULL)
	{
		return ;
	}
	postorder(T->left);
	postorder(T->right);
	printf("%d(Bf=%d)  ",T->data,BF(T));
}
int main()
{
	node *root=NULL;
	int x,n,i,op;
	do
	{
		printf("\nOUR OPTION WILL BE:");
		printf("\n1. CREATE:");
		printf("\n2. INSERATION:");
		printf("\n3. DISPLAY:");
		printf("\n4. QUIT:");
		printf("\n\nENTER YOUR CHOICE:");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
			{
			    printf("\nENTER NUMBER OF ELEMENTS : ");
				scanf("%d",&n);
				printf("\nENTER TREE DATA : ");
				root=NULL;
				for(i=0;i<n;i++)
				{
					scanf("%d",&x);
					root=insert(root,x);
				}
				break;
		    }
			case 2:
			{
			    printf("\nENTER A VALUE FOR INSERATION : ");
				scanf("%d",&x);
				root=insert(root,x);
				break;
		    }
			case 3:
			{
			    printf("\nPREORDER SEQUENCE :\n");
				preorder(root);
				printf("\n\nINORDER SEQUENCE:\n");
				inorder(root);
				printf("\n\nPOSTORDER SEQUENCE:\n");
				postorder(root);
				printf("\n");
				break;
			}
		}
	}while(op!=4);
	return 0;
}
