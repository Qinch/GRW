CC= g++
FLAGS= -Wno-unused-result -O3 -msse2 -std=c++11 
SRC= ./src
SRC-FILE= $(SRC)/*.cpp
BIN= ./bin


GRWTEST-BIN = $(BIN)/grw
grw: $(GRWTEST-BIN)
$(GRWTEST-BIN) : $(SRC-FILE)
	$(CC) $(FLAGS) -o $@ $^
clean:
	-rm -r -f $(BIN)/*

