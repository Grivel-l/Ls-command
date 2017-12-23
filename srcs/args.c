/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   options.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 23:19:10 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/24 00:50:28 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void		option_error(void)
{
	ft_putstr_fd("Invalid option\n", 2);
}

static int		add_option(char **options, char c)
{
	if (ft_strchr(*options, c) != NULL)
		return (0);
	if (c == 'l')
		*options = ft_strrealloc(*options, "l");
	else if (c == 'R')
		*options = ft_strrealloc(*options, "R");
	else if (c == 'a')
		*options = ft_strrealloc(*options, "a");
	else if (c == 'r')
		*options = ft_strrealloc(*options, "r");
	else if (c == 't')
		*options = ft_strrealloc(*options, "t");
	else
	{
		option_error();
		return (-1);
	}
	if (*options == NULL)
		return (-1);
	return (0);
}

char			*get_options(int argc, char **argv)
{
	int		i;
	char	*pointer;
	char	*options;

	i = 0;
	options = NULL;
	if ((options = ft_strnew(1)) == NULL || argc-- <= 1)
		return (options);
	while (i < argc)
	{
		if (argv[i][0] != '-')
			return (options);
		pointer = argv[i];
		argv[i] += 1;
		while (*(argv[i]))
		{
			if (add_option(&options, *(argv[i])) == -1)
				return (NULL);
			argv[i] += 1;
		}
		argv[i] = pointer;
		i += 1;
	}
	return (options);
}

t_flist		*get_args_list(int argc, char **argv)
{
	int		i;
	t_file	file;
	t_flist	*list;
	t_flist	*pointer;

	i = 0;
	list = NULL;
	pointer = NULL;
	while (i < argc - 1)
	{
		if (argv[i][0] != '-')
		{
			file.is_arg = 1;
			file.filename = ft_strdup(argv[i]);
			if (list == NULL)
			{
				if ((list = new_flist(new_file(argv[i], 1))) == NULL)
					return (NULL);
				pointer = list;
			}
			else
				if ((list->next = new_flist(new_file(argv[i], 1))) == NULL)
					return (NULL);
			if (list->next != NULL)
				list = list->next;
		}
		i += 1;
	}
	return (pointer == NULL ? new_flist(new_file(NULL, 0)) : pointer);
}
