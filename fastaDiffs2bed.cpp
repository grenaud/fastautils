#include <iostream>
#include <fstream>

#include "FastQParser.h"
#include "utils.h"

using namespace std;

int main (int argc, char *argv[]) {
    string filename1;
    string filename2;
    string usage=string(""+string(argv[0])+" (options) [fasta file1] [fasta file2] "+
			"\nThis program will print the location of the differences\n"+
			"for 2 fasta files of equal length\n"+
			"Options:\n"+
			//"\t"+"-v\t:  (Default: "+booleanAsString(notInList)+")\n"+
			"\n");

    if(argc==3){
	filename1=string(argv[1]);
	filename2=string(argv[2]);	
    }else{
	cerr<<usage<<endl;
	return 1;
    }

    

    string line1;
    string line2;
    string def;
    igzstream myFile1;
    igzstream myFile2;
    unsigned int pos=0;    
    myFile1.open(filename1.c_str(), ios::in);
    myFile2.open(filename2.c_str(), ios::in);

    if (myFile1.good() ){

	if (myFile2.good() ){

	    //def
	    getline (myFile1,line1);
	    getline (myFile2,line2);
	    def=line1.substr(1);
	    
	    if(line1 != line2){
		cerr<<"The defline is not equal between both files"<<endl;
	    }
	    
	    while ( getline (myFile1,line1)){
		if(getline (myFile2,line2)){
		    if(line1.size() != line2.size()){
			cerr << "Discrepancy between line lengths "<<line1<<"\t"<<line2<<endl;
			return 1;
		    }
		    
		    unsigned int i=0;
		    for(i=0;i<line1.size();i++){
			if(line1[i]!=line2[i]){
			    cout<<def<<"\t"<<(pos+i)<<"\t"<<(pos+i+1)<<endl;
			}
		    }
		    pos+=i;
		    
		}else{
		    cerr << "Discrepancy between amount of data "<<endl;
		    return 1;
		}
		   
	    }


	    myFile2.close();
	    
	}else{
	    cerr << "Unable to open file "<<filename2<<endl;
	    return 1;
	}
	myFile1.close();
    }else{
	cerr << "Unable to open file "<<filename1<<endl;
	return 1;
    }

    return 0;
}

