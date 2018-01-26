/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   errors.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/26 00:28:49 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/26 00:31:26 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_prefix(void)
{
	ft_putstr_fd(BINARY, 2);
	ft_putstr_fd(": ", 2);
}

void		print_error(t_file *file)
{
	print_prefix();
	ft_putstr_fd(file->filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file->error, 2);
}

void		enoent_error(char *filename)
{
	print_prefix();
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
}

void		eacces_error(char *filename)
{
	print_prefix();
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("Permission denied", 2);
}

void		invalid_option(char c)
{
	print_prefix();
	ft_putstr_fd("illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(BINARY, 2);
	ft_putchar_fd(' ', 2);
	ft_putstr_fd("[-Ralrt] [file ...]\n", 2);
}
