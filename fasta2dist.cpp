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

using namespace std;

int main (int argc, char *argv[]) {
    vector< vector<int> > matTot;
    vector< vector<int> > matMut;

    map<string,unsigned int> ids2index;
    vector<string> idsVec;
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
		//cout<<i<<endl;
		cerr<<"Found id "<<ids[i]<<endl;
		ids2index[ ids[i] ] = i;
		idsVec.push_back( ids[i] );
		//cout<<seqs[i]<<endl;
	    }
	    
	    for(unsigned int i=0;i<ids.size();i++){
		vector<int> tempzeromat  (ids.size(),0);
		matTot.push_back(tempzeromat);
		matMut.push_back(tempzeromat);
	    }

	}else{
	    
	    for(unsigned int i=0;i<ids.size();i++){
		//cout<<"Found id "<<ids[i]<<endl;
		if(ids2index.find( ids[i] )  == ids2index.end( ) ){
		    cerr<<"ERROR cannot reconcile ID order for file "<< argv[ar] <<endl;
		    return 1;
		}
	    }

	}

	for(unsigned int i=0;i<ids.size();i++){
	    for(unsigned int j=i+1;j<ids.size();j++){
		unsigned int i2 = ids2index[ ids[i] ];
		unsigned int j2 = ids2index[ ids[j] ];

		//cerr<<"Found id "<<ids[i]<<"-"<<ids[j]<<endl;
		for(unsigned int k=0;k<seqs[i].size();k++){
		    if(isResolvedDNA(seqs[i][k]) &&
		       isResolvedDNA(seqs[j][k]) ){
			matTot[i2][j2]++;
			if(seqs[i][k] != seqs[j][k]){
			    matMut[i2][j2]++;
			}
		    }
		}
	    }
	}



    }


    for(unsigned int i=0;i<idsVec.size();i++){
	for(unsigned int j=i+1;j<idsVec.size();j++){
	    unsigned int i2 = ids2index[ idsVec[i] ];
	    unsigned int j2 = ids2index[ idsVec[j] ];
	    cout<<idsVec[i]<<"\t"<<idsVec[j]<<"\t"<<matMut[i2][j2]<<"\t"<<matTot[i2][j2]<<"\t"<<(double(matMut[i2][j2])/double(matTot[i2][j2]))<<endl;
	}
    }    
    
    return 0;
}

