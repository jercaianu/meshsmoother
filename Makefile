all: main.cpp mesh.cpp mesh.hpp point.hpp polyline.hpp normal.hpp
	clang++ -std=c++11 point.hpp normal.hpp polyline.hpp mesh.hpp mesh.cpp main.cpp
