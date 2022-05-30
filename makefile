CC = gcc
CFLAGS = -Wall -Werror -lm -g
INC = -Iinclude/
SRC = ~/Bureau/IN104/CMaze/CMaze-main/
#DPE = mazeEnv.h
#$(info EXEC before = $(EXEC))
#$(info EXEC after = $(EXEC))
#$(info DIRECTORY before = $(DIRECTORY))
DIRECTORY = ~/Bureau/IN104/CMaze/CMaze-main # Make sure you're in the right directory!
#$(info DIRECTORY after = $(DIRECTORY)) 
all : dfs mazeEnv functions

dfs.o : $(SRC)dfs.c $(SRC)mazeEnv.h $(SRC)Q_learning.h
	$(CC) $(INC) -c -o $@ $< $(CFLAGS)

mazeEnv.o : $(SRC)mazeEnv.c $(SRC)mazeEnv.h $(SRC)funtions.h
	$(CC) $(INC) -c -o $@ $< $(CFLAGS)

functions.o : $(SRC)functions.c $(SRC)functions.h
	$(CC) $(INC) -c -o $@ $< $(CFLAGS)

Q_learning.o: $(SRC)Q_learning.c $(SRC)Q_learning.h $(SRC)mazeEnv.h $(SRC)functions.h
	$(CC) $(INC) -c -o $@ $< $(CFLAGS)

programme.out : $(SRC)dfs.o $(SRC)functions.o $(SRC)mazeEnv.o $(SRC)Q_learning.o
	$(CC) $(INC) -o programme.out $^ $(CFLAGS)

clean :
	rm -rf $(SRC)%.o
	rm -rf $(SRC)%.out
                                                                                                                                                             





#Ce que je veux :                                                                                                                                                                                          
#gcc -c trucs.c                                                                                                                                                                                            
#...                                                                                                                                                                                                      
#gcc -o a.out trucs.o 
