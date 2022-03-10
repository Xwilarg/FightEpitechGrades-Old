CC	= g++

LDLIBS	= -lsfml-graphics -lsfml-window -lsfml-system -lGL

CXXFLAGS = -W
CXXFLAGS += -Wall
CXXFLAGS += -g3
CXXFLAGS += -std=c++11
CXXFLAGS += -Iinclude

NAME	= fightEpitechGrades

SRCS	= src/main.cpp	\
	  src/player.cpp \
	  src/projectile.cpp \
	  src/ai_old.cpp \
	  src/ai_functions.cpp \
	  src/ai_new.cpp


OBJS	= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDLIBS) $(CXXFLAGS)

launch: all
	./$(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re launch
