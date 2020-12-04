
toolchain=g++
bin_destination_path =./build
TARGET=browser
LINK=-lsfml-graphics -lsfml-window -lsfml-system
SOURCE=parse.cpp loadfile.cpp layout.cpp 

.PHONY : all
all: $(TARGET)
	
$(TARGET):
	mkdir -p build
	$(toolchain) browser.cpp $(SOURCE) -o $(bin_destination_path)/$(TARGET) $(LINK)

	@echo
	@echo Build sucessfully!


#Clean objects and bin
.PHONY : clean
clean :
	-rm $(bin_destination_path)/$(TARGET)
	






























