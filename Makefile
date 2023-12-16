CC = g++
CFLAGS = -Wall -g
EXEC = deputados
SRC_DIR = src
OBJ_DIR = obj
CPP = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/electionslib/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CPP))
CPPFLAGS = -std=c++17

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(EXEC)
runfederal:
	@make > /dev/null
	@./$(EXEC) --federal candidatos.csv votacao.csv 02/10/2022
runestadual:
	@make > /dev/null
	@./$(EXEC) --estadual candidatos.csv votacao.csv 02/10/2022
