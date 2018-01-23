#include "ft_ls.h"

static void	print_prefix(void)
{
	ft_putstr_fd(BINARY, 2);
	ft_putstr_fd(": ", 2);
}

static void	print_usage(void)
{
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(BINARY, 2);
	ft_putchar_fd(' ', 2);
	ft_putstr_fd("[-Ralrt] [file ...]\n", 2);
}

void		check_errno(char *path)
{
	print_prefix();
	if (errno == EACCES)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied", 2);
	}
}

void		enoent_error(char *filename)
{
	print_prefix();
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("No such file or directory", 2);
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
	print_usage();
}
