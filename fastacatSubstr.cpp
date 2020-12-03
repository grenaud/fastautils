/*
 * fasta2oneLine
 * Date: Feb-25-2013 
 * Author : Gabriel Renaud gabriel.reno [at sign here ] gmail.com
 *
 */

#include <iostream>
#include <fstream>

#include "FastQParser.h"
#include "libgab.h"

using namespace std;

int main (int argc, char *argv[]) {
  
    map<string,unsigned int> ids2index;
    vector<string> idsVec;
    vector<string> seqVec;

    for(int ar=1;ar<argc;ar++){
	FastQParser fqp (argv[ar],true );
	cerr<<"reading file "<<argv[ar]<<endl;
	vector<string> ids;
	vector<string> seqs;


    
	while(fqp.hasData()){
	    FastQObj * test	=fqp.getData();

	    ids.push_back(*(test->getID()) );
	    seqs.push_back(*(test->getSeq()));

	}

	if(ar==1){
	    for(unsigned int i=0;i<ids.size();i++){
		cerr<<"Found id "<<ids[i]<<endl;
		ids2index[ ids[i].substr(0,7) ] = i;
		idsVec.push_back( ids[i].substr(0,7) );
		seqVec.push_back( seqs[i] );
	    }
	    

	}else{
	    
	    for(unsigned int i=0;i<ids.size();i++){
		//cout<<"Found id "<<ids[i]<<endl;
		if(ids2index.find( ids[i].substr(0,7) )  == ids2index.end( ) ){
		    cerr<<"ERROR cannot reconcile ID order for file "<< argv[ar] <<" cannot assign id "<<ids[i].substr(0,7)<<endl;
		    return 1;
		}
		
		seqVec[	ids2index[ ids[i].substr(0,7) ] ]+= seqs[i];
	    }

	}




    }


    for(unsigned int i=0;i<idsVec.size();i++){
	cout<<idsVec[i]<<"\n"<<seqVec[i]<<endl;
    }
    
    return 0;
}

