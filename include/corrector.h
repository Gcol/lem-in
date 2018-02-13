
#ifndef CORRECTOR_H
# define CORRECTOR_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_room
{
  char *name;
  struct s_room *next;
} t_room;

typedef struct s_path
{
  t_room *room;
  unsigned long long o_ant;
  unsigned long long length;
  unsigned long long nb_ant;
  struct s_path *next;
} t_path;

typedef struct s_res
{
  char *name;
  unsigned long long ant_left;
  t_path *path;
  struct s_res *next;
} t_res;

t_res *read_file(char *file, int error, int state, t_res *res);

#endif

/*
Quantifié dispo des gens ( quantification du temps)
Capacite talent ()
Roadmap (grand module par etape( objectif d'implemantation(phase de test a chaque fois)))
Fixe les grand modules (diviser les modules en semaine/ quantifié en heure)
Division le travail ()
*/
