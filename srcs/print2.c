/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/26 01:51:35 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/26 01:59:02 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	print_as_list2(t_file *file, time_t timestamp)
{
	struct group	*group;

	if ((group = getgrgid(file->file_info.st_gid)) == NULL)
		ft_putnbr(file->file_info.st_gid);
	else
		ft_putstr(group->gr_name);
	ft_putchar(' ');
	if (S_ISCHR(file->file_info.st_mode) || S_ISBLK(file->file_info.st_mode))
	{
		ft_putnbr(major(file->file_info.st_rdev));
		ft_putstr(", ");
		ft_putnbr(minor(file->file_info.st_rdev));
	}
	else
		ft_putofft(file->file_info.st_size);
	ft_putchar(' ');
	print_time(file->file_info.st_mtimespec.tv_sec, timestamp);
	ft_putchar(' ');
	ft_putstr(file->filename);
	if (S_ISLNK(file->file_info.st_mode))
		if (print_link(file) == -1)
			return (-1);
	return (0);
}

int			print_as_list(t_file *file, time_t timestamp)
{
	struct passwd	*passwd;

	print_filetype(file->file_info.st_mode);
	print_permissions(file->permissions / 100);
	print_permissions(file->permissions % 100 / 10);
	print_permissions(file->permissions % 10);
	ft_putchar(' ');
	ft_putnbr(file->file_info.st_nlink);
	ft_putchar(' ');
	if ((passwd = getpwuid(file->file_info.st_uid)) == NULL)
		ft_putnbr(file->file_info.st_uid);
	else
		ft_putstr(passwd->pw_name);
	ft_putchar(' ');
	if (print_as_list2(file, timestamp) == -1)
		return (-1);
	return (0);
}

void		print_arg(t_file *file)
{
	if (file->print_arg && !file->is_arg)
	{
		if (ft_strcmp(file->path, ".") == 0)
			ft_putstr(file->path);
		else
			write(1, file->path, ft_strlen(file->path) - 1);
		ft_putstr(":\n");
	}
}

void		print_void_arg(char *arg, t_opts options)
{
	ft_putstr(arg);
	ft_putchar(':');
	if (options.l)
		ft_putchar('\n');
}

void		print_total(blkcnt_t total, t_opts options)
{
	if (total > 0 || options.a)
	{
		ft_putstr("total ");
		ft_putlonglong(total);
		ft_putchar('\n');
	}
}
