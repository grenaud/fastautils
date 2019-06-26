CXX      = g++   
#LIBGAB   = 
LIBGAB= $(realpath libgab/)

CXXFLAGS = -Wall -lm -O3 -lz -I${LIBGAB}/ -I${LIBGAB}/gzstream/  -c
LDFLAGS  = -lz


all:  allSubstrFasta fasta2columns fasta2dist fasta2oneLine fastacat fastacatSubstr fastaExtractIds fastalinebreak fastaDiffs2bed fastaUnresolvedBases fastaUnresolvedBases2Bed

allSubstrFasta.o:	allSubstrFasta.cpp
	${CXX} ${CXXFLAGS} allSubstrFasta.cpp

fasta2columns.o:	fasta2columns.cpp
	${CXX} ${CXXFLAGS} fasta2columns.cpp

fasta2dist.o:	fasta2dist.cpp
	${CXX} ${CXXFLAGS} fasta2dist.cpp

fasta2oneLine.o:	fasta2oneLine.cpp
	${CXX} ${CXXFLAGS} fasta2oneLine.cpp

fastacat.o:	fastacat.cpp
	${CXX} ${CXXFLAGS} fastacat.cpp

fastacatSubstr.o:	fastacatSubstr.cpp
	${CXX} ${CXXFLAGS} fastacatSubstr.cpp

fastaExtractIds.o:	fastaExtractIds.cpp
	${CXX} ${CXXFLAGS} fastaExtractIds.cpp

fastalinebreak.o:	fastalinebreak.cpp
	${CXX} ${CXXFLAGS} fastalinebreak.cpp

fastaDiffs2bed.o:	fastaDiffs2bed.cpp
	${CXX} ${CXXFLAGS} fastaDiffs2bed.cpp

fastaUnresolvedBases.o:	fastaUnresolvedBases.cpp
	${CXX} ${CXXFLAGS} fastaUnresolvedBases.cpp

fastaUnresolvedBases2Bed.o: fastaUnresolvedBases2Bed.cpp
	${CXX} ${CXXFLAGS} fastaUnresolvedBases2Bed.cpp

allSubstrFasta:	allSubstrFasta.o ${LIBGAB}/utils.o  ${LIBGAB}/FastQParser.o ${LIBGAB}/gzstream/libgzstream.a ${LIBGAB}/FastQObj.o
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fasta2columns:	fasta2columns.o ${LIBGAB}/utils.o  ${LIBGAB}/FastQParser.o ${LIBGAB}/gzstream/libgzstream.a ${LIBGAB}/FastQObj.o
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fasta2dist:	fasta2dist.o ${LIBGAB}/utils.o  ${LIBGAB}/FastQParser.o ${LIBGAB}/gzstream/libgzstream.a ${LIBGAB}/FastQObj.o
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fasta2oneLine:	fasta2oneLine.o ${LIBGAB}/utils.o  ${LIBGAB}/FastQParser.o ${LIBGAB}/gzstream/libgzstream.a ${LIBGAB}/FastQObj.o
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastacat:	fastacat.o ${LIBGAB}/utils.o  ${LIBGAB}/FastQParser.o ${LIBGAB}/gzstream/libgzstream.a ${LIBGAB}/FastQObj.o
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastacatSubstr:	fastacatSubstr.o ${LIBGAB}/utils.o  ${LIBGAB}/FastQParser.o ${LIBGAB}/gzstream/libgzstream.a ${LIBGAB}/FastQObj.o
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastaExtractIds:	fastaExtractIds.o ${LIBGAB}/utils.o  ${LIBGAB}/FastQParser.o ${LIBGAB}/gzstream/libgzstream.a ${LIBGAB}/FastQObj.o
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastalinebreak:	fastalinebreak.o ${LIBGAB}/utils.o  ${LIBGAB}/FastQParser.o ${LIBGAB}/gzstream/libgzstream.a ${LIBGAB}/FastQObj.o
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastaDiffs2bed:	fastaDiffs2bed.o ${LIBGAB}/utils.o  ${LIBGAB}/FastQParser.o ${LIBGAB}/gzstream/libgzstream.a ${LIBGAB}/FastQObj.o
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastaUnresolvedBases: fastaUnresolvedBases.o ${LIBGAB}/utils.o  ${LIBGAB}/FastQParser.o ${LIBGAB}/gzstream/libgzstream.a ${LIBGAB}/FastQObj.o
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastaUnresolvedBases2Bed: fastaUnresolvedBases2Bed.o ${LIBGAB}/utils.o  ${LIBGAB}/FastQParser.o ${LIBGAB}/gzstream/libgzstream.a ${LIBGAB}/FastQObj.o
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 


clean :
	rm -f *.o allSubstrFasta fasta2columns fasta2dist fasta2oneLine fastacat fastacatSubstr fastaExtractIds fastalinebreak fastaDiffs2bed fastaUnresolvedBases fastaUnresolvedBases2Bed

