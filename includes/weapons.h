#ifndef WEAPONS_H
# define WEAPONS_H

/*
** ====-* INCLUDES *-====
*/

/*
** ====-* DEFINES *-====
*/

# define CUT				(1)
# define DEAGLE				(1 << 1)
# define AK-47				(1 << 2)

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_weapon		t_weapon;

/*
** ====-* STRUCTURES *-====
*/

struct						s_weapon
{
	long					weapons;
};

#endif
