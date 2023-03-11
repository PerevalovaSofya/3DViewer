CFLAGS = -std=c++17 -Wall -Wextra -Werror 
CFLAGS1 = -std=c++17
GFLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS = -L. -lcheck -lgcov -lm

ifeq ($(shell lsb_release -si), Ubuntu)
LDFLAGS += -lsubunit 
endif


all: build

build: clean
	mkdir build
	cd build/; qmake ../3DViewer.pro
	make -C build/
	cd build/; rm -rf *.o *.cc *.cpp *.h Makefile

install: build
	mkdir $(HOME)/Desktop/3DViewer/
	cp -rf build/3DViewer.app $(HOME)/Desktop/3DViewer/

uninstall:
	rm -rf $(HOME)/Desktop/3DViewer/


tests: clean
	g++ --coverage model/model.cc test.cc -o test -lstdc++ -lgtest -lgtest_main
	./test
	rm -rf *.o 

gcov_report: 
	g++ --coverage model/model.cc test.cc -o test -lstdc++ -lgtest -lgtest_main
	./test
	lcov -t "test" --no-external -o test.info -c -d ./
	genhtml -o report test.info
	open ./report/index.html

check:
	cppcheck --language=c++ --suppress=missingIncludeSystem *.cc *.h

clean:
	rm -rf *.o *.a *.gcda *.gcno 3DViewer test 3DViewer.tar gcov_report build/ report/ test.info Dist/ *.out *.cfg
