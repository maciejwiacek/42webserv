CC       := g++
CFLAGS   := -Wall -Wextra -Werror -std=c++98
SRC      := $(wildcard *.cpp)
OBJ      := $(SRC:.cpp=.o)
NAME     := cgi

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) cgi_output.txt

re: fclean all

.PHONY: all clean fclean re