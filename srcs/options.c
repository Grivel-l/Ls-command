/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   options.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 23:19:10 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/11 23:23:47 by legrivel    ###    #+. /#+    ###.fr     */
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
	return (0);
}

char			*get_options(int argc, char **argv)
{
	char	*options;

	if (argc <= 1 || (options = ft_strnew(1)) == NULL)
		return (NULL);
	argc -= 1;
	while (argc-- > 0)
	{
		if (argv[argc][0] == '-')
		{
			argv[argc] += 1;
			while (*(argv[argc]))
			{
				if (add_option(&options, *(argv[argc])) == -1)
					return (NULL);
				argv[argc] += 1;
			}
		}
	}
	return (options);
}
