CXX = g++
CXXFLAGS = -g
LDFLAGS_CXX =`pkg-config opencv openssl gtk+-2.0 --cflags --libs`
SUBDIRS=pinsketch
BIN=genSS recSS

#显式指定clean为伪目标，防止在当前目录下存在clean文件是无法执行清理工作
.PHONY:default all clean $(SUBDIRS) del
default:all

all: $(BIN) $(SUBDIRS) del

#prep:
#	if [ -d bin ]; then echo '' > /dev/null; else mkdir bin; fi
#	if [ -d tmp ]; then echo '' > /dev/null; else mkdir tmp; fi

#func.o: func.cpp func.h
#	$(CXX) $(CXXFLAGS) -c $< -o tmp/func.o $(LDFLAGS_CXX)
#genSS.o: genSS.cpp func.h
#	$(CXX) $(CXXFLAGS)  -c $< -o tmp/genSS.o $(LDFLAGS_CXX)
#genSS: func.o genSS.o
#	$(CXX) $(CXXFLAGS)  tmp/func.o tmp/genSS.o -o $@ $(LDFLAGS_CXX)
#recSS.o: recSS.cpp func.h
#	$(CXX) $(CXXFLAGS)  -c $< -o tmp/recSS.o $(LDFLAGS_CXX)
#recSS: func.o recSS.o
#	$(CXX) $(CXXFLAGS)  tmp/func.o tmp/recSS.o -o $@ $(LDFLAGS_CXX)

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS_CXX)
genSS:func.o genSS.o 
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS_CXX)
recSS:func.o recSS.o 
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS_CXX)
$(SUBDIRS):
	$(MAKE) -C $@ all
	
del:
	rm *.o
clean:
	rm -rf  *.o
	$(MAKE) -C $(SUBDIRS) clean
