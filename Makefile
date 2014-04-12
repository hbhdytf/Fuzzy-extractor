CXX = g++
CXXFLAGS = -g
LDFLAGS_CXX =`pkg-config opencv openssl gtk+-2.0 --cflags --libs`
SUBDIRS=pinsketch

#
.PHONY:default all clean $(SUBDIRS) 
default:all
all:prep genSS recSS $(SUBDIRS) 

prep:
	if [ -d bin ]; then echo '' > /dev/null; else mkdir bin; fi
	if [ -d tmp ]; then echo '' > /dev/null; else mkdir tmp; fi

func.o: func.cpp func.h
	$(CXX) $(CXXFLAGS) -c $< -o tmp/func.o $(LDFLAGS_CXX)
genSS.o: genSS.cpp func.h
	$(CXX) $(CXXFLAGS)  -c $< -o tmp/genSS.o $(LDFLAGS_CXX)
genSS: func.o genSS.o
	$(CXX) $(CXXFLAGS)  tmp/func.o tmp/genSS.o -o $@ $(LDFLAGS_CXX)
recSS.o: recSS.cpp func.h
	$(CXX) $(CXXFLAGS)  -c $< -o tmp/recSS.o $(LDFLAGS_CXX)
recSS: func.o recSS.o
	$(CXX) $(CXXFLAGS)  tmp/func.o tmp/recSS.o -o $@ $(LDFLAGS_CXX)
$(SUBDIRS):
	$(MAKE) -C $@ all
clean:
	rm -rf tmp/*
	$(MAKE) -C $(SUBDIRS) clean