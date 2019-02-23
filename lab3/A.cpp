#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
using namespace std;

#define NAME_QUEUE  "/queue_expr"
#define SIZE_EXPR    5

 void gen(char *expression)
 {
    const char *digits[] = {"1","2", "3","4", "5", "6","7", "8", "9"};
    const char *signs[] = {"+","-", "*","/"};
    for(int i=0;i<SIZE_EXPR;i++){
        srand ( time(NULL)+i);
        if(i%2)    expression[i]=*signs[rand() % sizeof(signs)/sizeof(char*)];
        else    expression[i]=*digits[rand() % sizeof(digits)/sizeof(char*)];
        cout<<expression[i];              
    }
    cout<<endl;
 }

 
int main(int argc, char** argv) {
	mqd_t mq_expr;
    char expression[SIZE_EXPR]; 
    mq_expr = mq_open(NAME_QUEUE, O_WRONLY);
    while(1) {
        gen(expression);
        mq_send(mq_expr, expression, SIZE_EXPR, 0);
	sleep(4);
    }
    mq_close(mq_expr);
	return 0;
 
}

