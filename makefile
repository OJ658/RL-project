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

dfs.o : $(SRC)dfs.c $(SRC)mazeEnv.h $(SRC)q_learning.h $(SRC)sarsa.h $(SRC)double_q_learning.h
	$(CC) $(INC) -c -o $@ $< $(CFLAGS)

mazeEnv.o : $(SRC)mazeEnv.c $(SRC)mazeEnv.h $(SRC)funtions.h
	$(CC) $(INC) -c -o $@ $< $(CFLAGS)

functions.o : $(SRC)functions.c $(SRC)functions.h
	$(CC) $(INC) -c -o $@ $< $(CFLAGS)

q_learning.o: $(SRC)q_learning.c $(SRC)q_learning.h $(SRC)mazeEnv.h $(SRC)functions.h
	$(CC) $(INC) -c -o $@ $< $(CFLAGS)

sarsa.o: $(SRC)sarsa.c $(SRC)sarsa.h $(SRC)mazeEnv.h $(SRC)functions.h
	$(CC) $(INC) -c -o $@ $< $(CFLAGS)

double_q_learning.o: $(SRC)double_q_learning.c $(SRC)double_q_learning.h $(SRC)mazeEnv.h $(SRC)functions.h
	$(CC) $(INC) -c -o $@ $< $(CFLAGS)

programme.out : $(SRC)dfs.o $(SRC)functions.o $(SRC)mazeEnv.o $(SRC)q_learning.o $(SRC)sarsa.o $(SRC)double_q_learning.o
	$(CC) $(INC) -o programme.out $^ $(CFLAGS)

clean :
	rm -rf $(SRC)%.o
	rm -rf $(SRC)%.out
                                                                                                                                                             
