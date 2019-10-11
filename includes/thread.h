#ifndef THREAD_H
# define THREAD_H

/*
** ====-* INCLUDES *-====
*/

# include <phtread.h>

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
	int						id;
	t_doom					*data;
};

#endif
