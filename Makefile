all: base64

base64: base64.o
	$(CXX) -std=gnu++14 -Wall -o base64 base64.o

base64.o:
	$(CXX) -std=gnu++14 -Wall -c base64.cpp


clean:
	rm -f base64 
