TARGET := test
SOURCES := ./test_slice.cpp
INCLUDES := ../../bases
PACKAGE_FILE_NAMES := basetype\
					  shape\
					  stride\
					  slice
PACKAGES := ../../bases/basetype.cpp\
			../../bases/shape.cpp\
			../../bases/stride.cpp\
			../../bases/slice.cpp
OBJS := basetype.o\
		shape.o\
		stride.o\
		slice.o


$(TARGET).exe: $(OBJS)
	g++ $(SOURCES) $(OBJS) -I$(INCLUDES) -std=c++11 -o $(TARGET).exe

$(OBJS): $(PACKAGES)
	for file_name in $(PACKAGE_FILE_NAMES); do \
		g++ -c $(INCLUDES)/$$file_name.cpp -std=c++11 -o $$file_name.o; \
	done


clean:
	$(RM) -rf $(OBJS) $(TARGET).exe


	