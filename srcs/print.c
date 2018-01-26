/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/24 01:18:53 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/26 01:57:12 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

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
	{
		if (!options.l)
			ft_putchar_fd('\n', 2);
		print_error((*list)->file);
	}
	else
	{
		if (options.l)
			if (print_as_list((*list)->file, timestamp) == -1)
				return (-1);
		if (!options.l)
		{
			ft_putstr((*list)->file->filename);
			ft_putstr("  ");
		}
	}
	if (options.l)
		ft_putchar('\n');
	return (0);
}

static void	print_newlines(t_flist *list, t_opts options, size_t *i)
{
	if (*i > 0 && (list == NULL || (list != NULL && !list->file->is_arg)))
	{
		if (options.l)
			ft_putchar('\n');
		else
			ft_putstr("\n\n");
	}
	*i += 1;
}

static int	preprint_file(t_flist **list_start, t_opts options)
{
	if (options.l && !(*list_start)->file->eacces)
		print_total(get_total(list_start), options);
	if (options.r)
	{
		if (browse_reverse_flist(list_start,
					options, print_files) == -1)
			return (-1);
	}
	else
	{
		if (browse_flist(list_start, options, print_files) == -1)
			return (-1);
	}
	return (0);
}

int			print_flist(t_flist **list_start, t_opts options)
{
	static size_t	i = 0;

	print_newlines(*list_start, options, &i);
	if (*list_start != NULL)
	{
		if ((*list_start)->file->exist || (*list_start)->file->is_arg)
		{
			if ((*list_start)->file->is_arg)
			{
				if (!S_ISDIR((*list_start)->file->file_info.st_mode) &&
						(*list_start)->file->exist)
					print_files(list_start, options);
				else
					i -= 1;
				return (0);
			}
			print_arg((*list_start)->file);
			if (preprint_file(list_start, options) == -1)
				return (-1);
		}
		else
			enoent_error((*list_start)->file->filename);
	}
	return (0);
}
