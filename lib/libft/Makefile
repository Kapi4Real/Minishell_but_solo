# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: togomez <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/24 16:12:04 by togomez           #+#    #+#              #
#    Updated: 2024/10/11 12:04:23 by togomez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_atoi.c \
	  ft_bzero.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_isprint.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_strchr.c \
	  ft_strlcpy.c \
	  ft_strlen.c \
	  ft_strncmp.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  ft_strlcat.c \
	  ft_calloc.c \
	  ft_strdup.c \
	  ft_substr.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_itoa.c \
	  ft_strmapi.c \
	  ft_striteri.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_split.c \
	  ft_strcmp.c \
	  ft_isdigit_str.c\
	  ft_strjoin3.c\
	  ft_lstadd_back.c \
	  ft_lstclear.c \
	  ft_lstnew.c \
	  ft_lstadd_front.c \
          ft_lstsize.c \
          ft_lstlast.c \
          ft_lstdelone.c \
          ft_lstiter.c \
          ft_lstmap.c \
	  ft_isspace.c\
	  ft_strspn.c\
	  ft_strcspn.c\
	  ft_strtok.c\
	 	


	  
BSRC = 

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

HEADER = libft.h

CFLAGS = -Werror -Wextra -Wall

NAME = libft.a

all:	 $(NAME)

$(NAME): $(OBJ)
		 ar -crs $@ $^

$(BOBJ): $(BSRC)
	cc $(CFLAGS) -c $(BSRC) $(HEADER)

bonus: $(OBJ) $(BOBJ)
		 ar -crs $(NAME) $(OBJ) $(BOBJ) $(HEADER)

%.o: %.c $(HEADER)
		cc $(CFLAGS) $< -c -o $@

clean:
		rm -f $(OBJ) $(BOBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
