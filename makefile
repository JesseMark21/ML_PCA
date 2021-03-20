CC = g++

driver: driver.o
	$(CC) driver.o -o driver -std=c++11

driver.o: driver.cpp
	$(CC) -c driver.cpp -std=c++11


clean:
	@rm -f *.o
	@rm driver
