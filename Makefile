##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

all clear fclear re tests_run:
	$(MAKE) -C ai $@
	$(MAKE) -C server $@
	$(MAKE) -C gui $@

zappy_server:
	$(MAKE) -C server
zappy_gui:
	$(MAKE) -C gui
zappy_ai:
	$(MAKE) -C ai
