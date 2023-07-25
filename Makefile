CC		= clang++
CXXFLAGS	=  -ggdb -O0 -g3 -g -std=c++17
NAME    =   test
CFLAGS  =       -W  -Wextra -Wall 
SRC =   src/main.cpp 
OBJ =   $(SRC:.cpp=.o)
FLAGS   =   -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDES =  -I./includes/

all:    $(NAME)

$(NAME):    $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(INCLUDES) $(FLAGS) $(CFLAGS) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)   \
	rm -f *~    \
	rm -f *#    \

re: fclean clean all

.cpp.o:
	$(CC) -c -o $@ $< $(INCLUDES) $(CFLAGS) $(CXXFLAGS)

.PHONY: all re clean fclean