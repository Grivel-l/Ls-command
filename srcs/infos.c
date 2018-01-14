#include "ft_ls.h"

static void	fill_others_permissions(t_file *file)
{
	if ((file->file_info.st_mode & S_IROTH) != 0)
		file->permissions += 4;
	if ((file->file_info.st_mode & S_IWOTH) != 0)
		file->permissions += 2;
	if ((file->file_info.st_mode & S_IXOTH) != 0)
		file->permissions += 1;
}

static void	fill_group_permissions(t_file *file)
{
	if ((file->file_info.st_mode & S_IRGRP) != 0)
		file->permissions += 40;
	if ((file->file_info.st_mode & S_IWGRP) != 0)
		file->permissions += 20;
	if ((file->file_info.st_mode & S_IXGRP) != 0)
		file->permissions += 10;
}

static void	fill_user_permissions(t_file *file)
{
	if ((file->file_info.st_mode & S_IRUSR) != 0)
		file->permissions += 400;
	if ((file->file_info.st_mode & S_IWUSR) != 0)
		file->permissions += 200;
	if ((file->file_info.st_mode & S_IXUSR) != 0)
		file->permissions += 100;
}

static void	fill_permissions(t_file *file)
{
	fill_user_permissions(file);
	fill_group_permissions(file);
	fill_others_permissions(file);
}

int		fill_infos(t_file *file, char *path, t_opts options)
{
	if (lstat(path, &(file->file_info)) == -1)
	{
		if (errno == ENOENT)
			file->exist = 0;
		else
			return (-1);
	}
	else
		file->exist = 1;
	if (options.l)
		fill_permissions(file);
	return (0);
}
