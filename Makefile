CXX = g++
CXXFLAGS = -g
#编译时的依赖环境，包括openssl opencv 和gtk+-2.0
#openssl-->>虹膜随机化时使用到，即产生最终KEY
#opencv-->>获取虹膜特征图像的数据时使用
#gtk+-2.0-->>在操作配置文件时使用到
LDFLAGS_CXX =`pkg-config opencv openssl gtk+-2.0 --cflags --libs`
SUBDIRS=pinsketch
BIN=genSS recSS genfinSS recfinSS
#指定动态库的链接路径和执行搜索路径为/pinsketch ，NTL为运算库 
SOFLAGS_CXX = -L/home/sandy/Fuzzy/pinsketch/ -lpinsketch -lntl -Wl,-rpath,/home/sandy/Fuzzy/pinsketch/

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
genfinSS:func.o genfinSS.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS_CXX)
recfinSS:func.o recfinSS.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS_CXX) $(SOFLAGS_CXX)
$(SUBDIRS):
	$(MAKE) -C $@ all
	
del:
	@rm *.o  #命令前加@，可以不显示该调用
clean:
	rm -rf  *.o
	$(MAKE) -C $(SUBDIRS) clean
