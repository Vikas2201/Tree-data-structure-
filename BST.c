#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *left , *right ;
};
struct node *insert(struct node *root,int value)
{
	if(root==NULL)
	{
		root=(struct node*)malloc(sizeof(struct node));
		root->data=value;
		root->left=NULL;
		root->right=NULL; 
	}
	else if(value<root->data)
	{
		root->left=insert(root->left,value);
	}
	else if(value>root->data)
	{
		root->right=insert(root->right,value);
	}
	else
	{
		printf("\nDUPLICATE VALUE");
	}
	return root;
}
void search(struct node *root, int n)
{
	if (root==NULL)
	{
		printf("\n%d NOT PRESENT IN TREE ");
		return ;
	}
	else if(n==root->data)
	{
		printf("\n%d PRESENT IN TREE ");
	}
	else if(n<root->data)
	{
		search(root->left,n);
	}
	else 
	{
		search(root->right,n);
	}
}
struct node *inordersuccessor(struct node* key)
{
	struct node* current = key;
	while(current->left !=NULL)
	{
		current = current->left;
	}
	return current;
}
struct node *delete(struct node *root, int ele)
{
	struct node *ptr;
	if(root==NULL)
	{
		return root;
	}
	else if(ele<root->data)
	{
		root->left=delete(root->left,ele);
	}
	else if(ele>root->data)
	{
		root->right=delete(root->right,ele);
	}
	else
	{
		if(root->left==NULL)
		{
			ptr=root->right;
			free(root);
			return ptr;
		}
		else if(root->right==NULL)
		{
			ptr=root->left;
			free(root);
			return ptr;
		}
		ptr=inordersuccessor(root->right);
		root->data=ptr->data;
		root->right=delete(root->right,ptr->data);
		return root;
	}
}
void inorder(struct node *root)
{
	if(root==NULL)
	{
		return ;
	}
	inorder(root->left);
	printf("%d  ",root->data);
	inorder(root->right);
}
void postorder(struct node *root)
{
	if(root==NULL)
	{
		return ;
	}
	postorder(root->left);
	postorder(root->right);
	printf("%d  ",root->data);
	
}
void preorder(struct node *root)
{
	if(root==NULL)
	{
		return ;
	}
	printf("%d  ",root->data);
	preorder(root->left);
	preorder(root->right);	
}
int main()
{
	struct node *root=NULL;
	int choice,value,ele,n,i;
	while(1)
	{
		printf("\n");
		printf("\nOUR OPTION WILL BE:");
		printf("\n1. CREATE A BST TREE ");
		printf("\n2. INSERATION IN BST");
		printf("\n3. DELETION IN BST");
		printf("\n4. SEARCHING IN BST");
		printf("\n5. INORDER TRAVERSAL IN BST");
		printf("\n6. POSTORDER TRAVERSAL IN BST");
		printf("\n7. PREORDER TRAVERSAL IN BST");
		printf("\n8. EXIT");
		printf("\nENTER OUR CHOICE:");                  
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			{
			    printf("\nENTER NUMBER OF ELEMENTS : ");
				scanf("%d",&n);
				printf("\nENTER TREE DATA : ");
				root=NULL;
				for(i=0;i<n;i++)
				{
					scanf("%d",&value);
					root=insert(root,value);
				}
				getch();
				break;
			}
			case 2:
			{
				printf("\nENTER VALUE FOR INSERATION : ");
				scanf("%d",&value);
				root=insert(root,value);
				getch();
				break;
			}	
			case 3:
			{
				printf("\nENTER VALUE FOR DELETION : ");
				scanf("%d",&value);
				root=delete(root,value);
				getch();
				break;
			}
			case 4:
			{
				printf("\nENTER VALUE FOR SEARCHING : ");
				scanf("%d",&value);
				search(root,value);
				getch();
				break;
			}
            case 5:
			{
				inorder(root);
				getch();
				break;
			}
			case 6:
			{
			    postorder(root);
				getch();
				break;
			}	
			case 7:
			{
				preorder(root);
				getch();
				break;
			}	
			case 8:
			{
				exit(1);
				break;
			}
			default:
			{
				printf("\nENTER CORRECT CHOICE:");
				getch();
				break;
			}
		}
	}
}
