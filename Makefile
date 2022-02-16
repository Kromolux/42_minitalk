# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 15:44:10 by rkaufman          #+#    #+#              #
#    Updated: 2022/02/16 17:17:26 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		:=	minitalk
CC 			:=	gcc
HEADER		:=	minitalk.h

SERVER		:=	ft_server.c
CLIENT		:=	ft_client.c
UTILS		:=	ft_utils.c

SRCBONUS	:=	

OBJFILES 	:=	$(SRCFILES:%.c=%.o)


CFLAGS 		:=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): server client

server:
	$(CC) $(CFLAGS) $(SERVER) $(UTILS) -o server

client:
	$(CC) $(CFLAGS) $(CLIENT) $(UTILS) -o client

clean:
	rm -f server client

fclean: clean

re: fclean all

norminette:
	norminette -R CheckForbiddenSourceHeader $(SERVER) $(CLIENT) $(HEADER)

.PHONY: clean fclean re