/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   options.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/26 00:40:17 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/26 00:41:52 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int		add_option(t_opts *options, char c)
{
	if (c == 'l')
		options->l = 1;
	else if (c == 'R')
		options->R = 1;
	else if (c == 'a')
		options->a = 1;
	else if (c == 'r')
		options->r = 1;
	else if (c == 't')
		options->t = 1;
	else
	{
		invalid_option(c);
		options->error = 1;
		return (-1);
	}
	return (0);
}

static t_opts    set_default_options(void)
{
	t_opts    options;

	options.R = 0;
	options.a = 0;
	options.l = 0;
	options.r = 0;
	options.t = 0;
	options.error = 0;
	return (options);
}

t_opts			get_options(size_t argc, char **argv)
{
	size_t	i;
	char	*pointer;
	t_opts	options;

	options = set_default_options();
	if (argc-- <= 1)
		return (options);
	i = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			return (options);
		pointer = argv[i];
		argv[i] += 1;
		if (*(argv[i]) != '-')
		{
			while (*(argv[i]))
			{
				add_option(&options, *(argv[i]));
				if (options.error)
					return (options);
				argv[i] += 1;
			}
		}
		argv[i] = pointer;
		i += 1;
	}
	return (options);
}
