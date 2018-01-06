#include "ft_ls.h"

void	print_filetype(mode_t st_mode)
{
	if (S_ISDIR(st_mode))
		ft_putchar('d');
	else if (S_ISLNK(st_mode))
		ft_putchar('l');
	else if (S_ISSOCK(st_mode))
		ft_putchar('s');
	else if (S_ISCHR(st_mode))
		ft_putchar('c');
	else if (S_ISBLK(st_mode))
		ft_putchar('b');
	else
		ft_putchar('-');
}

void	print_permissions(size_t permissions)
{
	if (permissions >= 4)
	{
		permissions -= 4;
		ft_putchar('r');
	}
	else
		ft_putchar('-');
	if (permissions >= 2)
	{
		permissions -= 2;
		ft_putchar('w');
	}
	else
		ft_putchar('-');
	if (permissions >= 1)
	{
		permissions -= 1;
		ft_putchar('x');
	}
	else
		ft_putchar('-');
}

void	print_time(char *time)
{
	size_t	i;

	i = 0;
	while (*time)
	{
		if (i >= 4 && i <= 15)
			ft_putchar(*time);
		time += 1;
		i += 1;
		if (i > 15)
			break ;
	}
}
