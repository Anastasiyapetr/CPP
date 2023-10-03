FILES 	 = *.cpp
FLAGS 	 = gcc -Wall -Werror -Wextra
DOPFLAGS = -lm -lstdc++ -std=c++17
TESTFLAGS= -lgtest -lgmock -pthread
VALGFULL = --leak-check=full
VALGORIG = --track-origins=yes
GCOV_FLAG = --coverage
SOURCE = common_func.cpp matrix_oop.cpp
TEST = test.cpp

all: clean matrix_oop.a test

matrix_oop.a:
	$(FLAGS) -c $(SOURCE) $(DOPFLAGS)
	ar -rcs libmatrix_oop.a *.o
	rm -rf *.o

clean:
	rm -f *.a *.o *.so *.out *.info *.gcno *.gcda
	rm -rf report
	rm -rf *.gch

test: clean matrix_oop.a
	$(FLAGS) -c $(TEST) $(DOPFLAGS)
	$(FLAGS) *.o -L ../MATRIX_LIB -lmatrix_oop $(DOPFLAGS) $(TESTFLAGS)
	rm -rf *.o
	./a.out

leak:
	valgrind $(VALGFULL) $(VALGORIG) -s ./a.out

gcov_report: clean 
	$(FLAGS) $(GCOV_FLAG) *.cpp $(DOPFLAGS) $(TESTFLAGS) -o test.out
	./test.out > /dev/null
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

linter:
	cp ../materials/linters/.clang-format ../src && clang-format -n *.cpp *.h
	rm -rf .clang-format

lintery:
	clang-format -i -style=google *.cpp *.h
