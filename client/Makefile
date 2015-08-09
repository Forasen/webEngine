INC_DIR := ./
CXX := g++
CXXFLAGS := -std=c++11 -g -Wno-strict-aliasing $(addprefix -I, $(INC_DIR)) -ljson
OBJS := $(wildcard *.cpp)
EXE := client
RM := rm -rf
$(EXE) : $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)
.PHONY : rebuild clean
rebuild: clean $(EXE)
clean:
	$(RM) $(EXE)
