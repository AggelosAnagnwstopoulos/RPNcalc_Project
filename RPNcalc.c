#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER 1 /* signal that a number was found */
#define BUFSIZE 100
#define MAXVAL 100
#define MAXLINE 100

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
int mgetline(char* s, int lim);
void clearsp(void);

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;
int li = 0; /*Line index*/
char line[MAXLINE];


/* reverse Polish calculator */
int main(){
    int type;
    double op1,op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
              push(atof(s));
              break;
            case '+':
              push(pop() + pop());
              break;
            case '*':
              push(pop() * pop());
              break;
            case '-':
              op2 = pop();
              push(pop() - op2);
              break;
            case '/':
              op2 = pop();
              if (op2 != 0.0)
                  push(pop() / op2);
              else
                  printf("error: zero divisor\n");
                  break;
            case 'c':
                clearsp();
                break;
            case 'd':
                op2=pop();
                push(op2);
                push(op2);
                break;
            case 's':
                op1=pop();
                op2=pop();
                push(op1);
                push(op2);
                break;
            case '\n':
              printf("\t%.8g\n", pop());
              break;
            default:
              printf("error: unknown command %s\n", s);
              break;
        }
    }
    return 0;
}

void clearsp(){
  sp = 0;
}

void push(double f){
    if(sp < MAXVAL)
        val[sp++]=f;
    else
        printf("error:stack full, cant push %g\n",f);
}

double pop(void){
    if(sp>0)
        return val[--sp];
    else{
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(char s[]){
    int c,i=0;

    if(line[li] == '\0')
        if(mgetline(line,MAXLINE) == 0)
            return EOF;
        else
            li =0;
    while((s[0] = c = line[li++]) == ' ' || c == '\t');

    s[1] = '\0';
    if(!isdigit(c) && c!= '.')
        return c;
    if(isdigit(c))
        while(isdigit(s[++i] = c = line[li++]));
    if( c == '.')
        while(isdigit(s[++i] = c = line[li++]));
    s[i] = '\0';
    li--;
    return NUMBER;
}

int mgetline(char s[],int lim){
    int i,c;
    for(i=0;i<lim-1 && (c=getchar())!=EOF && c!='\n';++i)
        s[i] =c;
    if(c=='\n')
        s[i++] =c;
    s[i]='\0';
    return i;
}
