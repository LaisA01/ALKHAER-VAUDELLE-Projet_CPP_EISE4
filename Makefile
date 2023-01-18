OBJS	= main.o MCQ.o question.o TrueFalse.o game.o
SOURCE	= main.cpp MCQ.cpp question.cpp TrueFalse.cpp game.cpp
HEADER	= MCQ.h question.h TrueFalse.h game.h TimedMCQ.h button.hpp
OUT	= quizz.out
CC	 = g++
FLAGS	 = -g -c
LFLAGS	 = 
SFML_LIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(SFML_LIBS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

MCQ.o: MCQ.cpp
	$(CC) $(FLAGS) MCQ.cpp 

question.o: question.cpp
	$(CC) $(FLAGS) question.cpp 

TrueFalse.o: TrueFalse.cpp
	$(CC) $(FLAGS) TrueFalse.cpp 

game.o: game.cpp
	$(CC) $(FLAGS) game.cpp 


clean:
	rm -f $(OBJS) $(OUT)