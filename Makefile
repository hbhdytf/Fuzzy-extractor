CXX = g++
CXXFLAGS = -g
LDFLAGS_CXX =`pkg-config opencv openssl gtk+-2.0 --cflags --libs`
SUBDIRS=pinsketch
BIN=genSS recSS
SOFLAGS_CXX = -L./pinsketch -lpinsketch -lntl -Wl,-rpath,./pinsketch/

#显式指定clean为伪目标，防止在当前目录下存在clean文件是无法执行清理工作
.PHONY:default all clean $(SUBDIRS) del
default:all

all: $(SUBDIRS) $(BIN)  del

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
#$<依赖列表第一项 #$^依赖列表的所有项 func.o genSS #$@表示目标项 recSS
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS_CXX) 
genSS:func.o genSS.o 
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS_CXX) 
recSS:func.o recSS.o 
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS_CXX) $(SOFLAGS_CXX)
$(SUBDIRS):
	$(MAKE) -C $@ all
	
del:
	@rm *.o  #命令前加@，可以不显示该调用
clean:
	rm -rf  *.o
	$(MAKE) -C $(SUBDIRS) clean
