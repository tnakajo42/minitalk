# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnakajo <tnakajo@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/11 14:48:02 by tnakajo           #+#    #+#              #
#    Updated: 2023/02/20 19:41:06 by tnakajo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = server.c client.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all:
	@cd ft_printf && make all
	@cd libft && make all
	$(CC) $(CFLAGS) server.c ft_printf/ft_printf.a libft/libft.a -o server	
	$(CC) $(CFLAGS) client.c ft_printf/ft_printf.a libft/libft.a -o server
	
clean:
	@cd ft_printf && make clean
	@cd libft && make clean
	@rm -f server
	@rm -f client

fclean: clean
	@cd ft_printf && make fclean
	@cd libft && make fclean

re: fclean all

bonus: fclean
	@cd ft_printf && make all
	@cd libft && make all
	$(CC) $(CFLAGS) server.c ft_printf/ft_printf.a libft/libft.a -o server	
	$(CC) $(CFLAGS) client.c ft_printf/ft_printf.a libft/libft.a -o server

# server client

# bonus:	server client

# server:
# 	$(CC) $(CFLAGS) server.c ft_printf/ft_printf.a libft/libft.a -o server

# server: server.o libft ft_printf
# 	$(CC) -o $@ $< -Llibft -lft -Lft_printf -lft

# server: server.o libft ft_printf	
# $(CC) -o $@ $< -Llibft -Lft_printf -lft

# client: client.o ft_printf
# 	$(CC) -o $@ $< -Lft_printf -lft

# %.o: %.c
# 	$(CC) -c $(CFLAGS) $?

# libft:
# 	make -C libft

# ft_printf:
# 	make -C ft_printf

# clean:
# 	rm -f $(OBJECTS)
# 	make -C libft clean
# 	make -C ft_printf clean
	
# fclean: clean
# 	rm -f server client libft/libft.a ft_printf/ft_printf.a

# re: fclean all

# .PHONY: all bonus libft ft_printf clean fclean re

#--------------------------------------------------------------------

# SRCS		= server.c client.c

# OBJS		= ${SRCS:.c=.o}

# NAME		= minitalk.a

# CC			= gcc

# CFLAGS		= -Wall -Wextra -Werror

# all: 		server client

# bonus:		server client

# server: 	server.o libft ft_printf

# client:		client.o libft ft_printf

# .c.o:		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

# libft:		make -c libft

# ft_printf:	make -c ft_printf

# clean:
# 			rm -f $(OBJECTS)
# 			make -c libft clean
# 			make -c ft_printf clean
	
# fclean: 
# 			clean
# 			rm -f server client libft/libft.a
# 			rm -f server client ft_printf/ft_printf.a

# re: fclean all

# .PHONY: all bonus libft ft_printf clean fclean re