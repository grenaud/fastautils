/*
 * fasta2oneLine
 * Date: Feb-25-2013 
 * Author : Gabriel Renaud gabriel.reno [at sign here ] gmail.com
 *
 */

#include <iostream>
#include <fstream>

#include "FastQParser.h"
#include "utils.h"
#define LINESIZE 80

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
        cout<<*(test->getID())<<endl;
	unsigned int i=0;
	while(i<test->getSeq()->size()){
	    if( (test->getSeq()->size()-i) >= LINESIZE){
		cout<<test->getSeq()->substr(i,LINESIZE)<<endl;
		i+=LINESIZE;
	    }else{
		cout<<test->getSeq()->substr(i)<<endl;
		break;
	    }
	}
	    
	//"\t"<<*(test->getSeq())<<endl;
    	// cout<<*(test->getQual())<<endl;
    }
    return 0;
}

