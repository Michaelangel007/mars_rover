all: mars

mars: mars_rover.cpp
	g++ $< -o $@

