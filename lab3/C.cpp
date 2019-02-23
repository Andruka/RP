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

#define SIZE_EXP    5

using namespace boost::interprocess;
using namespace std;

struct data{
	int status;
	double result;
	char expr[5];
};

double calc(char *buffer){
	int len=SIZE_EXP/2+1;
	double  chisla[SIZE_EXP/2+1];
	char signs[SIZE_EXP/2];
	int ind=0;
	for(int i=0;i<SIZE_EXP;++i){
		if(i%2)signs[i/2]=buffer[i];
		else chisla[i/2]=atof(&buffer[i]);
	}
	for(int t=len;t>1;--t){
		ind=0;
		for(int i=0;i<len-1;++i){
			if(signs[i]=='*'||signs[i]=='/'){
				ind=i;
				break;
			}
		}
		if(signs[ind]=='*')chisla[ind]=chisla[ind]*chisla[ind+1];
		if(signs[ind]=='/')chisla[ind]=chisla[ind]/chisla[ind+1];
		if(signs[ind]=='-')chisla[ind]=chisla[ind]-chisla[ind+1];
		if(signs[ind]=='+')chisla[ind]=chisla[ind]+chisla[ind+1];
		for(int i=ind+1;i<len-1;++i){
			chisla[i]=chisla[i+1];
		}
		for(int i=ind;i<len-1;++i){
			signs[i]=signs[i+1];
		}
	}
	return chisla[0];
}

int main(){
    managed_shared_memory managed_shm{open_only, "Table"};
  	pair<data*, std::size_t> expression = managed_shm.find<data>("Object");
	while(1){	
		for(int i=0;i<10;i++){
			if(expression.first[i].status==1){
				char arr[SIZE_EXP];
				strcpy( arr, expression.first[i].expr );
				expression.first[i].status=2;
				expression.first[i].result=calc(arr);
				for(int j=0;j<5;++j)cout<<expression.first[i].expr[j];
					cout<<endl;
					cout<<expression.first[i].result<<endl;

			}
		}
		usleep(4);
	}
}
