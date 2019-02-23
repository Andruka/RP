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

int main(){
	ofstream fout("out.txt");
    managed_shared_memory managed_shm{open_only, "Table"};
  	pair<data*, std::size_t> arr = managed_shm.find<data>("Object");
	while(1){
    	for(int i=0;i<10;i++){
                if(arr.first[i].status==2){
                    arr.first[i].status=0;
                    fout<<arr.first[i].result<<"  ";
					for(int j=0;j<5;++j)fout<<arr.first[i].expr[j];
					fout<<" i= "<<i<<endl;
                }
		}
		usleep(4);
	}
	fout.close(); 	
}
