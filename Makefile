##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

all clean fclean re tests_run:
	$(MAKE) -C ai $@
	$(MAKE) -C server $@
	$(MAKE) -C gui $@

display_cov:
	gcovr --exclude gui/build
	cd ai; coverage report

zappy_server:
	$(MAKE) -C server
zappy_gui:
	$(MAKE) -C gui
zappy_ai:
	$(MAKE) -C ai

.PHONY: all clean fclean re tests_run display_cov zappy_server zappy_gui zappy_ai
