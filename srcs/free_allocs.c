#include "ft_ls.h"

void	free_dir_files(char *filename, char **dir_files, char *path)
{
	size_t	i;

	i = 0;
	while (dir_files[i])
	{
		ft_strdel(&(dir_files[i]));
		i += 1;
	}
	ft_strdel(&filename);
	ft_strdel(&path);
	free(dir_files);
}

