#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>


#define QUEUE_NAME  "/queue_expr"
#define SIZE_EXP    5

using namespace boost::interprocess;
using namespace std;

struct data{
	int status;
	double result;
	char expr[5];
};

int main(){
    shared_memory_object::remove("Table");
    managed_shared_memory managed_shm{open_or_create, "Table", 1024};
    data *expression  = managed_shm.construct<data>("Object")[10]();
	mqd_t mq_expr;
	int flag;
	ssize_t bytes_read;
    struct mq_attr attr;
    char buffer[SIZE_EXP];
 
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = SIZE_EXP;
    attr.mq_curmsgs = 0;
 
	mq_expr = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY | O_NONBLOCK, 0644, &attr);
	while(1){
		memset(buffer, 0x00, sizeof(buffer));
		bytes_read = mq_receive(mq_expr, buffer, SIZE_EXP, NULL);
		if(bytes_read >= 0){
			flag=0;
        	for(int i=0;i<10;i++){
				if(expression[i].status==0){
					expression[i].status=1;
					strcpy(expression[i].expr,buffer);
					flag=1;
					for(int j=0;j<SIZE_EXP;++j)cout<<expression[j].expr;
					cout<<endl;
                	break;  
				}
			}
			if(flag==0){
                std::cout<<"Не хватает памяти\n";
                exit(1);   
            }
		} 
		usleep(4);
	}
    
}
