##
## EPITECH PROJECT, 2023
## Raytracer
## File description:
## Makefile
##

NAME =	zappy_gui

BUILD = build

all:	$(NAME)

$(NAME):
	mkdir -p $(BUILD)
	cmake -S . -B $(BUILD)
	make -C $(BUILD)
	mv $(BUILD)/$(NAME) ../$(NAME)

clean:
	make -C $(BUILD) clean

fclean: clean
	rm -f ../$(NAME)
	if [ -d "$(BUILD)" ]; then \
		rm -rf $(BUILD); \
	fi \

re: fclean all

tests_run:

.PHONY: fclean all re clean tests_run