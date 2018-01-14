/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 01:18:53 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/14 20:30:57 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	print_as_list(t_file *file)
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
	// print_time(ctime(&(file->file_info.st_mtim.tv_sec)));
	print_time(ctime(&(file->file_info.st_mtimespec.tv_sec)));
	ft_putchar(' ');
	ft_putstr(file->filename);
	if (S_ISLNK(file->file_info.st_mode))
		if (print_link(file) == -1)
			return (-1);
	return (0);
}

static int	print_files(t_flist **list, char *options)
{
	if (!(*list)->file->exist)
		enoent_error((*list)->file->filename);
	else
	{
		if (ft_strchr(options, 'l') != NULL)
		{
			if (print_as_list((*list)->file) == -1)
				return (-1);
			ft_putchar('\n');
		}
		else
		{
			ft_putstr((*list)->file->filename);
			ft_putstr("  ");
		}
	}
	return (0);
}

static void	putstr_r(char *arg)
{
	write(1, arg, ft_strlen(arg) - 1);
}

void		print_arg(t_file *file)
{
	if (file->print_arg && !file->is_arg)
	{
		if (ft_strcmp(file->path, ".") == 0)
			ft_putstr(file->path);
		else
			putstr_r(file->path);
		ft_putstr(":\n");
	}
}

void		print_void_arg(char *arg, char *options)
{
	ft_putstr(arg);
	ft_putchar(':');
	if (ft_strchr(options, 'l') != NULL)
		ft_putchar('\n');
}

void		print_total(off_t total)
{
	if (total > 0)
	{
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putchar('\n');
	}
}

void		print_flist(t_flist **list_start, char *options)
{
	static size_t	i = 0;

	if (i > 0)
	{
		if (ft_strchr(options, 'l') != NULL)
			ft_putchar('\n');
		else
			ft_putstr("\n\n");
	}
		i += 1;
	if (*list_start != NULL)
	{
		if (ft_strchr(options, 'R') != NULL)
			print_arg((*list_start)->file);
		if (ft_strchr(options, 'l') != NULL)
			print_total(get_total(list_start));
		if (ft_strchr(options, 'r') != NULL)
			browse_reverse_flist(list_start, options, print_files);
		else
			browse_flist(list_start, options, print_files);
	}
}

void		print_file(t_file *file)
{
	ft_putstr(file->filename);
}
