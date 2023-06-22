##
## EPITECH PROJECT, 2023
## Raytracer
## File description:
## Makefile
##

NAME =	zappy_gui

PARTICLES_ZIP = Particles.zip

PARTICLES_FOLDER = assets/Particles

PARTICLES_SRC = OneDirection.particle

BUILD = build

DEBUG =

all:	$(NAME) zip_particles

$(NAME):
	mkdir -p $(BUILD)
	cmake -S . $(DEBUG) -B $(BUILD)
	make -C $(BUILD)
	cp $(BUILD)/$(NAME) ../$(NAME)

zip_particles:
	rm -f assets/$(PARTICLES_ZIP)
	cd $(PARTICLES_FOLDER); zip $(PARTICLES_ZIP) $(PARTICLES_SRC)
	mv $(PARTICLES_FOLDER)/$(PARTICLES_ZIP) assets/$(PARTICLES_ZIP)

clean:
	if [ -d "$(BUILD)" ]; then make -C $(BUILD) clean; fi

fclean: clean
	rm -f ../$(NAME)
	if [ -d "$(BUILD)" ]; then rm -rf $(BUILD); fi

re: fclean all

tests_run: func_tests

func_tests: DEBUG += -DCOMPILE_FLAGS=--coverage
func_tests: re
	find . -name "*.gcda" -delete
	./tests/functional/tester.sh

debug: DEBUG += -DCMAKE_BUILD_TYPE=Debug
debug: re

.PHONY: fclean all re clean tests_run debug func_tests zip_particles
