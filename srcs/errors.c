#include "ft_ls.h"

static void	print_prefix(void)
{
	ft_putstr_fd(BINARY, 2);
	ft_putstr_fd(": ", 2);
}

void		check_errno(char *path)
{
	print_prefix();
	if (errno == EACCES)
	{
		ft_putstr_fd("cannot open directory '", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("': Permission denied\n", 2);
	}
}

void		enoent_error(char *filename)
{
	print_prefix();
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
}
