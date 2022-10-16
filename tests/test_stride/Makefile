TARGET := test
SOURCES := ./test_stride.cpp
INCLUDES := ../../bases
PACKAGE_FILE_NAMES := basetype\
					  shape\
					  stride
PACKAGES := ../../bases/basetype.cpp\
			../../bases/shape.cpp\
			../../bases/stride.cpp
OBJS := basetype.o\
		shape.o\
		stride.o


$(TARGET).exe: $(OBJS)
	g++ $(SOURCES) $(OBJS) -I$(INCLUDES) -std=c++11 -o $(TARGET).exe

$(OBJS): $(PACKAGES)
	for file_name in $(PACKAGE_FILE_NAMES); do \
		g++ -c $(INCLUDES)/$$file_name.cpp -std=c++11 -o $$file_name.o; \
	done


clean:
	$(RM) -rf $(OBJS) $(TARGET).exe


	