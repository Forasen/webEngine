INC_DIR := ./include/ /usr/include/
SRC_DIR := ./src/
CXX := g++
LIBS := -lpthread -L ../../../../jsoncpp-src-0.5.0/libs/linux-gcc-4.8 -ljson
LINK := -ljson
CXXFLAGS := -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) 
OBJS := $(wildcard *.cpp)
EXE := ./bin/main
RM := rm -rf
$(EXE) : $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) 
.PHONY : rebuild clean
rebuild: clean $(EXE)
clean:
	$(RM) $(EXE)
