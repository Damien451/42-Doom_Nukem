#include "doom.h"
#include "libft.h"
#include "inputs.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static int	give_title_to_input(t_input *inputs)
{
	int		i;

	i = -1;
	while (++i < NB_INPUTS - 1)
		inputs[i].set_title = ft_strjoin(inputs[i].key_name, " : ");
	return (0);
}

static int	get_input(t_input input, char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i + 1] != '"')
		++i;
	if (!(input.key_name = malloc(sizeof(char) * i + 1)))
		return (1);
	ft_memcpy(input.key_name, line + 1, i);
	input.key_name[i] = '\0';
	if ((ft_strcmp(input.key_name, "Mouse Left") != 0)
		&& (ft_strcmp(input.key_name, "Mouse Middle") != 0)
		&& (ft_strcmp(input.key_name, "Mouse Right") != 0))
		input.scancode
			= SDL_GetScancodeFromName(input.key_name);
	else
		input.scancode = 0;
	return (0);
}

static int	parse_input_dict2(t_doom *data, int fd)
{
	int		nbinput;
	int		rd;
	char	*line;

	nbinput = 0;
	while ((rd = get_next_line(fd, &line)) > 0)
	{
		if (line[0] == '#')
			data->tabinputs.comment = line;
		else
		{
			if (get_input(data->tabinputs.inputs[nbinput], line) == 1)
				return (1);
			++nbinput;
		}
	}
	return (rd);
}

int			parse_input_dict(t_doom *data, char *input_dict)
{
	int		fd;
	
	if ((fd = open(input_dict, O_RDONLY)) == -1)
		return (1);
	if ((parse_input_dict2(data, fd)) != 0)
		return (1);
	close(fd);
	if ((give_title_to_input(data->tabinputs.inputs)) != 0)
		return (1);
	return (0);
}
