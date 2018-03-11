#include "corrector.h"

void add_room_to_path(t_path *act_path,char *room)
{
  t_room *tmp;

  tmp = act_path->room;
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = ft_memalloc_exit(sizeof(t_room));
  tmp->next->name = room;
  act_path->length++;
}

void act_path(t_res *res, char *line, long long cmp)
{
	t_path *act_path;
	unsigned long long ant;
  char **path;
	char *room;

	path = ft_strsplit(line, ' ');
	while(path[++cmp])
	{
		ant = ft_atoi(path[cmp] + 1);
		room = ft_strdup(path[cmp] + (ft_strchr(path[cmp], '-') - path[cmp]) + 1);
		act_path = res->path;
		while(act_path && ft_strcmp(room, act_path->room->name) && ant != act_path->o_ant)
			act_path = act_path->next;
    if (act_path && !ft_strcmp(room, act_path->room->name))
      act_path->nb_ant++;
    if (act_path && ant == act_path->o_ant)
      add_room_to_path(act_path, room);
    else
      free(room);
    free(path[cmp]);
	}
  free(path);
}

t_path *init_path(char *line, long long cmp, t_path *res, t_path *act_path)
{
	char **path;

	path = ft_strsplit(line, ' ');
	while(path[++cmp])
	{
		if (!act_path)
    {
      act_path = ft_memalloc_exit(sizeof(t_path));
      res = act_path;
    }
		else
    {
      act_path->next = ft_memalloc_exit(sizeof(t_path));
			act_path = act_path->next;
    }
		act_path->room = ft_memalloc_exit(sizeof(t_room));
    act_path->o_ant = ft_atoi(path[cmp] + 1);
		act_path->room->name =
    ft_strdup(path[cmp] + (ft_strchr(path[cmp], '-') - path[cmp]) + 1);
    act_path->length = 1;
    act_path->nb_ant = 1;
    free(path[cmp]);
	}
  free(path);
	return(res);
}

t_res *read_file(char *file, int error, int state, t_res *res)
{
	char *line;
	int fd;

	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd > 0 && (res = ft_memalloc_exit(sizeof(t_res))))
		while (get_next_line(fd, &line) > 0 && !error)
		{
      if (state == 0 && ft_isalnum(*line) && (state = 1))
        res->ant_left = ft_atoi(line);
      if (state == 3 && ++res->Nb_tour)
			   act_path(res, line, -1);
      if (state == 2 && (state = 3) && ++res->Nb_tour)
				res->path = init_path(line, -1, NULL, NULL);
			state = (!line[0] && state == 1) ? 2 : state;
			ft_memdel((void **)&line);
		}
	if (error)
		ft_memdel((void **)&res);
  else
    res->name = ft_strdup(file);
	if (fd <= 0 || error)
		printf("Bad file : %s\n", file);
	return(res);
}
