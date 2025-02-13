NAME = webserv

CC = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
# CXXFLAGS = -std=c++98
#CPPFLAGS 
SRCS = ./server/main.cpp \
		./server/Server.cpp \
		./server/ServerProxy.cpp \
		./server/ServerWeb.cpp \
		./server/ServerManager.cpp \
		./server/Kqueue.cpp \
		./server/HttpMsg.cpp \
		./server/HttpRequest.cpp \
		./server/HttpResponse.cpp \
		./exception/Exception.cpp
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
