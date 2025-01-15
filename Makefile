NAME = webserv

CC = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
#CPPFLAGS 
SRCS = ./main.cpp \
	   ./AConfig.cpp \
	   ./AServer.cpp \
	   ./Location.cpp \
	   ./LocationConfig.cpp \
	   ./MainServer.cpp \
	   ./ServerConfig.cpp \
	   ./exception/Exception.cpp \

OBJS = $(SRCS:.cpp=.o)

#bonus
all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

%.o : %.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean
	make all

.PHONY: all clean fclean re
