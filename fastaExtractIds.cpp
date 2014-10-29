/*
 * fasta2oneLine
 * Date: Feb-25-2013 
 * Author : Gabriel Renaud gabriel.reno [at sign here ] gmail.com
 *
 */

#include <iostream>
#include <fstream>
#include <set>

#include "FastQParser.h"
#include "utils.h"

using namespace std;

int main (int argc, char *argv[]) {
    bool notInList=false;

    string usage=string(""+string(argv[0])+" (options) [ID file] [fasta file] "+
			"\nThis program retrieves all the fasta records in [fasta file]\n"+
			"in the file [ID file]. This file has the following format:\n"+
			"\t>id1\n"+
			"\t>id2\n"+
			"\t...\n"+
			"Options:\n"+
			"\t"+"-v\t:  (Default: "+booleanAsString(notInList)+")\n"+
			"\n");

    if(argc == 1 ||
       argc < 3  ||
       (argc == 2 && (string(argv[0]) == "-h" || string(argv[0]) == "--help") )
       ){
	cerr << "Usage "<<usage<<endl;
	return 1;       
    }

    for(int i=1;i<(argc-2);i++){ 

	
        if(string(argv[i]) == "-v"){
	    notInList = true;
            continue;
	}

    }

    
    ifstream myFile;
    string filename = string(argv[argc-2]);
    string line;
    set<string> idsToExtract;
    myFile.open(filename.c_str(), ios::in);
    if (myFile.good()){
	while ( getline (myFile,line)){
	    idsToExtract.insert(line);
	}
	 	
	myFile.close();

    }else{
       cerr << "Unable to open file "<<filename<<endl;
       return 1;
    }



    FastQParser fqp (argv[argc-1],true );

    while(fqp.hasData()){
    	FastQObj * test	=fqp.getData();
	//cout<<*(test)<<endl;
	if(notInList){
	    if( !( idsToExtract.find( *(test->getID()) ) != idsToExtract.end() ))
		cout<<*(test->getID())<<endl<<*(test->getSeq())<<endl;
	}else{
	    if( idsToExtract.find( *(test->getID()) ) != idsToExtract.end() )
		cout<<*(test->getID())<<endl<<*(test->getSeq())<<endl;
	}
    	// cout<<*(test->getQual())<<endl;
    }
    return 0;
}

