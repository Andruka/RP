#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <sstream>
#include <sys/wait.h>

using namespace std;

int main(){
    pid_t p[10];
    pid_t result;
    ifstream conf("conf.xml");
    ofstream file_out;
    ifstream file_in;
    string buf;
    string in_name;
    string out_name;
    string word;
    int status;
    int max;
    int quantity;
    int counter;
    int start,end;
    bool flag=true;
    char text[1000];
    string name;
    ostringstream os;
    conf>>buf;
    if(buf!="<data>"){
	cout<<"Ошибка чтения!"<<endl;
	return(1);
    	}
    while(!conf.eof()){
    	conf>>buf;
    	if(buf=="<in_file>"){
    	    conf>>buf;
	    in_name=buf;
    	    }
    	if(buf=="<out_file>"){
    	    conf>>buf;
	    out_name=buf;
    	    }
    	if(buf=="<num_of_proc>"){
    	    conf>>buf;
	    quantity=atoi(buf.c_str());
    	    }
    	if(buf=="<max_size>"){
    	    conf>>buf;
	    max=atoi(buf.c_str());
    	    }
    	if(buf=="</data>")break;
	}
    srand(time(NULL));
    for(int i=1;i-1<quantity;++i){
	os<<i;
	name=in_name+os.str()+".txt";
	os.str("");
	file_out.open(name.c_str());
	for(int q=0;q<1000;++q){
	    text[q]=31+rand()%97;
	    }
	file_out<<text;
	file_out.close();
	}
    for(int i=1;i-1<quantity;++i){
	switch(p[i-1]=fork()){
	    case 0:
		start=clock();
		os<<i;
		name=in_name+os.str()+".txt";
		file_in.open(name.c_str());
		name=out_name+os.str()+".txt";
		os.str("");
		file_out.open(name.c_str());
		while(1){
		    file_in>>word;
		    if(file_in.eof())break;
		    ++counter;
		    }
	        end=clock();
		file_out<<"ID процесса: "<<getpid()<<endl<<"Количество слов: "<<counter<<endl<<"Время работы процесса: "<<end-start;
		counter=0;
		file_in.close();
		file_out.close();
		exit(0);
	    case -1:cout<<"Ошибка при создании процесса "<<i<<endl;
	    	return 1;
	    }
	}
    while(flag){
	flag=false;
	for(int i=0;i<quantity;++i){
	    result = waitpid(p[i], &status, WNOHANG);
	    if(result>0)cout<<"процесс "<<i+1<<" завершён"<<endl;
	    else if(result==0)flag=true;
	    }
    	}    
    }


