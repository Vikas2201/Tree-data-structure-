#include<stdio.h>
#include<stdlib.h>
struct trie
{
 struct trie *alpha[26];
 int flag;
};

typedef struct trie trie;

trie *root;

trie *createnode()
{
  trie *node=(trie*)malloc(sizeof(trie));
  int i;
  for(i=0;i<26;i++)
  {
    node->alpha[i]=NULL;
  }
  node->flag=0;
  return node;
}

int search_insert_delete(trie *node, char *word, char mode)
{
  if(!node) 
 {
   if(mode=='i') 
  {
   printf("\nCreating root node..."); 
   node=createnode(); 
   root=node; 
  }
  else if(mode=='s' || mode=='d') 
  {
    printf("\nRoot node does not exist."); 
    return 1;
  }
 }
 while(*word)
 {
   int index=(*word|('A'^'a'))-'a';
   if(!node->alpha[index]) 
   {
     if(mode=='i') 
     {
       printf("\nCreating node for character '%c'...",*word); 
       node->alpha[index]=createnode();
     }
     else if(mode=='s' || mode=='d') 
    {  
      printf("\nNo node found for character '%c'.",*word); 
      return 1;  
    }
   }
   node=node->alpha[index];
   word++;
 }
 if(!node->flag) 
 {
   if(mode=='i') 
  { 
    printf("\nSetting wordflag..."); 
    node->flag=1; 
    return 0;
  }
  else if(mode=='s' || mode=='d') 
  {  
    printf("\nWordflag not set."); 
	return 1;
  }
 }
  else if(mode=='d') 
  {
    printf("\nResetting wordflag..."); 
    node->flag=0; 
    return 0;
  }
  else return 0; 
}   

int main()
{
 int choice;
 do
 {
  char word[10];
  int result;
  printf("\n\n1. Enter into trie ");
  printf("\n2. Search from trie  ");
  printf("\n3. Delete from trie ");
  printf("\n4. Exit ");
  printf("\n\nEnter your choice: ");
  scanf("%d",&choice);
  switch(choice)
  {
    case 1: 
    {
        printf("\nEnter the word to be inserted: ");
        scanf("%s",word);
        result=search_insert_delete(root,word,'i');
        if(!result) 
		{
		   printf("\nInsertion successful!");
	    }
        break;
    }
    case 2:
	{
	    printf("\nEnter the word to be searched: ");    
        scanf("%s",word);            
        result=search_insert_delete(root,word,'s');
        if(result==0) 
		{
		    printf("\nSearch successful!\nThe word is present in the trie."); 
        }
		else
		{
		    printf("\nSearch unsuccessful!\nThe word is not present in the trie!");
        }
		break;
	}
    case 3 :
	{
	    printf("\nEnter the word to be deleted: ");    
        scanf("%s",word);            
        result=search_insert_delete(root,word,'d');
        if(result==0)
		{
		    printf("\nDeletion successful!"); 
        }
		else
		{
		    printf("\nSearch unsuccessful!\nThe word is not present in the trie!");
        }
		break;
	}
    case 4 :
	{
		break;
	}
    default:
	{
		printf("Enter correct choice ");
		break;
	} 
  }
 }
 while(choice!=4);
}                 
