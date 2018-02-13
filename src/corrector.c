#include "corrector.h"
#include <stdio.h>


// pense a utiliser ton printf et a le mettre dans ta lib
void print_res(t_res *res)
{
  t_res *tmp;
  t_path *path;
  t_room *room;

  tmp = res;
  while(tmp)
  {
    path = tmp->path;
    printf("Resultat de  : %s\nNb_ant = %lld\n", tmp->name, tmp->ant_left);
    while(path)
    {
      room = path->room;
      while(room)
      {
        printf("%s", room->name);
        if (room->next)
          printf("-");
        room = room->next;
      }
      printf(" length = %lld : ant_lauch = %lld\n", path->length, path->nb_ant);
      path = path->next;
    }
    tmp = tmp->next;
    printf("\n\n");
  }
}

void add_res(t_res *new_result, t_res **res)
{
  t_res *tmp;

  if (*res)
  {
    tmp = *res;
    while(tmp->next)
      tmp = tmp->next;
    tmp->next = new_result;
  }
  else
    *res = new_result;
}

int main(int argc, char **argv)
{
	t_res *res;

	if (argc < 2)
		write(1, "Usage : ./corrector [outpout_lem-in]\n", 37);
  else
  {
    while(--argc > 0)
  		add_res(read_file(argv[argc], 0, 0, NULL), &res);
  	print_res(res);
  }
	return(0);
}
