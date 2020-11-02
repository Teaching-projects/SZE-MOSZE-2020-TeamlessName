OBJS = Hero.o JSON.o main.o Monster.o
CFLAGS = -Wall -Werror -std=c++17
CC = g++-10

add: $(OBJS)
	$(CC) $(CFLAGS) -o add $(OBJS)

Hero.o: Hero.cpp Hero.h JSON.h Exceptions.h 
	$(CC) $(CFLAGS) -c Hero.cpp

JSON.o: JSON.cpp JSON.h Exceptions.h
	$(CC) $(CFLAGS) -c JSON.cpp
	
Monster.o: Monster.cpp Monster.h Exceptions.h JSON.h
	$(CC) $(CFLAGS) -c Monster.cpp

main.o: main.cpp JSON.h Monster.h Exceptions.h
	$(CC) $(CFLAGS) -c main.cpp

install-valgrind-and-cppcheck:
	sudo apt-get install -y valgrind cppcheck

memoryleak-check:
	valgrind --leak-check=full --error-exitcode=1 ./a.out units/scenario1.json

upgrade-gcc:
	sudo apt --only-upgrade install g++-10 gcc-10

build: $(OBJS)
	$(CC) $(CFLAGS) -o a.out *.cpp
	
static-code-analysis:
	cppcheck *.cpp --enable=warning --error-exitcode=1

static-code-analysis-report:
	cppcheck *.cpp --enable=warning,style,performance --output-file=checkreport.txt

io-diff-tests:
	diff ./units/output1.txt Genoutput1.txt && diff ./units/output2.txt Genoutput2.txt

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