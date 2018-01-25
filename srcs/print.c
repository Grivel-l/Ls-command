/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 01:18:53 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/26 00:15:52 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	print_as_list(t_file *file, time_t timestamp)
{
	struct group	*group;
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

static char	*remove_path(char *filename)
{
	size_t	i;

	i = ft_strlen(filename);
	while (i > 0 && filename[i] != '/')
		i -= 1;
	return (i > 0 ? &(filename[i + 1]) : filename);
}

static int	print_files(t_flist **list, t_opts options)
{
	time_t	timestamp;

	timestamp = time(NULL);
	if ((*list)->file->eacces)
		eacces_error(remove_path(&(((*list)->file->filename)[2])));
	else if ((*list)->file->error != NULL)
		print_error((*list)->file);
	else
	{
		if (options.l)
		{
			if (print_as_list((*list)->file, timestamp) == -1)
				return (-1);
		}
		else
		{
			ft_putstr((*list)->file->filename);
			ft_putstr("  ");
		}
	}
	if (options.l)
		ft_putchar('\n');
	return (0);
}

static void	putstr_r(char *arg)
{
	write(1, arg, ft_strlen(arg) - 1);
}

static void	print_total(blkcnt_t total, t_opts options)
{
	if (total > 0 || options.a)
	{
		ft_putstr("total ");
		ft_putlonglong(total);
		ft_putchar('\n');
	}
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

void		print_void_arg(char *arg, t_opts options)
{
	ft_putstr(arg);
	ft_putchar(':');
	if (options.l)
		ft_putchar('\n');
}

int			print_flist(t_flist **list_start, t_opts options)
{
	static size_t	i = 0;

	if (i > 0 && (*list_start == NULL || (*list_start != NULL && !(*list_start)->file->is_arg)))
	{
		if (options.l)
			ft_putchar('\n');
		else
			ft_putstr("\n\n");
	}
	i += 1;
	if (*list_start != NULL)
	{
		if ((*list_start)->file->exist || (*list_start)->file->is_arg)
		{
			if ((*list_start)->file->is_arg)
			{
				if(!S_ISDIR((*list_start)->file->file_info.st_mode) && (*list_start)->file->exist)
					print_files(list_start, options);
				else
					i -= 1;
				return (0);
			}
			print_arg((*list_start)->file);
			if (options.l && !(*list_start)->file->eacces)
				print_total(get_total(list_start), options);
			if (options.r)
			{
				if (browse_reverse_flist(list_start, options, print_files) == -1)
					return (-1);
			}
			else
			{
				if (browse_flist(list_start, options, print_files) == -1)
					return (-1);
			}
		}
		else
			enoent_error((*list_start)->file->filename);
	}
	return (0);
}
