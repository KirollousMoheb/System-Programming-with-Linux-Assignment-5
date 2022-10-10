LINKING_TYPE=static


######################################
SOURCE_PATH=./source
EXE_PATH=./objects/executables
INC= -I ./includes

ifeq ($(LINKING_TYPE), static)
OBJ_PATH=./objects/static
LIB=libCommands.a
else ifeq ($(LINKING_TYPE), dynamic)
OBJ_PATH=./objects/dynamic
LIB=libCommands.so

endif
##########################################
$(EXE_PATH)/myshell: $(OBJ_PATH)/myshell.o $(OBJ_PATH)/$(LIB)
ifeq ($(LINKING_TYPE), static)
	gcc -g $^ -lreadline -o $@
else ifeq ($(LINKING_TYPE), dynamic)
	gcc -g  $< -lCommands -L $(OBJ_PATH) -lreadline -o $@
	export LD_LIBRARY_PATH=$(OBJ_PATH)::$LD_LIBRARY_PATH
endif
###############################################################



$(OBJ_PATH)/myshell.o: myshell.c
	gcc -c -g $(INC)  $< -o $@

$(OBJ_PATH)/$(LIB): $(OBJ_PATH)/cd.o  $(OBJ_PATH)/echo.o $(OBJ_PATH)/export.o $(OBJ_PATH)/helper.o $(OBJ_PATH)/local_vars.o $(OBJ_PATH)/parse.o $(OBJ_PATH)/prompt.o
ifeq ($(LINKING_TYPE), static)
	ar rcs $@ $^
else ifeq ($(LINKING_TYPE), dynamic)
	gcc -shared  $^  -o $@
endif

$(OBJ_PATH)/%.o:$(SOURCE_PATH)/%.c
ifeq ($(LINKING_TYPE), static)
	gcc -c -g $< -o $@
else ifeq ($(LINKING_TYPE), dynamic)
	gcc -c -g -fpic  $< -o $@
endif

clean:
	rm -f  $(OBJ_PATH)/*.o $(OBJ_PATH)/*.so  $(OBJ_PATH)/*.a $(EXE_PATH)/*









