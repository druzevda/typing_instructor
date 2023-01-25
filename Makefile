SRC=./src

INCLUDE=./include
MAIN=main.cpp

EXE=./typeStructor

CC=g++

OBJ=./obj

OBJ_FILES=\
          $(OBJ)/main.o\
          $(OBJ)/menu.o\
          $(OBJ)/typingSample.o\
          $(OBJ)/weighMaster.o

DEBUG=-D NDEBUG
NODEBUG=
ISDEBUG=$(NODEBUG)

CFLAGS= -lmenu -lncurses -march=x86-64 $(ISDEBUG) -std=c++2a -fomit-frame-pointer -fexpensive-optimizations -O3 -pedantic-errors -pedantic  -fdiagnostics-show-option  -fdiagnostics-show-option -Wno-div-by-zero  -funroll-loops -fvariable-expansion-in-unroller -fprefetch-loop-arrays -freorder-blocks-and-partition -fno-cprop-registers -funswitch-loops -funsafe-loop-optimizations

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

##########################################################################################3

$(EXE):\
					clear\
          $(INCLUDE)\
          $(SRC)/$(MAIN)\
          OBJ_COMPILE
	$(PRINT_LINKED)
	@$(CC) $(OBJ_FILES) -o $@ -I$(INCLUDE) $(CFLAGS)

##########################################################################################3

OBJ_COMPILE: $(OBJ)\
						$(OBJ)/main.o\
						$(OBJ)/menu.o\
						$(OBJ)/typingSample.o\
						$(OBJ)/weighMaster.o

##########################################################################################3

$(OBJ)/typingSample.o:\
          $(SRC)/typingSample.cpp\
          $(INCLUDE)/typingSample.hxx
	$(PRINT_BUILD)
	@$(CC) -c $< -o $@ -I$(INCLUDE) $(CFLAGS)

$(OBJ)/menu.o:\
          $(SRC)/menu.cpp\
          $(INCLUDE)/menu.hxx
	$(PRINT_BUILD)
	@$(CC) -c $< -o $@ -I$(INCLUDE) $(CFLAGS)

$(OBJ)/weighMaster.o:\
          $(SRC)/weighMaster.cpp\
          $(INCLUDE)/weighMaster.hxx
	$(PRINT_BUILD)
	@$(CC) -c $< -o $@ -I$(INCLUDE) $(CFLAGS)

$(OBJ)/main.o:\
          $(SRC)/main.cpp
	$(PRINT_BUILD)
	@$(CC) -c $< -o $@ -I$(INCLUDE) $(CFLAGS)

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
