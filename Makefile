# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 15:44:10 by rkaufman          #+#    #+#              #
#    Updated: 2022/01/26 06:03:42 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		:=	minitalk
CC 			:=	gcc
HEADER		:=	minitalk.h

SERVER 	:=	ft_server.c
CLIENT	:=	ft_client.c

SRCBONUS	:=	

OBJFILES 	:=	$(SRCFILES:%.c=%.o)


CFLAGS 		:=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SERVER) -o server
	$(CC) $(CFLAGS) $(CLIENT) -o client

clean:
	rm -f

fclean: clean
	rm -f server client

re: fclean all

norminette:
	norminette -R CheckForbiddenSourceHeader $(SERVER) $(CLIENT) $(HEADER)

.PHONY: clean fclean re