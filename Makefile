#
# Makefile for Combatant
#

CCC	= g++ -std=c++11 -pedantic -Wall -Wextra

all: Combatant.o Team.o Market.o Mechanics.o storage.o Demo3

Combatant.o: Combatant.cc Combatant.h
	$(CCC) -c Combatant.cc

Team.o: Team.cc Team.h Combatant.o
	$(CCC) -c Team.cc Combatant.o

Market.o: Market.cc Market.h Team.o Combatant.o
	$(CCC) -c Market.cc Team.o Combatant.o

Mechanics.o: Mechanics.cc Mechanics.h Team.o Market.o Combatant.o storage.o
	$(CCC) -c Mechanics.cc Team.o Market.o Combatant.o storage.o

storage.o: storage.cc storage.h storage.tpp
	$(CCC) -c storage.cc storage.tpp

storage_test: Test_main.cc storage.o
	$(CCC) -o Save_test Test_main.cc storage.o

Demo: Demo.cc Market.o Team.o Combatant.o
	$(CCC) -o demo_combatant Demo.cc Market.o Team.o Combatant.o

Demo2: Demo_v2.cc Market.o Team.o Combatant.o Mechanics.o
	$(CCC) -o demo_mechanics Demo_v2.cc Market.o Team.o Combatant.o Mechanics.o

Demo3: Demo_v3.cc Market.o Team.o Combatant.o Mechanics.o
	$(CCC) -o demo_mechanics Demo_v3.cc Market.o Team.o Combatant.o Mechanics.o storage.o

clean:
	@ \rm -rf *.o *.gch core

zap: clean
	@ \rm -f Combatant.o  *~
