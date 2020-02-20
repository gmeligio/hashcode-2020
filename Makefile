GCC=g++
SOURCE=sol.cpp checker.cpp sol_book.cpp

build: $(SOURCE)
	$(GCC) -std=c++11 -o sol sol.cpp
	$(GCC) -std=c++11 -o checker checker.cpp
	$(GCC) -std=c++11 -o sol2 sol_book.cpp
