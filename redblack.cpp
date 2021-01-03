#include <stdio.h>
#include <stdlib.h>
enum nodeColor 
{
    RED,
    BLACK
};
struct rbNode 
{
    int data, color;
    struct rbNode *link[2];
};
struct rbNode *root = NULL;
struct rbNode *createNode(int data) 
{
    struct rbNode *new_node;
    new_node = (struct rbNode *)malloc(sizeof(struct rbNode));
    new_node->data = data;
    new_node->color = RED;
    new_node->link[0] = new_node->link[1] = NULL;
    return new_node;
}
void insertion(int value) 
{
    struct rbNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
    int dir[98], ht = 0, index;
    ptr = root;
    if (root==NULL)
    {
        root = createNode(value);
        return;
    }
    stack[ht] = root;
    dir[ht++] = 0;
    while (ptr != NULL) 
    {
        if (ptr->data == value) 
	    {
            printf("\nDUPLICATES VALUES NOT ALLOWED ");
            return;
        }
        index = (value - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        ptr = ptr->link[index];
        dir[ht++] = index;
    }
    stack[ht - 1]->link[index] = newnode = createNode(value);
    while ((ht >= 3) && (stack[ht - 1]->color == RED)) 
    {
        if (dir[ht - 2] == 0)
	    {
            yPtr = stack[ht - 2]->link[1];
            if (yPtr != NULL && yPtr->color == RED) 
	        {
                stack[ht - 2]->color = RED;
                stack[ht - 1]->color = yPtr->color = BLACK;
                ht = ht - 2;
            }
	        else
	        {
                if (dir[ht - 1] == 0) 
				{
                    yPtr = stack[ht - 1];
                }
				else
			    {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->link[1];
                    xPtr->link[1] = yPtr->link[0];
                    yPtr->link[0] = xPtr;
                    stack[ht - 2]->link[0] = yPtr;
                }
                xPtr = stack[ht - 2];
                xPtr->color = RED;
                yPtr->color = BLACK;
                xPtr->link[0] = yPtr->link[1];
                yPtr->link[1] = xPtr;
                if (xPtr == root) 
			    {
                    root = yPtr;
                }   
			    else 
			    {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        } 
	    else
	        {
                yPtr = stack[ht - 2]->link[0];
                if ((yPtr != NULL) && (yPtr->color == RED))
			    {
                    stack[ht - 2]->color = RED;
                    stack[ht - 1]->color = yPtr->color = BLACK;
                    ht = ht - 2;
                }
		        else 
		        {
                    if (dir[ht - 1] == 1)
			        {
                        yPtr = stack[ht - 1];
                    }
				    else
				    {
                        xPtr = stack[ht - 1];
                        yPtr = xPtr->link[0];
                        xPtr->link[0] = yPtr->link[1];
                        yPtr->link[1] = xPtr;
                        stack[ht - 2]->link[1] = yPtr;
                    }
                xPtr = stack[ht - 2];
                yPtr->color = BLACK;
                xPtr->color = RED;
                xPtr->link[1] = yPtr->link[0];
                yPtr->link[0] = xPtr;
                if (xPtr == root) 
			    {
                    root = yPtr;
                }  
			    else 
			    {
                    stack[ht - 3]->link[dir[ht - 3]] = yPtr;
                }
                break;
            }
        }
    }
    root->color = BLACK;
}
void deletion(int data) 
{
    struct rbNode *stack[98], *ptr, *xPtr, *yPtr ,*temp;
    struct rbNode *pPtr, *qPtr, *rPtr;
    int dir[98], ht = 0, diff, i;
    enum nodeColor color;
    if (!root) 
	{
        printf("\nTREE NOT AVAILABLE ");
        return;
    }
    ptr = root;
    while (ptr != NULL) 
	{
        if ((data - ptr->data) == 0)
        {
		   break;
        }
	    diff = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        dir[ht++] = diff;
        ptr = ptr->link[diff];
    }
    if (ptr->link[1] == NULL) 
	{
        if ((ptr == root) && (ptr->link[0] == NULL)) 
		{
            free(ptr);
            root = NULL;
        }
	    else if (ptr == root)
		{
            root = ptr->link[0];
            free(ptr);
        }
		else
		{
            stack[ht - 1]->link[dir[ht - 1]] = ptr->link[0];
        }
    }
	else
	{
        xPtr = ptr->link[1];
        if (xPtr->link[0] == NULL) 
		{
            xPtr->link[0] = ptr->link[0];
            temp->color = xPtr->color;
            xPtr->color = ptr->color;
            ptr->color = temp->color;
            if (ptr == root) 
			{
                root = xPtr;
            } 
			else 
			{
                stack[ht - 1]->link[dir[ht - 1]] = xPtr;
            }
			dir[ht] = 1;
            stack[ht++] = xPtr;
        }
		else
		{
            i = ht++;
            while (1) 
			{
                dir[ht] = 0;
                stack[ht++] = xPtr;
                yPtr = xPtr->link[0];
                if (!yPtr->link[0])
               {
					break;
				}
                xPtr = yPtr;
            }
            dir[i] = 1;
            stack[i] = yPtr;
            if (i > 0)
            stack[i - 1]->link[dir[i - 1]] = yPtr;
            yPtr->link[0] = ptr->link[0];
            xPtr->link[0] = yPtr->link[1];
            yPtr->link[1] = ptr->link[1];
            if (ptr == root)
			{
                root = yPtr;
            }
            temp->color = yPtr->color;
            yPtr->color = ptr->color;
            ptr->color = temp->color;
        }
    }
    if (ht < 1)
    {
	    return;
    }
    if (ptr->color == BLACK)
	{
        while (1) 
		{
            pPtr = stack[ht - 1]->link[dir[ht - 1]];
            if (pPtr && pPtr->color == RED) {
            pPtr->color = BLACK;
            break;
        }
        if (ht < 2)
        {
		    break;
        }
        if (dir[ht - 2] == 0) 
		{
            rPtr = stack[ht - 1]->link[1];
            if (!rPtr)
            {
			   break;
            }
            if (rPtr->color == RED)
			{
                stack[ht - 1]->color = RED;
                rPtr->color = BLACK;
                stack[ht - 1]->link[1] = rPtr->link[0];
                rPtr->link[0] = stack[ht - 1];
				if (stack[ht - 1] == root)
				{
                    root = rPtr;
                }
				else 
				{
                    stack[ht - 2]->link[dir[ht - 2]] = rPtr;
                }
                dir[ht] = 0;
                stack[ht] = stack[ht - 1];
                stack[ht - 1] = rPtr;
                ht++;
                rPtr = stack[ht - 1]->link[1];
            }
            if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) && (!rPtr->link[1] || rPtr->link[1]->color == BLACK)) 
		    {
                rPtr->color = RED;
            } 
		    else 
		    {
                if (!rPtr->link[1] || rPtr->link[1]->color == BLACK) 
			    {
                    qPtr = rPtr->link[0];
                    rPtr->color = RED;
                    qPtr->color = BLACK;
                    rPtr->link[0] = qPtr->link[1];
                    qPtr->link[1] = rPtr;
                    rPtr = stack[ht - 1]->link[1] = qPtr;
                }
                rPtr->color = stack[ht - 1]->color;
                stack[ht - 1]->color = BLACK;
                rPtr->link[1]->color = BLACK;
                stack[ht - 1]->link[1] = rPtr->link[0];
                rPtr->link[0] = stack[ht - 1];
                if (stack[ht - 1] == root)
			    {
                    root = rPtr;
                }
			    else
		    	{
                    stack[ht - 2]->link[dir[ht - 2]] = rPtr;
                }
                break;
            }
        }
	    else 
	    {
            rPtr = stack[ht - 1]->link[0];
            if (!rPtr)
            {
		        break;
            }
            if (rPtr->color == RED)
		    {
                stack[ht - 1]->color = RED;
                rPtr->color = BLACK;
                stack[ht - 1]->link[0] = rPtr->link[1];
                rPtr->link[1] = stack[ht - 1];
                if (stack[ht - 1] == root) 
			    { 
                    root = rPtr;
                }
			    else
			    {
                    stack[ht - 2]->link[dir[ht - 2]] = rPtr;
                }
                dir[ht] = 1;
                stack[ht] = stack[ht - 1];
                stack[ht - 1] = rPtr;
                ht++;
                rPtr = stack[ht - 1]->link[0];
            }
            if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) && (!rPtr->link[1] || rPtr->link[1]->color == BLACK)) 
		    {
                rPtr->color = RED;
            }   
		    else
		    {
                if (!rPtr->link[0] || rPtr->link[0]->color == BLACK) 
			    {
                    qPtr = rPtr->link[1];
                    rPtr->color = RED;
                    qPtr->color = BLACK;
                    rPtr->link[1] = qPtr->link[0];
                    qPtr->link[0] = rPtr;
                    rPtr = stack[ht - 1]->link[0] = qPtr;
                }
                rPtr->color = stack[ht - 1]->color;
                stack[ht - 1]->color = BLACK;
                rPtr->link[0]->color = BLACK;
                stack[ht - 1]->link[0] = rPtr->link[1];
                rPtr->link[1] = stack[ht - 1];
                if (stack[ht - 1] == root)
			    {
                    root = rPtr;
                }
			    else
			    {
                    stack[ht - 2]->link[dir[ht - 2]] = rPtr;
                }
                break;
            }
        }
        ht--;
        }
    }
}
void inorder(struct rbNode *T)
{
	if(T==NULL)
	{
		return ;
	}
	inorder(T->link[0]);
	printf("%d(COLOR=%d)  ",T->data,T->color);
	inorder(T->link[1]);
}
void preorder(struct rbNode *T)
{
	if(T==NULL)
	{
		return ;
	}
	printf("%d(COLOR=%d)  ",T->data,T->color);
	preorder(T->link[0]);
	preorder(T->link[1]);
}
void postorder(struct rbNode *T)
{
	if(T==NULL)
	{
		return ;
	}
	postorder(T->link[0]);
	postorder(T->link[1]);
	printf("%d(COLOR=%d)  ",T->data,T->color);
}
int main()
{
	int x,n,i,op;
	do
	{
		printf("\nOUR OPTION WILL BE:");
		printf("\n1. CREATE:");
		printf("\n2. INSERATION:");
		printf("\n3. DELETE:");
		printf("\n4. DISPLAY:");
		printf("\n5. QUIT:");
		printf("\n\nENTER YOUR CHOICE:");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
			{
			    printf("\nENTER NUMBER OF ELEMENTS : ");
				scanf("%d",&n);
				printf("\nENTER TREE DATA : ");
				for(i=0;i<n;i++)
				{
					scanf("%d",&x);
					insertion(x);
				}
				break;
		    }
			case 2:
			{
			    printf("\nENTER A VALUE FOR INSERATION : ");
				scanf("%d",&x);
				insertion(x);
				break;
		    }
			case 3: 
			{
			    printf("\nENTER A VALUE FOR DELETION : ");
				scanf("%d",&x);
				deletion(x);
				break;
		    }
			case 4:
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
	}while(op!=5);
	return 0;
}

