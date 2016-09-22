#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
        char data[40];
        struct Node *left, *right;
}TREE;

char* oper[2] = {"ln", "tg"};

void inOrder(TREE* tree)
{
	if(tree!=NULL)
	{
		inOrder(tree->left);
		if(strcmp(tree->data,"#") != 0) printf("%s ",tree->data);
		inOrder(tree->right);
	}
}

void preOrder(TREE* tree)
{
	if(tree!=NULL)
	{
		if(strcmp(tree->data,"#") != 0) printf("%s ",tree->data);
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

void postOrder(TREE* tree)
{
	if(tree!=NULL)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		if(strcmp(tree->data,"#") != 0) printf("%s ",tree->data);
	}
}

void PrintTree(TREE *head,int x1,int x2,int y)
{
     if(head==NULL) return;

if(head->left!=NULL) PrintTree(head->left,x1,x1+(x2-x1)/2,y+2);
     window(1,1,81,25);
     gotoxy(x1+(x2-x1)/2,y);
     puts(head->data);
     if(head->right!=NULL) PrintTree(head->right,x1+(x2-x1)/2,x2,y+2);
}

int Priority ( char c )
{
        switch ( c ) {
                case '+': case '-': return 1;
                case '*': case '/': return 2;
                case '^': return 3;
                case 'l': case 't': return 4;
        }
        return 10;
}

TREE* MakeTree (char Str[], int first, int last)
{
int MinPrt, i, k, prt;
int nest = 0;
TREE *Tree = (TREE*)malloc(sizeof(TREE));
MinPrt = 10;
for ( i = first; i <= last; i ++ ) {
        if ( Str[i] == '(' )
                { nest ++; continue; }
        if ( Str[i] == ')' )
                { nest --; continue; }
        if ( nest > 0 ) continue;
        prt = Priority ( Str[i] );
        if ( prt <= MinPrt ) {
                MinPrt = prt;
                k = i;
        }
}
if ( MinPrt == 10)
        if(Str[first]== '(' && Str[last]==')' )
                if(Str[first+1] == '-'){
                        Str[first] = '0';
                        free(Tree);
                        return MakeTree(Str, first, last-1);
                }
                else{
                        free(Tree);
                        return MakeTree(Str, first+1, last-1);
                }

else{
                k = last - first + 1;
                strncpy(Tree->data, Str+first, k);
                Tree->data[k] = '\0';
                Tree->left = NULL;
                Tree->right = NULL;
                return Tree;
        }

if(Str[k] == 'l' || Str[k] == 't') {
        if(Str[k] == 'l') strcpy(Tree->data, oper[0]);
        if(Str[k] == 't') strcpy(Tree->data, oper[1]);
        Str[k] = '#';
        Tree->left = MakeTree (Str,first,k);
        Tree->right = MakeTree (Str,k+2,last);
}
else{
        Tree->data[0] = Str[k];
        Tree->data[1] = '\0';
        Tree->left = MakeTree (Str,first,k-1);
        Tree->right = MakeTree (Str,k+1,last);
}
return Tree;
}


void main(void){
        TREE* tree;
        char s[100];
        int k,key;


        while(1)
        {
                clrscr();
                printf("1)Enter expressions\n2)View tree\n3)Detours\nESC - Exit");
                key = getch();
                if(key == 49){
                        clrscr();
                        gets(s);
                        k = strlen(s);
                        tree = MakeTree(s, 0, k-1);
                        getch();
                }
                if(key == 50){
                        clrscr();
                        PrintTree(tree,0,80,1);

getch();
                }
                if(key == 51){
                        clrscr();
                        inOrder(tree);
                        printf("\n");
                        preOrder(tree);
                        printf("\n");
                        postOrder(tree);
                        getch();
                }
                if(key == 27) exit(0);
        }
}
