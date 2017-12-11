# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/12/11 16:25:45 by legrivel     #+#   ##    ##    #+#        #
#    Updated: 2017/12/11 16:36:39 by legrivel    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = ft_ls
SRCS = main.c
OBJS = $(SRCS:.c=.o)
SRCS_PATH = ./srcs/
INCS_PATH = ./includes/
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) -I $(INCS_PATH) $(OBJS) -o $(NAME)

%.o: $(SRCS_PATH)%.c
	gcc $(FLAGS) -I $(INCS_PATH) -c $?

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean re
