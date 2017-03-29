OBJECTS = main.o City.o
HEADERS = City.h
CS315PA1: $(OBJECTS)
	g++ -std=c++11 $^ -o CS315PA1
%.o: %.cpp $(HEADERS)
	g++ -std=c++11 -c $< -o $@
clean:
	rm -i *.o CS315PA1
