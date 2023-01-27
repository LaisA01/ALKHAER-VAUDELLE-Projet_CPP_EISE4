OBJS	= main.o game.o Textbox.o
SOURCE	= main.cpp game.cpp Textbox.cpp
HEADER	= MCQ.h question.h TrueFalse.h game.h TimedMCQ.h button.hpp PhotoMCQ.h Textbox.hpp textboxQuestion.h
OUT	= quizz.out
CC	 = g++
FLAGS	 = -g -c 
LFLAGS	 = 
SFML_LIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(SFML_LIBS)
	rm -f $(OBJS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

TrueFalse.o: TrueFalse.cpp
	$(CC) $(FLAGS) TrueFalse.cpp 

game.o: game.cpp
	$(CC) $(FLAGS) game.cpp 

Textbox.o: Textbox.cpp
	$(CC) $(FLAGS) Textbox.cpp 

clean:
	rm -f $(OBJS) $(OUT)