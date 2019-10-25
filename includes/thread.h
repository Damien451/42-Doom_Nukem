#ifndef THREAD_H
# define THREAD_H

/*
** ====-* INCLUDES *-====
*/

# include <pthread.h>

# define NBR_THREAD			8

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_thread		t_thread;

typedef struct s_doom		t_doom;

/*
** ====-* STRUCTURES *-====
*/

struct						s_thread
{
	pthread_t				thread;
	int						num;
	unsigned int			*image;
	int						total_frame;
	int						frame;
	t_doom					*data;
};

#endif
