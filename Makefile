NAME= duel

SRC_PATH= ./src/
OBJ_PATH= ./obj/
INC_PATH= ./includes/

SOURCES= main.cpp \
		 sdl_functions.cpp \
		 Player.cpp \
		 game_loop.cpp

INCLUDES= duel.h

OBJECTS= $(SOURCES:.cpp=.o)

INC= $(addprefix $(INC_PATH), $(INCLUDES))
SRC= $(addprefix $(SRC_PATH), $(SOURCES))
OBJ= $(addprefix $(OBJ_PATH), $(OBJECTS))

FLAGS= -Wall -Werror -Wextra

all:
	make $(NAME)

$(NAME): $(OBJ) Makefile
	g++ $(FLAGS) -o ${NAME} ${OBJ} -I . -lSDL2 -lSDL2_image -lSDL2_mixer -Wl,-rpath=/usr/local/lib

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp $(INC)
	if test ! -d $(dir $@); then mkdir -p $(dir $@); fi
	g++ $(FLAGS) -I $(INC_PATH) -o $@ -c $<

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
