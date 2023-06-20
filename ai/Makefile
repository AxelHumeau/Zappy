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
	rm -rf $(NAME)

re: fclean all

tests_run: func_tests

func_tests: re
	find . -name "*.gcda" -delete
	./tests/functional/tester.sh

.PHONY: fclean all re clean debug tests_run func_tests
