##
## EPITECH PROJECT, 2023
## Raytracer
## File description:
## Makefile
##

SRC =	src/main.cpp

OBJ =	 $(SRC:src/%.cpp=obj/%.o)

MAIN_OBJ =	$(MAIN_SRC:src/%.cpp=obj/%.o)

CXX =	g++

CXXFLAGS =	-std=c++20 -Wall -Wextra

CPPFLAGS =	-iquote include

LDFLAGS =

LDLIBS =

NAME =	../zappy_gui

TESTS =

all:	$(NAME)

obj/%.o:	src/%.cpp
	mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

clean:
	rm -f $(OBJ)
	find . -name *.gcno -delete
	find . -name *.gcda -delete

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CXXFLAGS += -ggdb
debug: fclean $(NAME)

tests_run:

.PHONY: fclean all re clean debug tests_run
