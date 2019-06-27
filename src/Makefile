CXX=g++
INC=-I=.
CXXFLAGS ?= -Wall -g -O0 --std=c++17 ${INC}
LIBS=


TARGET_EXEC=exbed

ALL=${TARGET_EXEC}

OBJS = euclidean.o


$(TARGET_EXEC): $(OBJS) main.cpp
	$(CXX) $(OBJS) main.cpp $(CXXFLAGS) -o $@ $(LIBS)

%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

unittests: unittests.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) unittests.cpp $(OBJS) -o $@ $(LIBS)


.PHONY: clean

clean:
	-rm *.o
	-rm exebd
	-rm unittests

