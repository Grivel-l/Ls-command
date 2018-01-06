/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 01:18:53 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/27 00:41:32 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	enoent_error(void)
{
	ft_putstr_fd("The file doesn't exist\n", 2);
}

static void print_filetype(mode_t st_mode)
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

static void print_permissions(size_t permissions)
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

static void	print_time(char *time)
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

static void	print_as_list(t_file *file)
{
	print_filetype(file->file_info.st_mode);
	print_permissions(file->permissions / 100);
	print_permissions(file->permissions % 100 / 10);
	print_permissions(file->permissions % 10);
	ft_putchar(' ');
	ft_putnbr(file->file_info.st_nlink);
	ft_putchar(' ');
	ft_putstr(getpwuid(file->file_info.st_uid)->pw_name);
	ft_putchar(' ');
	ft_putstr(getgrgid(file->file_info.st_gid)->gr_name);
	ft_putchar(' ');
	ft_putnbr(file->file_info.st_size);
	ft_putchar(' ');
	print_time(ctime(&(file->file_info.st_mtim.tv_sec)));
	ft_putchar(' ');
	ft_putstr(file->filename);
}

static int	print_files(t_flist **list, char *options)
{
	if ((*list)->file->is_arg && !(*list)->file->exist)
		enoent_error();
	else
	{
		if (ft_strchr(options, 'l') != NULL)
		{
			print_as_list((*list)->file);
			ft_putchar('\n');
		}
		else
		{
			ft_putstr((*list)->file->filename);
			ft_putchar('\n');
		}
	}
	return (0);
}

void		print_flist(t_flist **list_start, char *options)
{
	if (*list_start != NULL)
	{
		ft_putstr((*list_start)->file->path);
		ft_putchar('\n');
	}
	if (ft_strchr(options, 'r') != NULL)
		browse_reverse_flist(list_start, options, print_files);
	else
		browse_flist(list_start, options, print_files);
}
