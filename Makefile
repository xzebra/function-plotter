default:
	g++ main.cpp plot.cpp -std=c++11
test:
	g++ main.cpp mathParser/mathParser.cpp -std=c++11
	./a.out