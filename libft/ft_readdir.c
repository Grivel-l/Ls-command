/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_readdir.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/11 19:30:27 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/11 19:32:19 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	**read_dir(char *filename)
{
	DIR				*dir;
	char			**all_dirs;
	struct dirent	*dir_content;

	if ((all_dirs = malloc(sizeof(char *) * 1)) == NULL)
		return (NULL);
	all_dirs[0] = NULL;
	if ((dir = opendir(filename)) == NULL)
		return (NULL);
	dir_content = readdir(dir);
	while ((dir_content = readdir(dir)) != NULL)
		ft_pushstr(&all_dirs, dir_content->d_name);
	if (closedir(dir) == -1)
		return (NULL);
	return (all_dirs);
}
