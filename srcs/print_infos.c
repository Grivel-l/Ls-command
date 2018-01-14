/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_infos.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/14 18:58:03 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/14 19:30:54 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

off_t	get_total(t_flist **list)
{
	off_t	total;

	total = 0;
	if (*list != NULL)
	{
		if ((*list)->right != NULL)
			total += get_total(&((*list)->right));
		if ((*list)->left != NULL)
			total += get_total(&((*list)->left));
		total += (*list)->file->file_info.st_blocks;
	}
	return (total);
}

int		print_link(t_file *file)
{
	char	buf[4096];

	ft_memset(buf, 0, sizeof(buf));
	if (readlink(ft_strjoin(file->path, file->filename), buf, sizeof(buf) - 1) == -1)
		return (-1);
	ft_putstr(" -> ");
	ft_putstr(buf);
	return (0);
}

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