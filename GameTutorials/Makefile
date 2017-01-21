CXX=g++ # clang++ is also a good one
LIBS=
OPT=-O3
CXXFLAGS=-I. -std=c++11 -Wall $(OPT)
DEPS=AI.h Board.h MainGame.h
OBJ=AI.o Board.o MainGame.o main.o

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

tictactoe: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean force strip
clean:
	rm -f *.o tictactoe

force: clean tictactoe

strip:
	strip -s tictactoe

