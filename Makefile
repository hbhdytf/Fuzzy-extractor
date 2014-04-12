CXX = g++
CXXFLAGS = -g
LDFLAGS_CXX =`pkg-config opencv openssl gtk+-2.0 --cflags --libs`
SUBDIRS=pinsketch

#
.PHONY:default all clean $(SUBDIRS) 
default:all
all:prep genSS $(SUBDIRS) 

prep:
	if [ -d bin ]; then echo '' > /dev/null; else mkdir bin; fi
	if [ -d tmp ]; then echo '' > /dev/null; else mkdir tmp; fi

func.o: func.cpp func.h
	$(CXX) $(CXXFLAGS) -c $< -o tmp/func.o $(LDFLAGS_CXX)
genSS.o: genSS.cpp func.h
	$(CXX) $(CXXFLAGS)  -c $< -o tmp/main.o $(LDFLAGS_CXX)
genSS:prep func.o genSS.o
	$(CXX) $(CXXFLAGS)  tmp/*.o -o $@ $(LDFLAGS_CXX)
$(SUBDIRS):
	$(MAKE) -C $@ all
clean:
	rm -rf tmp/*
	$(MAKE) -C $(SUBDIRS) clean