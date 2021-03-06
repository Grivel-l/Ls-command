# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/12/11 16:25:45 by legrivel     #+#   ##    ##    #+#        #
#    Updated: 2018/01/26 03:10:56 by legrivel    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = ft_ls
SRCS = main.c args.c objects.c list.c free_alloc.c print.c dirs.c errors.c \
	   sort.c infos.c print_infos.c options.c print2.c get_files.c
OBJS = $(SRCS:.c=.o)
SRCS_PATH = ./srcs/
INCS_PATH = ./includes/
LIB_PATH = ./libft/
FLAGS = -Wall -Wextra -Werror -Ofast
COMPILER = clang

all: $(NAME)

$(NAME): $(LIB_PATH) $(OBJS)
	$(COMPILER) $(FLAGS) -I $(INCS_PATH) $(OBJS) -o $(NAME) libft/libft.a

$(LIB_PATH): $(LIB_PATH)libft.a

$(LIB_PATH)libft.a:
	make -C $(LIB_PATH)

%.o: $(SRCS_PATH)%.c
	$(COMPILER) $(FLAGS) -I $(INCS_PATH) -c $?

clean:
	make -C $(LIB_PATH) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIB_PATH) fclean
	rm -f $(NAME)

re: fclean all
