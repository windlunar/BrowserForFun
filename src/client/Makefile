
toolchain=g++
bin_destination_path =../../build
TARGET=main
SOURCE=parse.cpp loadfile.cpp layout.cpp 
CLIENT_SOURCE=client.cpp main.cpp ../browser/parse.cpp ../browser/loadfile.cpp ../browser/layout.cpp
LINK=-lsfml-graphics -lsfml-window -lsfml-system -lpthread

.PHONY : all
all: $(TARGET)
	
$(TARGET):
	$(toolchain) $(CLIENT_SOURCE) -o $(bin_destination_path)/$(TARGET) $(LINK)

	@echo
	@echo client Build sucessfully!