##
## EPITECH PROJECT, 2023
## NanoTekSpice
## File description:
## Makefile
##

SRC =			main.c							\
				client_handling.c				\
				player_handling.c				\
				loop.c							\
				destroy_server.c				\
				buffer.c						\
				utils.c							\
				initialization/get_params.c		\
				initialization/init_server.c	\
				initialization/setup_server.c	\
				initialization/init_game.c		\
				initialization/init_resource.c	\
				gui/handle_gui_client.c			\
				gui/commands/map_size.c			\
				gui/commands/tile_content.c		\
				gui/commands/map_content.c		\
				gui/commands/team_names.c		\
				gui/commands/player_infos.c		\

OBJ 		= 			$(SRC:%.c=obj/%.o)

CC			 =			gcc

CFLAGS 		=		-Wall -Wextra

CPPFLAGS 	=		-iquote include -D_GNU_SOURCE

LDFLAGS 	=

LDLIBS 		=

NAME 		= 		../zappy_server

all:	$(NAME)

obj/%.o:	src/%.c
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) -o $(NAME) $(OBJ)

clean:
	find . -name "*.gcno" -delete
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CPPFLAGS += -ggdb
debug: fclean $(NAME)

tests_run:

.PHONY: fclean all re clean debug tests_run
