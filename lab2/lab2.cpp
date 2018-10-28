#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

int main () {
    unlink("/tmp/name");
    unlink("/tmp/det");
    if((mkfifo("/tmp/det", 0777)) == -1)
    	{
    	cout<<"Unable to create FIFO name\n"<<endl;
    	_exit(0);
  	}
    if((mkfifo("/tmp/name", 0777)) == -1)
    	{
    	cout<<"Unable to create FIFO det\n"<<endl;
    	_exit(0);
  	}
    ifstream conf("conf.xml");
    ifstream init("init.txt");
    ofstream matrix;
    string buf;
    string in_name;
    string out_name;
    string name;
    ostringstream os;
    int count;
    int dim;
    int det;
    int chislo;    cout<<111<<endl;
    ifstream fifo_in("/tmp/det");
    cout<<111<<endl;
    ofstream fifo_out("/tmp/name");
    cout<<111<<endl;
    ofstream determ;
    const char space=32;
    conf>>buf;
    srand(time(0));
    if(buf!="<data>"){
    	cout<<"Ошибка чтения!"<<endl;
    	return(1);
    }
    while(!conf.eof()){
    	conf>>buf;
        if(buf=="<count>"){
    	    conf>>buf;
	    count=atoi(buf.c_str());
    	    }
    	if(buf=="<in_file>"){
    	    conf>>buf;
	    in_name=buf;
    	    }
    	if(buf=="<out_file>"){
    	    conf>>buf;
	    out_name=buf;
    	    }
    	if(buf=="</data>")break;
	}
    cout<<111<<endl;
    fifo_out<<count<<endl;
    cout<<111<<endl;
    for(int i=0;i<count;++i){
	init>>dim;
	os<<i+1;
	name=in_name+os.str()+".txt";
	cout<<name<<endl;
	matrix.open(name.c_str());
	matrix<<dim<<endl;
	for(int j=0;j<dim;++j){
		for(int r=0;r<dim;++r){
			matrix<<rand()%20;
			matrix<<space;
			}
		matrix<<endl;
		}
    	matrix.close();
	fifo_out<<name<<endl;
	name=out_name+os.str()+".txt";
	os.str("");
	fifo_in>>det;
	determ.open(name.c_str());
	determ<<det;
	determ.close();
	}
    }

