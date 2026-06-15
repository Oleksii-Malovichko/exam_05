NAME = polyset

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Ido2 -I.

SRCS = array_bag.cpp \
	main.cpp \
	./do2/searchable_array_bag.cpp \
	./do2/searchable_tree_bag.cpp \
	./do2/set.cpp \
	tree_bag.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all