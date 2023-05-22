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
	pyinstaller -F $(SCRIPT_SRC)
	mv dist/$(EXE_NAME) $(NAME)

clean:
	rm -rf dist

fclean: clean
	rm -rf build

re: fclean all

.PHONY: fclean all re clean
