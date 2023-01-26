SRC=./src

INCLUDE=./include
MAIN=main.cpp

EXE=./typeStructor

CC=g++

OBJ=./obj

OBJ_FILES=\
          $(OBJ)/main.o\
          $(OBJ)/menu.o\
          $(OBJ)/modes.o\
          $(OBJ)/constructFunctions.o\
          $(OBJ)/typingSample.o\
          $(OBJ)/weighMaster.o

DEBUG=
NODEBUG=-D NDEBUG
ISDEBUG=$(DEBUG)

LIBS= -lmenu -lncurses -lm
OPTIMIZATION=-O3
CFLAGS= $(LIBS) $(OPTIMIZATION) -march=x86-64 $(ISDEBUG) -std=c++2a -fomit-frame-pointer -fexpensive-optimizations -pedantic-errors -pedantic  -fdiagnostics-show-option  -fdiagnostics-show-option -Wno-div-by-zero  -funroll-loops -fvariable-expansion-in-unroller -fprefetch-loop-arrays -freorder-blocks-and-partition -fno-cprop-registers -funswitch-loops -funsafe-loop-optimizations -Wall -Wextra

PRINT_CLEAR     =@echo "\e[1;29m CLEAR \e[0m"
PRINT_PREPARE   =@echo "\e[1;29m PREPARE TO COMPILE \e[0m"
PRINT_UNZIPTEXTS=@echo "\e[1;29m UNZIP TEXTS \e[0m"
PRINT_BUILD     =@echo "\e[1;31m BUILDING \e[0m \e[1;36m $@ \e[0m"
PRINT_LINK      =@echo "\e[1;32m LINK\e[0m \e[1;36m    $@ \e[0m"
PRINT_EXE       =@echo "\e[1;33m EXECUTION\e[0m \e[1;36m $< \e[0m"
PRINT_SUCSESS   =@echo "\e[1;33m SUCSESSFULLY FINISH \e[0m"

##########################################################################################3
all:run

##########################################################################################3

run: $(EXE) ./texts
	$(PRINT_EXE)
	$(EXE)
	$(PRINT_SUCSESS)

debugrun: $(EXE) ./texts
	$(PRINT_EXE)
	@valgrind -q --show-reachable=yes --leak-check=full --error-exitcode=-1 --exit-on-first-error=no ./$(EXE)
	$(PRINT_SUCSESS)
##########################################################################################3

$(EXE):\
          $(INCLUDE)\
          $(SRC)/$(MAIN)\
          OBJ_COMPILE
	$(PRINT_LINKED)
	@$(CC) $(OBJ_FILES) -o $@ -I$(INCLUDE) $(CFLAGS)

##########################################################################################3
configuration: $(INCLUDE)/config.hxx

OBJ_COMPILE: $(OBJ)\
						$(OBJ_FILES)
##########################################################################################3

$(OBJ)/modes.o: configuration\
          $(SRC)/modes.cpp\
          $(INCLUDE)/modes.hxx
	$(PRINT_BUILD)
	@$(CC) -c $(SRC)/modes.cpp -o $@ -I$(INCLUDE) $(CFLAGS)

$(OBJ)/constructFunctions.o:\
          configuration\
          $(SRC)/constructFunctions.cpp\
          $(INCLUDE)/constructFunctions.hxx
	$(PRINT_BUILD)
	@$(CC) -c $(SRC)/constructFunctions.cpp -o $@ -I$(INCLUDE) $(CFLAGS)

$(OBJ)/typingSample.o:\
          configuration\
          $(SRC)/typingSample.cpp\
          $(INCLUDE)/typingSample.hxx
	$(PRINT_BUILD)
	@$(CC) -c $(SRC)/typingSample.cpp -o $@ -I$(INCLUDE) $(CFLAGS)

$(OBJ)/menu.o:\
          configuration\
          $(SRC)/menu.cpp\
          $(INCLUDE)/menu.hxx
	$(PRINT_BUILD)
	@$(CC) -c $(SRC)/menu.cpp -o $@ -I$(INCLUDE) $(CFLAGS)

$(OBJ)/weighMaster.o:\
          configuration\
          $(SRC)/weighMaster.cpp\
          $(INCLUDE)/weighMaster.hxx
	$(PRINT_BUILD)
	@$(CC) -c $(SRC)/weighMaster.cpp -o $@ -I$(INCLUDE) $(CFLAGS)

$(OBJ)/main.o:\
          configuration\
          $(SRC)/main.cpp
	$(PRINT_BUILD)
	@$(CC) -c $(SRC)/main.cpp -o $@ -I$(INCLUDE) $(CFLAGS)

##########################################################################################
./texts:
	$(PRINT_UNZIPTEXTS)
	@unzip texts.zip >/dev/null 2>/dev/null

$(OBJ):
	$(PRINT_MAKEDIRS)
	@mkdir -p $(OBJ)

clear:
	@clear
	$(PRINT_CLEAR)
	@rm -rf $(OBJ)
	@rm -f $(EXE)
	@rm -f logfile
	@rm -rf texts

##########################################################################################3
