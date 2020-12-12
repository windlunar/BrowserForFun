
toolchain=g++
bin_destination_path =../../build
TARGET=main
SOURCE=parse.cpp loadfile.cpp layout.cpp 
CLIENT_SOURCE=client.cpp main.cpp

.PHONY : all
all: $(TARGET)
	
$(TARGET):
	$(toolchain) $(CLIENT_SOURCE) -o $(bin_destination_path)/$(TARGET)

	@echo
	@echo client Build sucessfully!