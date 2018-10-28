#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;
int det(int dim,int **aa)
{
    int d=0;
    int **bb;
    bb=new int * [dim-1];
    for(int i=0;i<dim-1;++i){
	bb[i]=new int[dim-1];
	}
    if(dim==2){
	d=aa[0][0]*aa[1][1]-aa[0][1]*aa[1][0];
 	}
    else {
	d=0;
	int xx,yy;
	for(int i=0;i<dim;++i){
	    xx=yy=0;
	    for(int x=1;x<dim;++x){
		for(int y=0;y<dim;++y){
		    if(y==i)continue;
		    bb[xx][yy]=aa[x][y];
		    ++yy;
		    }
		++xx;
		yy=0;
		}
	    d=d+pow(-1,i)*det(dim-1,bb)*aa[0][i];
	    xx=yy=0;
	    }
    	}
    return d;
    }

int main(){
    ofstream fifo_out("/tmp/det");
    ifstream fifo_in("/tmp/name");
    ifstream matrix;
    int dim;
    int **aa;
    int count;
    int determ;;
    string name;
    fifo_in>>count;
    for(int i=0;i<count;++i){
	fifo_in>>name;
	matrix.open(name.c_str());
	matrix>>dim;
	aa=new int * [dim];
    	for(int j=0;j<dim;++j){
	    aa[j]=new int[dim];
	    }
	for(int j=0;j<dim;++j){
	    for(int q=0;q<dim;++q){
		matrix>>aa[j][q];
		}
	    }
	matrix.close();
	determ=det(dim,aa);
    	for(int j=0;j<dim;++j){
	    delete[] aa[j];
	    }
	delete[] aa;
	fifo_out<<determ<<endl;
	}
    }
