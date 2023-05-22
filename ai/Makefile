##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

SCRIPT_SRC = zappy_ai.py

EXE_NAME = $(SCRIPT_SRC:%.py=%)

NAME = ../zappy_ai

all:
	pyinstaller $(SCRIPT_SRC)
	mv dist/$(EXE)/$(EXE) $(NAME)

clean:
	rm -r dist/$(EXE)

fclean: clean
	rm -r build

re: fclean all

.PHONY: fclean all re clean
