#include "doom.h"
#include "libft.h"
#include "inputs.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
** add write_input_file to the makefile
->> open file
->> re-write all the lines in order
->> close file
-------->>> CHECK LEAKS
int		write_input_file(t_doom *data, char *file)
{
	return (0);
}
*/
