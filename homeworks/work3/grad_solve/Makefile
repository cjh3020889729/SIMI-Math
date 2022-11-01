TARGET := work_solve
LOG_FILE := gradient_logs.txt conjugate_logs.txt
SOURCES := ./solve.cpp
INCLUDES1 := ../../../bases
INCLUDES2 := ../../../algorithms
PACKAGE_FILE_NAMES1 := basetype\
					  shape\
					  stride\
					  slice\
					  tensor\
					  debugs
PACKAGE_FILE_NAMES2 := utils\
					   matrix\
					   solves
PACKAGES1 := ../../../bases/basetype.cpp\
			../../../bases/shape.cpp\
			../../../bases/stride.cpp\
			../../../bases/slice.cpp\
			../../../bases/tensor.cpp\
			../../../bases/debugs.cpp
PACKAGES2 := ../../../algorithms/utils.cpp\
			 ../../../algorithms/matrix.cpp\
			 ../../../algorithms/solves.cpp
OBJS := basetype.o\
		shape.o\
		stride.o\
		slice.o\
		tensor.o\
		debugs.o\
		utils.o\
		matrix.o\
		solves.o


$(TARGET).exe: $(OBJS)
	g++ $(SOURCES) $(OBJS) -I$(INCLUDES1) -I$(INCLUDES2) -std=c++11 -o $(TARGET).exe

$(OBJS): $(PACKAGES1) $(PACKAGES2)
	for file_name in $(PACKAGE_FILE_NAMES1); do \
		g++ -c $(INCLUDES1)/$$file_name.cpp -std=c++11 -o $$file_name.o; \
	done

	for file_name in $(PACKAGE_FILE_NAMES2); do \
		g++ -c $(INCLUDES2)/$$file_name.cpp -std=c++11 -o $$file_name.o; \
	done

clean:
	$(RM) -rf $(OBJS) $(TARGET).exe $(LOG_FILE)


	