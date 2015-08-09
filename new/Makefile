INC_DIR := ./
SRC_DIR := ./
CXX := g++
LIBS := -lpthread
CXXFLAGS := -std=c++11 -g  -Wno-strict-aliasing $(addprefix -I, $(INC_DIR)) $(LIBS)
OBJS := $(wildcard *.cpp)
EXE := main
RM := rm -rf
$(EXE) : $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)
.PHONY : rebuild clean
rebuild: clean $(EXE)
clean:
	$(RM) $(EXE)
