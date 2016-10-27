/*
 * fasta2columns
 * Date: Feb-25-2013 
 * Author : Gabriel Renaud gabriel.reno [at sign here ] gmail.com
 *
 */

#include <iostream>
#include <fstream>

#include "FastQParser.h"
#include "utils.h"

using namespace std;

int main (int argc, char *argv[]) {

    bool printIndex=false;
    bool printIndexRef=false;
    bool printOnlyDiff=false;
    int index1=-1;
    int index2=-1;
    int indexR=-1;
    
    if(argc==1){
	cerr<<"Usage "<<argv[0]<<" <options> [fasta file]"<<endl;
	cerr<<"Options:"<<endl;
	cerr<<"\t-ind\t\t\t\tPrint 1-based index "<<endl;
	cerr<<"\t-inds [seq X]\t\t\t\tPrint 1-based index using sequence X as the reference "<<endl;
	cerr<<"\t-diff [seq X] [seq Y]\t\tPrint only lines that differ between sequence X and Y (1-based)"<<endl;	
	return 1;
    }

    
    for(int i=1;i<(argc-1);i++){ //all but the last arg

	if(string(argv[i]) == "-inds" ){
	    printIndexRef = true;
	    indexR        = destringify<int>(string(argv[i+1]));
	    i++;
	    continue;
	}

	if(string(argv[i]) == "-inds" ){
	    printIndex=true;
	    continue;
	}

	if(string(argv[i]) == "-diff" ){
	    printOnlyDiff=true;
	    index1 = destringify<int>(string(argv[i+1]));
	    index2 = destringify<int>(string(argv[i+2]));
	    i+=2;
	    continue;
	}
       
	cerr<<"Unknown option "<<argv[i] <<" exiting"<<endl;
	return 1;
    }

    if(printIndex && printIndexRef){
	cerr<<"Cannot use both -ind and -inds"<<endl;
	return 1;
    }

    FastQParser fqp (argv[argc-1],true );
    vector<string> toprint;
    while(fqp.hasData()){
    	FastQObj * test	=fqp.getData();
	//cout<<*(test)<<endl;
        //cout<<*(test->getID())<<"\t"<<*(test->getSeq())<<endl;
    	// cout<<*(test->getQual())<<endl;
	toprint.push_back( *(test->getSeq()));
    }
    unsigned int length = toprint[0].size();


    // cout<<index1<<"\t"<<index2<<endl;

    
    for(unsigned int i=1;i<toprint.size();i++){
	if(toprint[i].size() != length){
	    cerr<<"Error all sequences must have the same length"<<endl;
	    return 1;
	}
    }

    unsigned int indexUsingRef=0;

    if(!printOnlyDiff){

	if(printIndexRef){
	    if( indexR<1 ){
		cerr<<"Wrong -inds option, reference index greater than 1"<<endl;
		return 1;
	    }

	    if( (indexR>int(toprint.size())) ){
		cerr<<"Wrong -inds option, it must be a sequence index lesser than the number of sequences"<<endl;
		return 1;
	    }
	}

	for(unsigned int l=0;l<length;l++){	
	    if(printIndex){
		cout<<(l+1)<<"\t";
	    }

	    if(printIndexRef){
		if(toprint[indexR-1][l] != '-')//not gap
		    indexUsingRef++;
		cout<<(indexUsingRef)<<"\t";
	    }
	    
	    for(unsigned int i=0;i<toprint.size();i++){
		cout<<toprint[i][l];
	    }
	    cout<<endl;
	}
    }else{
	if(index1<1 || index2<1){
	    cerr<<"Wrong diff option, it must be a sequence index greater than 1"<<endl;
	    return 1;
	}

	if(index1 == index2){
	    cerr<<"Wrong diff option, both indices must differ"<<endl;
	    return 1;
	}

	if( (index1>int(toprint.size())) || (index2>int(toprint.size()))){
	    cerr<<"Wrong diff option, it must be a sequence index lesser than the number of sequences"<<endl;
	    return 1;
	}

	if(printIndexRef){
	    if( indexR<1 ){
		cerr<<"Wrong -inds option, reference index greater than 1"<<endl;
		return 1;
	    }

	    if( (indexR>int(toprint.size())) ){
		cerr<<"Wrong -inds option, it must be a sequence index lesser than the number of sequences"<<endl;
		return 1;
	    }
	}

	for(unsigned int l=0;l<length;l++){	
	    if(printIndexRef){
		if(toprint[indexR-1][l] != '-')//not gap
		    indexUsingRef++;
	    }

	    if(toprint[index1-1][l]  == toprint[index2-1][l]  )
		continue;

	    if(printIndexRef){
		cout<<(indexUsingRef)<<"\t";
	    }

	    if(printIndex){
		cout<<(l+1)<<"\t";
	    }
	    

	    for(unsigned int i=0;i<toprint.size();i++){
		cout<<toprint[i][l];
	    }
	    cout<<endl;
	}
    }
    return 0;
}

