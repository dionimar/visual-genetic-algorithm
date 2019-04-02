main: main.cpp
	g++ -g -O3 -std=gnu++11 main.cpp point.cpp path.cpp adn.cpp population.cpp  -o main_opt.out -lGL -lGLU -lglut
