OBJS = Hero.o JSON.o main.o Monster.o Map.o Game.o
CFLAGS = -Wall -Werror -std=gnu++17
CC = g++-10

add: $(OBJS)
	$(CC) $(CFLAGS) -o add $(OBJS)

Hero.o: Hero.cpp Hero.h Monster.h JSON.h Exceptions.h Damage.h
	$(CC) $(CFLAGS) -c Hero.cpp

JSON.o: JSON.cpp JSON.h Exceptions.h
	$(CC) $(CFLAGS) -c JSON.cpp

Monster.o: Monster.cpp Monster.h Exceptions.h JSON.h Damage.h
	$(CC) $(CFLAGS) -c Monster.cpp

main.o: main.cpp JSON.h Monster.h Exceptions.h Map.h Game.h Damage.h
	$(CC) $(CFLAGS) -c main.cpp

Map.o: Map.cpp Map.h
	$(CC) $(CFLAGS) -c Map.cpp

Game.o: Game.cpp Game.h Map.h Monster.h Hero.h
	$(CC) $(CFLAGS) -c  Game.cpp

install-valgrind-and-cppcheck:
	sudo apt-get install -y valgrind cppcheck

memoryleak-check:
	valgrind --leak-check=full --error-exitcode=1 ./a.out < userinput.txt

upgrade-gcc:
	sudo apt --only-upgrade install g++-10 gcc-10

build: $(OBJS)
	$(CC) $(CFLAGS) -o a.out $(OBJS)

static-code-analysis:
	cppcheck *.cpp --enable=warning --error-exitcode=1 --inline-suppr

static-code-analysis-report:
	cppcheck *.cpp --enable=warning,style,performance --output-file=checkreport.txt --inline-suppr

io-diff-tests:
	diff ./units/output1.txt Genoutput1.txt

run-test:
	bash -c "./test.sh"

unittest-build:
	cd test && cmake CMakeLists.txt && make

unittest-run:
	cd test &&./runTests

doxygen-documentation:
	doxygen doxconf

clean:
	rm -rf $(OBJS) a.out ./DOCS