#include <stdio.h>
#include <stdlib.h>
#define MAX 3
#define MIN 2
struct BNode
{
  int val[MAX + 1], count;
  struct BNode *link[MAX + 1];
};
struct BNode *root;
struct BNode *createNode(int val, struct BNode *child)
{
    struct BNode *new_node;
    new_node = (struct BNode *)malloc(sizeof(struct BNode));
    new_node->val[1] = val;
    new_node->count = 1;
    new_node->link[0] = root;
    new_node->link[1] = child;
    return new_node;
}
void insert(int val, int pos, struct BNode *node,struct BNode *child) 
{
    int j = node->count;
    while (j > pos) 
	{
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1] = val;
    node->link[j + 1] = child;
    node->count++;
}
void splitNode(int val, int *pval, int pos, struct BNode *node, struct BNode *child, struct BNode **newnode)
{
    int median, j;
    if (pos > MIN)
    {
	    median = MIN + 1;
    }
    else
    {
        median = MIN;
    }
    *newnode = (struct BNode *)malloc(sizeof(struct BNode));
    j = median + 1;
    while (j <= MAX) 
	{
        (*newnode)->val[j - median] = node->val[j];
        (*newnode)->link[j - median] = node->link[j];
        j++;
    }
    node->count = median;
    (*newnode)->count = MAX - median;
    if (pos <= MIN) 
	{
        insert(val, pos, node, child);
    } 
	else 
	{
        insert(val, pos - median, *newnode, child);
    }
    *pval = node->val[node->count];
    (*newnode)->link[0] = node->link[node->count];
    node->count--;
}
int setValue(int val, int *pval,struct BNode *node, struct BNode **child)
{
    int pos;
    if (!node) 
	{
        *pval = val;
        *child = NULL;
        return 1;
    }
    if (val < node->val[1]) 
	{
        pos = 0;
    }
	else
	{
        for (pos = node->count;(val < node->val[pos] && pos > 1); pos--)
        {
		    if (val == node->val[pos]) 
			{
                printf("\nDUPLICATES ARE NOT ALLOWS");
                return 0;
            }
        }
        if (setValue(val, pval, node->link[pos], child)) 
		{
            if (node->count < MAX) 
			{
                insert(*pval, pos, node, *child);
            }
			else
			{
                splitNode(*pval, pval, pos, node, *child, child);
                return 1;
            }
        }
    }
    return 0;
}
void INSERTION(int val)
{
    int i , j ;
    struct BNode *child;
    j = setValue(val, &i, root, &child);
    if (j)
    {
	    root = createNode(i, child);
    }
}
void search(int val, int *pos, struct BNode *Node) 
{
    if (!Node) 
	{
        return;
    }
    if (val < Node->val[1]) 
	{
        *pos = 0;
    } 
	else 
	{
        for (*pos = Node->count;(val < Node->val[*pos] && *pos > 1); (*pos)--)
        ;
        if (val == Node->val[*pos]) 
		{
            printf("%d IS FOUND ", val);
            return;
        }
    }
    search(val, pos, Node->link[*pos]);
    return;
}
void traversal(struct BNode *Node) 
{
    int i;
    if (Node)
	{
        for (i = 0; i < Node->count; i++) 
	    {
            traversal(Node->link[i]);
            printf("%d ", Node->val[i + 1]);
        }
        traversal(Node->link[i]);
    }
}
int main()
{
	int x,n,i,op,ch;
	do
	{
		printf("\nOUR OPTION WILL BE:");
		printf("\n1. CREATE:");
		printf("\n2. INSERATION:");
		printf("\n3. SEARCHING:");
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
					INSERTION(x);
				}
				break;
		    }
			case 2:
			{
			    printf("\nENTER A VALUE FOR INSERATION : ");
				scanf("%d",&x);
				INSERTION(x);
				break;
		    }
			case 3: 
			{
			    printf("\nENTER A VALUE FOR SEARCHING : ");
				scanf("%d",&x);
				search(x, &ch, root);
				break;
		    }
			case 4:
			{
			    printf("\nELEMENT IN BTREE IS  : ");
				traversal(root);
				break;
			}
		}
	}while(op!=5);
	return 0;
}

