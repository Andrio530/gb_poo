CXX = g++
CXXFLAGS = -std=c++17 -Wall
OBJS = main.o Sistema.o Process.o ProcessQueue.o ReadingProcess.o WritingProcess.o PrintingProcess.o ComputingProcess.o

all: TrabalhoGrauB

TrabalhoGrauB: $(OBJS)
	$(CXX) $(CXXFLAGS) -o TrabalhoGrauB $(OBJS)

clean:
	rm -f *.o TrabalhoGrauB
