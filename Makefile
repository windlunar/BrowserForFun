

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
	-rm $(bin_destination_path)/main $(bin_destination_path)/browser_test
	-rm ./src/server/Server
	-rm ./temp/*
	touch ./temp/record
	-rm ./build/temp/*
	touch ./build/temp/record

#Clean objects and bin
.PHONY : cleantemp
cleantemp :
	-rm ./temp/*
	touch ./temp/record
	












