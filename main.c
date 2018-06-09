/**
@file
BLM2512 Final Homework
@author
Name: Berna Tasel
Student no: 15011049
Date: 10.06.2018
E-Mail: bernataselbal@gmail.com
Compiler used:  GCC
IDE:   CodeBlocks
Operating System Windows 10  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define SIZE 255

// A structure to represent a stack
struct Stack{
    int top;
    int topn;
    unsigned capacity;
    char *array;
    int *numbs;
};

struct Variable{
    char variableName;
    int variableValue;
};


struct Stack* createStack(unsigned );
int isFull(struct Stack* );
int isEmpty(struct Stack* );
void push(struct Stack* , char );
char pop(struct Stack* );
int isFulln(struct Stack* );
int isEmptyn(struct Stack* );
void pushn(struct Stack* , int );
int popn(struct Stack* );
int getPriority(char );
void showAllVariables(struct Variable *, int );
void printStackCh(struct Stack *);
void printStackNum(struct Stack * );

int isVariable(struct Variable *variables,char tmp,int size){
    int i=0;
    int flag=0;
    while(i<size && !flag){
        if(variables[i].variableName==tmp){
            flag = 1;
        }
        i++;
    }
    if(flag == 1){
        return i-1;
    }
    else
        return -1;
}




int main()
{
	printf("BLM2512 Final Homework\n");
	printf("Press enter for continue...\n");
	getchar();
	int size=0;
	struct Variable variables[SIZE];
	FILE *file;
    file = fopen("input.txt", "r+");
    if(file == NULL){
        printf("Input file cannot be opened!");
        exit(1);
    }
	while(!feof(file)){
	    struct Stack* stack = createStack(SIZE);
		char *func = (char *) calloc(SIZE, sizeof(char));
		char *post = (char *) calloc(SIZE, sizeof(char));
		int i=0;

		fgets(func, SIZE, (FILE*)file);
        printf("\nOperation :\n%s", func);
        getchar();
		char theVariable = *(func);
		while(*(func++) != '=');
		printf("Infix translated to postfix...");
		while(*(++func) != ';'){
			if(*(func) != ' '){
				if(isdigit(*(func))){
					post[i++] = *(func);
					post[i++] = ' ';
				}
				else if(getPriority(*(func)) <= 4){
					char tmp = pop(stack);
					while(tmp != '\0' && getPriority(tmp) < getPriority(*(func))){
						post[i++] = tmp;
						post[i++] = ' ';
						tmp = pop(stack);
					}
					if(tmp != '\0')
						push(stack, tmp);
					push(stack, *(func));
				}
				else if(*(func) == '('){
					push(stack, *(func));
				}
				else if(*(func) == ')'){
					char tmp = pop(stack);
					while(tmp != '('){
						post[i++] = tmp;
						post[i++] = ' ';
						tmp = pop(stack);
					}
				}
				else{
					post[i++] = *(func);
					post[i++] = ' ';
				}
				printf("\nPostfix: %-50s", post );
				printStackCh(stack);
			}
		}
		char tmp = pop(stack);
		while(tmp != '\0')
		{
			post[i++] = tmp;
			post[i++] = ' ';
			printf("\nPostfix: %-50s", post );
			printStackCh(stack);
			tmp = pop(stack);

		}
		post[i++] = '\0';
        getchar();

        printf("\nCalculating for postfix: %s variables: ",post);
        showAllVariables(variables,size);
		int numb = 0;
		while(*(post) != '\0')
		{
			if(isdigit(*post))
			{
				numb *=10;
				numb += *(post) - '0';
			}
			else if(*(post) == ' ')
			{
				if(numb != 0)
				{
					pushn(stack ,numb);
					numb = 0;
				}
			}
			else if(getPriority(*(post)) <= 4)
			{
				if(numb != 0)
					pushn(stack, numb);
				if(*(post) == '+')
					pushn(stack, (popn(stack) + popn(stack)));
				else if(*(post) == '-')
				{
					int numb1 = popn(stack);
					int numb2 = popn(stack);
					pushn(stack, (numb2 - numb1));
				}
				else if(*(post) == '/')
				{
					int numb1 = popn(stack);
					int numb2 = popn(stack);
					pushn(stack, (numb2 / numb1));
				}
				else if(*(post) == '*')
					pushn(stack, (popn(stack) * popn(stack)));

			}
			else
			{
				int j = size;
				while(variables[j--].variableName != *(post));
				pushn(stack, variables[j+1].variableValue);
			}
            *(post++);
            printf("\n");
			printStackNum(stack);
		}

        if(isVariable(variables,theVariable,size)> -1){
            variables[isVariable(variables,theVariable,size)].variableValue = popn(stack);
        }
        else{
            variables[size].variableName = theVariable;
            variables[size++].variableValue = popn(stack);
        }
		printf("\n%c <- %d\n" ,variables[isVariable(variables,theVariable,size)].variableName, variables[isVariable(variables,theVariable,size)].variableValue);
		getchar();
	}
    printf("\nALL VARIABLES:\n");
    showAllVariables(variables, size);

    return 0;
}

// function to create a stack of given capacity. It initializes size of
struct Stack* createStack(unsigned capacity){
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->topn = -1;
    stack->array = (char *) calloc(stack->capacity, sizeof(char));
    stack->numbs = (int *) calloc(stack->capacity, sizeof(int));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack){
    if(stack->top == SIZE){
        return 1;
    }
    else{
        return 0;
    }
}

// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack){
    if(stack->top == -1){
        return 1;
    }
    else {
        return 0;
    }
}

// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, char item){
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Function to pop an item from stack.  It decreases top by 1
char pop(struct Stack* stack){
    if (isEmpty(stack))
        return '\0';
    return stack->array[stack->top--];
}

//Number stack
int isFulln(struct Stack* stack){
    if(stack->topn == SIZE){
        return 1;
    }
    else{
        return 0;
    }
}

// Stack is empty when top is equal to -1
int isEmptyn(struct Stack* stack){
    if(stack->topn == -1){
        return 1;
    }
    else {
        return 0;
    }
}

// Function to add an item to stack.  It increases top by 1
void pushn(struct Stack* stack, int item){
    if (isFulln(stack))
        return;
    stack->numbs[++stack->topn] = item;
}

// Function to pop an item from stack.  It decreases top by 1
int popn(struct Stack* stack){
    if (isEmptyn(stack))
        return -1;
    return stack->numbs[stack->topn--];
}

int getPriority(char ch){
	int i = 0;
	char *priority = "*/-+";
	while(priority[i++] != ch);
	return i;
}

void showAllVariables(struct Variable *variables, int size){
    int i;
	for(i=0; i<size; i++){
        printf("%c<-%d  ", variables[i].variableName, variables[i].variableValue);
	}
}

//print stack to console
void printStackCh(struct Stack *stack){
    int i;
    if(stack->top == -1){
        printf("Stack: empty");
    }
    else{
        printf("Stack: ");
        for(i=0 ; i <= stack->top; i++){
            printf("%c ",(stack->array[i]));
        }
    }
}

//print stack to console
void printStackNum(struct Stack * stack){
    int i;
    if(stack->topn == -1){
        printf("Stack: empty");
    }
    else{
        printf("Stack: ");
        for(i=0 ; i <= stack->topn; i++){
            printf("%d ",(stack->numbs[i]));
        }
    }
}
