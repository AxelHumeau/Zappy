##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

SCRIPT_SRC =	zappy_ai

EXE_NAME = $(SCRIPT_SRC:%.py=%)

NAME = ../zappy_ai

all: $(NAME)

$(NAME):
	cd ..; ln -s ai/$(SCRIPT_SRC) $(SCRIPT_SRC)

clean:
	rm -rf __pycache__

fclean: clean

re: fclean all

tests_run:

.PHONY: fclean all re clean tests_run
