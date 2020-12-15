CXX      = g++   
#LIBGAB   = 
LIBGAB= $(realpath libgab/)

CXXFLAGS = -Wall -lm -O3 -lz -I${LIBGAB}/ -I${LIBGAB}/gzstream/  -c
LDFLAGS  = -lz


all:  libgab/libgab.a bamtools/lib/libbamtools.so allSubstrFasta fasta2columns fasta2dist fasta2oneLine fastacat fastacatSubstr fastaExtractIds fastalinebreak fastaDiffs2bed fastaUnresolvedBases

libgab/libgab.h:
	rm -rf libgab/
	git clone --depth 1 --recursive https://github.com/grenaud/libgab.git

libgab/libgab.a: bamtools/lib/libbamtools.so  libgab/libgab.h
	make -C libgab

bamtools/src/api/BamAlignment.h:
	rm -rf bamtools/
	git clone  --recursive https://github.com/pezmaster31/bamtools.git && cd bamtools/ && git reset --hard d24d850de17134fe4e7984b26493c5c0a1844b35

bamtools/lib/libbamtools.so: bamtools/src/api/BamAlignment.h
	cd bamtools/ && mkdir -p build/  && cd build/ && if cmake ..; then echo ""; else if cmake3 ..; then echo ""; else echo "cmake failed, please install cmake v3"; fi  fi  && make && cd ../..


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

allSubstrFasta:	allSubstrFasta.o ${LIBGAB}/libgab.a   ${LIBGAB}/gzstream/libgzstream.a 
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fasta2columns:	fasta2columns.o ${LIBGAB}/libgab.a   ${LIBGAB}/gzstream/libgzstream.a 
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fasta2dist:	fasta2dist.o ${LIBGAB}/libgab.a   ${LIBGAB}/gzstream/libgzstream.a 
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fasta2oneLine:	fasta2oneLine.o ${LIBGAB}/libgab.a   ${LIBGAB}/gzstream/libgzstream.a 
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastacat:	fastacat.o ${LIBGAB}/libgab.a   ${LIBGAB}/gzstream/libgzstream.a 
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastacatSubstr:	fastacatSubstr.o ${LIBGAB}/libgab.a   ${LIBGAB}/gzstream/libgzstream.a 
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastaExtractIds:	fastaExtractIds.o ${LIBGAB}/libgab.a   ${LIBGAB}/gzstream/libgzstream.a 
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastalinebreak:	fastalinebreak.o ${LIBGAB}/libgab.a   ${LIBGAB}/gzstream/libgzstream.a 
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastaDiffs2bed:	fastaDiffs2bed.o ${LIBGAB}/libgab.a   ${LIBGAB}/gzstream/libgzstream.a 
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 

fastaUnresolvedBases: fastaUnresolvedBases.o ${LIBGAB}/libgab.a   ${LIBGAB}/gzstream/libgzstream.a 
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS) 



clean :
	rm -f *.o allSubstrFasta fasta2columns fasta2dist fasta2oneLine fastacat fastacatSubstr fastaExtractIds fastalinebreak fastaDiffs2bed fastaUnresolvedBases 

