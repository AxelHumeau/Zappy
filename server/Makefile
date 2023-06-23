##
## EPITECH PROJECT, 2023
## NanoTekSpice
## File description:
## Makefile
##

SRC =			main.c							\
				client_handling.c				\
				loop.c							\
				destroy_server.c				\
				buffer.c						\
				initialization/get_params.c		\
				initialization/init_server.c	\
				initialization/setup_server.c	\
				initialization/init_game.c		\
				initialization/init_resource.c	\
				utils/utils.c					\
				utils/utils_broadcast.c			\
				utils/utils_look.c				\
				utils/utils_player.c			\
				utils/utils_end_game.c			\
				utils/utils_incantation.c		\
				utils/utils_list.c				\
				utils/str_to_array.c			\
				utils/utils_object.c			\
				ai/player_handling.c			\
				ai/player_command.c				\
				ai/check_instant_command.c		\
				ai/commands/forward.c			\
				ai/commands/right.c				\
				ai/commands/left.c				\
				ai/commands/look.c				\
				ai/commands/inventory.c			\
				ai/commands/broadcast.c			\
				ai/commands/connect_nbr.c		\
				ai/commands/fork.c				\
				ai/commands/eject.c				\
				ai/commands/take.c				\
				ai/commands/set.c				\
				ai/commands/incantation.c		\
				gui/handle_gui_client.c			\
				gui/init_gui_client.c			\
				gui/broadcast_to_guis.c			\
				gui/commands/map_size.c			\
				gui/commands/tile_content.c		\
				gui/commands/map_content.c		\
				gui/commands/team_names.c		\
				gui/commands/player_infos.c		\
				gui/commands/time_unit.c		\
				gui/events/new_player.c			\
				gui/events/broadcast.c			\
				gui/events/death.c				\
				gui/events/egg.c				\
				gui/events/expulsion.c			\
				gui/events/incantation.c		\
				gui/events/resources.c			\
				gui/events/server_message.c		\

OBJ 		= 			$(SRC:%.c=obj/%.o)

CC			 =			gcc

CFLAGS 		=		-Wall -Wextra

CPPFLAGS 	=		-iquote include -D_GNU_SOURCE

LDFLAGS 	=		-lm

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

re:
	$(MAKE) fclean
	$(MAKE) all

debug: CPPFLAGS += -ggdb
debug: fclean $(NAME)

tests_run: func_tests

func_tests: CFLAGS += --coverage
func_tests: LDFLAGS += --coverage
func_tests: re
	find . -name "*.gcda" -delete
	./tests/functional/tester.sh

.PHONY: fclean all re clean debug tests_run func_tests
