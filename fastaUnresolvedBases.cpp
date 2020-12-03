/*
 * fastaUnresolvedBases
 * Date: Apr 19-2017 
 * Author : Gabriel Renaud gabriel.reno [at sign here ] gmail.com
 *
 */

#include <iostream>
#include <fstream>

#include "FastQParser.h"
#include "libgab.h"

using namespace std;

int main (int argc, char *argv[]) {
    string filename="/dev/stdin";
    if(argc==2){
	filename=string(argv[1]);
    }

    
    FastQParser fqp (filename.c_str(),true );

    while(fqp.hasData()){
    	FastQObj * test	=fqp.getData();
	//cout<<*(test)<<endl;
        cout<<*(test->getID())<<"\t";
	unsigned int i=0;
	unsigned int N=0;
	unsigned int T=0;
	
	for(i=0;i<test->getSeq()->size();i++){

	    if( toupper(test->getSeq()->at(i)) == '-' ){
		continue;
	    }
	    if( toupper(test->getSeq()->at(i)) == 'N' ){
		N++;
	    }
	    T++;

	}

	cout<<N<<"\t"<<T<<"\t"<<(double(N)/double(T))<<endl;
	//"\t"<<*(test->getSeq())<<endl;
    	// cout<<*(test->getQual())<<endl;
    }
    return 0;
}

