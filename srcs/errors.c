#include "ft_ls.h"

void	check_errno(char *path)
{
	ft_putstr_fd(BINARY, 2);
	ft_putstr_fd(": ", 2);
	if (errno == EACCES)
	{
		ft_putstr_fd("cannot open directory '", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("': Permission denied\n", 2);
	}
}
