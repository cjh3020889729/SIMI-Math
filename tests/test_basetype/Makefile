TARGET := test
SOURCES := ./test_basetype.cpp
INCLUDES := ../../bases
PACKAGES := ../../bases/basetype.cpp

$(TARGET).exe: packages.o
	g++ $(SOURCES) packages.o -I$(INCLUDES) -std=c++11 -o $(TARGET).exe

packages.o: $(PACKAGES)
	g++ -c $(PACKAGES) -std=c++11 -o packages.o

clean:
	$(RM) -rf ./packages.o ./main.o ./$(TARGET).exe


	