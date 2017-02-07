CC	:= gcc -g

RM	:= rm -rf

LDFLAGS	+= -L. -lncurses

CFLAGS	+= -Iinc -Wall -Wextra

SRCDIR := ./src/

SRCS	:= $(SRCDIR)main.c \
	$(SRCDIR)map/map.c \
	$(SRCDIR)logic/logic.c \

OBJS	:= $(SRCS:.c=.o)

NAME	:= game_of_life

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
