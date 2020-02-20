GCC=g++
SOURCE=sol.cpp checker.cpp

build: sol.cpp
	$(GCC) -std=c++11 -o sol sol.cpp
	$(GCC) -std=c++11 -o checker checker.cpp
