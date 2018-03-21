/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 06:03:03 by gcollett          #+#    #+#             */
/*   Updated: 2017/03/31 11:09:56 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_memory		*free_factory(t_memory *save)
{
	t_memory	*tmp;

	tmp = NULL;
	if (save->prev)
		(save->prev)->next = save->next;
	if (save->prev)
		tmp = (save->prev);
	else if (save->next)
		tmp = save->next;
	ft_memdel((void **)&save->buf);
	ft_memdel((void **)&save);
	return (tmp);
}

t_memory		*load_save(t_memory *save, int fd, char **line, int *cmp_line)
{
	t_memory *recup;

	recup = save;
	if (save)
	{
		while (save->next && save->fd != fd)
			save = save->next;
		while (save->prev && save->fd != fd)
			save = save->prev;
		if (save->fd != fd)
			while(++(*cmp_line) < save->taille_buf)
				*line[*cmp_line] = save->buf[*cmp_line];
	}
	if (!save || save->fd != fd)
	{
		save = ft_memalloc_exit(sizeof(t_memory));
		save->fd = fd;
		save->next = recup;
		save->buf = ft_memalloc_exit(BUFF_SIZE + 1);
	}
	return (save);
}

char *ft_realloc_line(char *data, int add_size, int old_size)
{
	char *res;
	int cmp;

	cmp = -1;
	res = ft_memalloc_exit(add_size + old_size + 1);
	while (++cmp < old_size)
		res[cmp] = data[cmp];
	ft_memdel((void **)&data);
	return (res);
}

void load_buff(t_memory *save, int nb_read, int cmp_buf)
{
	int i;

	i = 0;
	while (i + cmp_buf < nb_read)
	{
		save->buf[i] = save->buf[i + cmp_buf];
		i++;
	}
	while(i < nb_read)
	{
		save->buf[i] = '\0';
		i++;
	}
}


int get_next_line(const int fd, char **line)
{
	static t_memory	*save = NULL;
	int							nb_read;
	int						cmp_line;
	int						cmp_buf;

	cmp_line = -1;
	cmp_buf = 0;
	if (fd < 0 || BUFF_SIZE < 1 || !line)
		return (-1);
	save = load_save(save, fd, line, &cmp_line);
	while (save->buf[cmp_buf] != '\n' && (nb_read = read(fd, save->buf, BUFF_SIZE)) > 0)
	{
		cmp_buf = -1;
		*line = ft_realloc_line(*line, nb_read, cmp_line);
		save->taille_buf = nb_read;
		while (++cmp_buf < nb_read && save->buf[cmp_buf] != '\n')
		{
			printf("cmp_buf = %d\n",cmp_buf);
			*line[++cmp_line] = save->buf[cmp_buf];

				printf("cmp_buf = %d\n",cmp_buf);
		}
	}
	printf("nb_read = %d\n",nb_read);
	load_buff(save, nb_read, cmp_buf);
	if (nb_read < 0 && !save->taille_buf)
		free_factory(save);
	nb_read = (nb_read > 0) ? 1 : 0;
	return (nb_read);
}
