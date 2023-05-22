##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

zappy_server:
	$(MAKE) -C server
zappy_gui:
	$(MAKE) -C gui
zappy_ai:
	$(MAKE) -C ai

all clear fclear re:
	$(MAKE) -C ai $@
	$(MAKE) -C server $@
	$(MAKE) -C gui $@
