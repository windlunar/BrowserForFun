
toolchain=g++
bin_destination_path =../../build
TARGET=browser
LINK=-lsfml-graphics -lsfml-window -lsfml-system
SOURCE=parse.cpp loadfile.cpp layout.cpp 

.PHONY : all
all: $(TARGET)
	
$(TARGET):
	$(toolchain) browser.cpp $(SOURCE) -o $(bin_destination_path)/$(TARGET) $(LINK)


	@echo
	@echo browser Build sucessfully!



	






























