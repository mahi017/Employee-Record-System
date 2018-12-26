#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct employee_node_tag
{
	char name[50];
	int level;
	struct employee_node_tag *reportee1;
	struct employee_node_tag *reportee2;
}employee_node;

employee_node *Boss;

typedef struct avl_tree_node_tag
{
	char name[50];
	int height;
	employee_node *pos;
	struct avl_tree_node_tag *left;
	struct avl_tree_node_tag *right;
}avl_tree_node;

avl_tree_node *MakeAVL_tree_node(char name[],employee_node *pos)
{
	avl_tree_node *p;
	p=(avl_tree_node *)malloc(sizeof(avl_tree_node));
	strcpy(p->name,name);
	p->height=1;
	p->pos=pos;
	p->left=NULL;
	p->right=NULL;
	return p;
}

employee_node *MakeEmployee_node(char name[])
{
	employee_node *p;
	p=(employee_node *)malloc(sizeof(employee_node));
	strcpy(p->name,name);
	p->level=0;
	p->reportee1=NULL;
	p->reportee2=NULL;
	return p;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int heightAVL(avl_tree_node *p)
{
	int height;
    if (p == NULL)
    {
        height = 0;
	}
    else
    {
		height = p->height;
	}
	return height;
}

avl_tree_node *RotateLeft(avl_tree_node *p)
{
	avl_tree_node *temp;
	if(p==NULL)
	{
		printf("error");	
	}	
	else if(p->right==NULL)
	{
		printf("cannot rotate");
	}
	else
	{
		temp=p->right;
		p->right=temp->left;
		temp->left=p;
		temp->height = 1+max(heightAVL(temp->left),heightAVL(temp->right));
		p->height = 1+max(heightAVL(p->left),heightAVL(p->right));
	}
	return temp;
}

avl_tree_node *RotateRight(avl_tree_node *p)
{
	avl_tree_node *temp;
	if(p==NULL)
	{
		printf("error");
	}
	else if(p->left==NULL)
	{
		printf("cannot rotate");
	}
	else
	{
		temp=p->left;
		p->left=temp->right;
		temp->right=p;
		temp->height=1+max(heightAVL(temp->left),heightAVL(temp->right));
		p->height=1+max(heightAVL(p->left),heightAVL(p->right));
	}
	
	return temp;
}

int bal_factor(avl_tree_node *p)
{
	int bal_fac;
    if (p == NULL)
    {
        bal_fac = 0;
	}
    else
    {
		bal_fac = heightAVL(p->left) - heightAVL(p->right);
	}
	return bal_fac;
}

avl_tree_node* insertAVL(avl_tree_node* root,avl_tree_node *new_node)
{
    int balance;
    if (root == NULL)
    {
        root = new_node;
 	}
    else if (strcmp(new_node->name,root->name) < 0)
    {
        root->left  = insertAVL(root->left, new_node);
	}
    else if(strcmp(new_node->name,root->name) > 0)
    {
        root->right = insertAVL(root->right, new_node);
	}
	else
	{
		;
	}
 
    root->height = 1 + max(heightAVL(root->left),heightAVL(root->right));
 
	balance = bal_factor(root);
 
    // Left Left Case 
    if (balance == 2 && bal_factor(root->left) == 1)
    {
        root = RotateRight(root);
    }
 	// Right Right Case
    if (balance == -2 && bal_factor(root->right) == -1)
    {
        root = RotateLeft(root);
 	}
    // Left Right Case
    if (balance == 2 && bal_factor(root->left) == -1)
    {
        root->left =  RotateLeft(root->left);
        root = RotateRight(root);
    }
 
    // Right Left Case
    if (balance == -2 && bal_factor(root->right) == 1)
    {
        root->right = RotateRight(root->right);
        root = RotateLeft(root);
    }
    return root;
}

avl_tree_node *findCEO_AVL(avl_tree_node *avl_tree,char b_ceo[])
{
	avl_tree_node *ptr=avl_tree;
	while(ptr!=NULL && strcmp(b_ceo,ptr->name) != 0)
	{
		if(strcmp(b_ceo,ptr->name) < 0)
		{
			ptr=ptr->left;
		}
		if(strcmp(b_ceo,ptr->name) > 0)
		{
			ptr=ptr->right;
		}
	}
	return ptr;
}

employee_node *searchAVL(avl_tree_node *root,char name[])
{
	employee_node *pos=NULL;
	if(root!=NULL)
	{
		if(strcmp(name,root->name) < 0)
		{
			pos=searchAVL(root->left,name);
		}
		else if(strcmp(name,root->name) > 0)
		{
			pos=searchAVL(root->right,name);
		}
		else
		{
			pos=root->pos;
		}
	}
	return pos;
}


employee_node *InsertEmployee(employee_node *boss,employee_node *reportee)
{
	employee_node *ret_val;
	if(boss->reportee1==NULL)
	{
		boss->reportee1=reportee;
		ret_val=boss->reportee1;
	}
	else
	{
		if(boss->reportee2==NULL)
		{
			boss->reportee2=reportee;
			ret_val=boss->reportee2;
		}
	}
	return ret_val;
}


void printlevel(employee_node *root,int level)
{
	if(root!=NULL)
    {
        if(level==1)
        {
            printf("\n%s : ",root->name);
            if(root->reportee1!=NULL)
            {
            	printf("%s ",root->reportee1->name);
			}
			if(root->reportee2!=NULL)
			{
				printf("%s",root->reportee2->name);
			}
        }
        if(level > 1)
        {
           	printlevel(root->reportee1,level-1);
           	printlevel(root->reportee2,level-1);
        }
    }
}

int height_tree(employee_node *root)
{
	int height=-1;
	if(root!=NULL)
	{
		if(root->reportee1==NULL && root->reportee2==NULL)
		{
			height=0;
		}
		else
		{
			height=1+max(height_tree(root->reportee1),height_tree(root->reportee2));
		}
	}
	return height;
}

int no_of_nodes(avl_tree_node *root)
{
	int n;
	if(root==NULL)
	{
		n=0;
	}
	else
	{
		n = 1 + no_of_nodes(root->left) + no_of_nodes(root->right);
	}
	return n;
}

void preOrder(avl_tree_node *root)
{
	if(root!=NULL)
	{
		printf("%s ",root->name);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void findBoss(employee_node *root,employee_node *employee,int level)
{
		if(root!=NULL)
		{
			if(level == 1)
			{
				if((root->reportee1 == employee) || (root->reportee2 == employee))
				{
					//printf("%s ",root->name);
					Boss=root;
				}
			}
			if(level > 1)
			{
				findBoss(root->reportee1,employee,level-1);
				findBoss(root->reportee2,employee,level-1);
			}
		}
	
}

void printBosses(employee_node *root,employee_node *employee)
{
	int i;
	Boss=employee;
	for(i=employee->level - 1;i>0;i--)
	{
		findBoss(root,Boss,i);
		printf("%s ",Boss->name);
	}
}

void LCBoss(employee_node *root,employee_node *employee1,employee_node *employee2)
{
	int n,i,l;
	n=max(employee1->level,employee2->level);
	employee_node emp1[n],emp2[n];
	Boss=employee1;
	for(i=employee1->level - 1;i>0;i--)
	{
		findBoss(root,Boss,i);
		emp1[i]=*(Boss);
	}
	Boss=employee2;
	for(i=employee2->level - 1;i>0;i--)
	{
		findBoss(root,Boss,i);
		emp2[i]=*(Boss);
	}
	if(employee1->level < employee2->level)
	{
		l=employee1->level;
	}
	else
	{
		l=employee2->level;
	}
	i=l-1;
	while(strcmp(emp1[i].name,emp2[i].name) != 0 && i>1)
	{
		i--;
	}
	printf(" %s",emp1[i].name);
}


avl_tree_node* deleteAVL(avl_tree_node *root, char name[])
{
	avl_tree_node *p;
    if (root == NULL)
        return root;

    if ( strcmp(name,root->name) < 0 )
        root->left = deleteAVL(root->left, name);
 
    else if( strcmp(name,root->name) > 0 )
        root->right = deleteAVL(root->right, name);
 
    else
    {
        if(root->left == NULL)
        {
        	p=root;
     	    root=root->right;
     	    free(p);
        }
        else if(root->right == NULL)
        {
        	p=root;
        	root=root->left;
        	free(p);
		}
        else
        {
        	p=root->left;
			while(p->right!=NULL)
			{
				p=p->right;
			}
			strcpy(root->name,p->name);
			root->pos=p->pos;
            root->left = deleteAVL(root->left, p->name);
        }
    }
 
    if (root != NULL)
  	{
    	root->height = 1 + max(heightAVL(root->left),heightAVL(root->right));
 
        int balance = bal_factor(root);

    	// Left Left Case
    	if (balance > 1 && bal_factor(root->left) >= 0)
        root = RotateRight(root);
 
    	// Left Right Case
    	if (balance > 1 && bal_factor(root->left) < 0)
    	{
        	root->left =  RotateLeft(root->left);
        	root = RotateRight(root);
    	}
 
	    // Right Right Case
    	if (balance < -1 && bal_factor(root->right) <= 0)
        root = RotateLeft(root);
 
    	// Right Left Case
    	if (balance < -1 && bal_factor(root->right) > 0)
    	{
        	root->right = RotateRight(root->right);
        	root = RotateLeft(root);
    	}
	}
 	return root;
}

employee_node *deleteEmployee(employee_node *b,employee_node *employee)
{
	employee_node *ret_val,*p;
	if(employee->reportee1!=NULL && employee->reportee2!=NULL)
	{
		printf("\nCannot Delete");
		ret_val=b;
	}
	else
	{
		if(employee->reportee1==NULL)
		{
			p=employee;
			b=employee->reportee2;
			free(p);	
		}	
		else
		{
			p=employee;
			b=employee->reportee1;
			free(p);
		}
		ret_val=b;
	}
	return b;
}

void Inorder(avl_tree_node *root)
{
	if(root!=NULL)
	{
		Inorder(root->left);
		printf("%s ",root->name);
		Inorder(root->right);
	}
}

void ChangeLevel(employee_node *root)
{
	if(root!=NULL)
	{
		ChangeLevel(root->reportee1);
		root->level--;
		ChangeLevel(root->reportee2);
	}
}

main()
{
	avl_tree_node *avl_tree=NULL,*new_avl_node,*node;
	employee_node *employee_tree=NULL,*b,*pos,*new_employee,*p,*employee,*employee1;
	int ex=0,choice,level,found;
	char name[50],ceo_name[50],name1[50];
	while(ex==0)
	{
		printf("\n---------------------------------------------------");
		printf("\n1. Add CEO");
		printf("\n2. Add Employee");
		printf("\n3. Print names of all Employees at Level L");
		printf("\n4. Print bosses of an employee");
		printf("\n5 .Delete Employee");
		printf("\n6 .Lowest common Boss of two employees");
		printf("\n7. Number of nodes in left subtree of AVL tree\n   Number of nodes in right subtree of AVL tree\n   Pre-Order traversal of AVL tree");
		printf("\n8. Exit");
		printf("\n---------------------------------------------------");
		printf("\nEnter Choice : ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("\nEnter CEO name : ");
				scanf("%s",name);
				if(employee_tree!=NULL)
				{
					strcpy(ceo_name,employee_tree->name);
					strcpy(employee_tree->name,name);
					node = findCEO_AVL(avl_tree,ceo_name);
					new_avl_node = MakeAVL_tree_node(name,node->pos);
					avl_tree = deleteAVL(avl_tree,ceo_name);
					avl_tree = insertAVL(avl_tree,new_avl_node);
					printf("\n");
					Inorder(avl_tree);
					
				}
				else
				{
					employee_tree = MakeEmployee_node(name);
					employee_tree->level = 1;
					new_avl_node = MakeAVL_tree_node(name,employee_tree);
					avl_tree = new_avl_node;
				}
				
				
				printf("\nCEO : %s",employee_tree->name);
				break;
				
			case 2:
				printf("\nEnter Boss name : ");
				scanf("%s",name);
				b=searchAVL(avl_tree,name);
				if(b==NULL)
				{
					printf("\n%s not found",name);
				}
				else
				{
					if(b->reportee1!=NULL && b->reportee2!=NULL)
					{
						printf("\n%s has two reportees",name);
					}
					else
					{
						printf("\nEnter reportee name : ");
						scanf("%s",name);
						new_employee = MakeEmployee_node(name);
						new_employee->level = b->level + 1;
						pos = InsertEmployee(b,new_employee);
						new_avl_node = MakeAVL_tree_node(name,pos);
						avl_tree = insertAVL(avl_tree,new_avl_node);
						
					}
					printf("\n%s : ",b->name);
					if(b->reportee1!=NULL)
					{
						printf("%s ",b->reportee1->name);
					}
					if(b->reportee2!=NULL)
					{
						printf("%s ",b->reportee2->name);
					}
				}
				printf("\nInoder:");
				Inorder(avl_tree);
				printf("\nPreorder:");
				preOrder(avl_tree);
				break;
			case 3:
				printf("\nEnter level : ");
				scanf("%d",&level);
				if(level > height_tree(employee_tree) + 1)
				{
					printf("\nlevel is greater than height of tree");
				}
				else
				{
					printlevel(employee_tree,level);
				}
				break;
			case 4:
				printf("\nEnter employee name : ");
				scanf("%s",name);
				b=searchAVL(avl_tree,name);
				if(b==NULL)
				{
					printf("\n%s not found",name);
				}
				else
				{
					printf("\n%s { ",name);
					printBosses(employee_tree,b);
					printf("}");
				}
				break;
			case 5:
				printf("\nEnter Boss name : ");
				scanf("%s",name);
				b=searchAVL(avl_tree,name);
				if(b==NULL)
				{
					printf("\n%s not found",name);
				}
				else
				{
					printf("\nEnter employee name : ");
					scanf("%s",name);
					found=0;
					if(b->reportee1!=NULL)
					{
						if(strcmp(b->reportee1->name,name) == 0)
						{
							found=1;
							employee=b->reportee1;
							b->reportee1 = deleteEmployee(b->reportee1,employee);
							ChangeLevel(b->reportee1);
						}
					}
					if(b->reportee2!=NULL && found==0)
					{
						if(strcmp(b->reportee2->name,name) == 0)
						{
							found=1;
							employee=b->reportee2;
							b->reportee2 = deleteEmployee(b->reportee2,employee);
							ChangeLevel(b->reportee2);
						}
					}
					if(found==0)
					{
						printf("\n%s not found",name);
					}
					else
					{
						
						if(employee->reportee1==NULL || employee->reportee2==NULL)
						{
							avl_tree = deleteAVL(avl_tree,name);
						}
					}
					printf("\n");
					Inorder(avl_tree);
				}
				break;
			case 6:
				printf("\nEnter employee name : ");
				scanf("%s",name);
				printf("\nEnter employee name : ");
				scanf("%s",name1);
				employee=searchAVL(avl_tree,name);
				if(employee==NULL)
				{
					printf("\n%s not found",name);
				}
				employee1=searchAVL(avl_tree,name1);
				if(employee1==NULL)
				{
					printf("\n%s not found",name1);
				}
				if(employee!=NULL && employee1!=NULL)
				{
					printf("\n{ %s %s }",name,name1);
					if(employee==employee_tree || employee1==employee_tree)
					{
						printf("%s",employee_tree->name);
					}
					else
					{
						LCBoss(employee_tree,employee,employee1);
					}
				}
				break;
			case 7:
				if(avl_tree!=NULL)
				{
					printf("\nNumber of nodes in left subtree of AVL tree : %d",no_of_nodes(avl_tree->left));
					printf("\nNumber of nodes in right subtree of AVL tree : %d",no_of_nodes(avl_tree->right));
					printf("\nPre-Order Traversal of AVL tree\n");
					preOrder(avl_tree);
				}
				else
				{
					printf("\nTree is Empty");
				}
				break;
			case 8:
				ex=1;
				break;
			default :
				printf("\nINVALID CHOICE");
				break;	
		}
	}
}
