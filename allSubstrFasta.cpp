/*
 * arrayDesign 
 * Date: Apr-17-2013 
 * Author : Gabriel Renaud gabriel.reno [at sign here ] gmail.com (based on http://plindenbaum.blogspot.de/2011/08/memory-mapping-human-genome-with-mmap.html)
 *
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <stdint.h>
#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <cerrno>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <zlib.h>
#include "FastQParser.h"
#include "FastQObj.h"

#include "utils.h"

using namespace std;




int main (int argc, char *argv[]) {
    unsigned int lengthTag=35;
    int64_t tiling=1;
    bool isFasta   =true;

    const string usage = "  "+string(argv[0])+" (options) <path to fasta chromosome file> \n\n"+
	"This program list the subsequences for the fasta file\n"+
	//	"The fasta file has to have been fasta index using faidx\n"+
	"Options:\n"+
	"\t"+"--size"+"\t"+"Size of the probes (default: "+stringify(lengthTag)+")\n"+
	"\t"+"--tile"+"\t"+"Size of the tiling (default: "+stringify(tiling)+")\n"+
	"\t\tchr[tab]pos[tab]reference allele[tab]alternative allele\n\n"+
	"\t\tThey must contain a single chromosome and be sorted on the coordinate\n"+
	"\n";

   
    if( (argc== 1) ||
	(argc== 2 && string(argv[1]) == "-h") ||
	(argc== 2 && string(argv[1]) == "-help") ||
	(argc== 2 && string(argv[1]) == "--help") ){
	cerr<<"Usage:"<<usage<<endl;
	return 1;
    }

    
    for(int i=1;i<(argc-2);i++){


        if(string(argv[i]) == "--size" ){
            lengthTag =destringify<int>(argv[i+1]);
	    i++;
            continue;
        }

        if(string(argv[i]) == "--tile" ){
            tiling =destringify<int>(argv[i+1]);
	    i++;
            continue;
        }


    }


    FastQParser fqp  (argv[argc-1],isFasta);

    while(fqp.hasData()){

	// cout<<"l1"<<endl;
    	FastQObj * test	=fqp.getData();
	string * strtostore=test->getSeq();
	string chr = (*test->getID());
	vector<string> allto = allTokens(chr,' ');
	chr = allto[0].substr(1);
	for(unsigned int i=0;i<=(strtostore->size()-lengthTag); i++){
	    //cout<<<<endl;
	    string  substringStore =  strtostore->substr(i,lengthTag);
	    cout<<substringStore<<endl;
	}

    }


    //cerr<<"finished succesfully"<<endl;
    return 0;
}

