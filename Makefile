

bin_destination_path=./build


#Build
.PHONY : all
all:
	mkdir -p build
	make -C ./src

	@echo
	@echo Build sucessfully!


.PHONY : copy
copy :
	cp ./src/server/Server $(bin_destination_path)/

#Clean objects and bin
.PHONY : clean
clean :
	-rm $(bin_destination_path)/*
	-rm ./src/server/Server
	












