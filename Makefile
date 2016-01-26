TARGET1 = antalg 
TARGET2 = gridantalg
all:$(TARGET1) $(TARGET2)
$(TARGET1):
	g++ main.cpp Aoc.cpp Ant.cpp Para.cpp MMAnt.cpp MMAoc.cpp -o antalg
$(TARGET2):
	g++ gridmain.cpp GridAnt.cpp GridAoc.cpp Para.cpp -o gridantalg

clean:
	rm $(TARGET1) $(TARGET2)