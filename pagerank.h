#ifndef PAGERANK_H
# define PAGERANK_H

# include <stdlib.h>
# include <stdio.h>

typedef struct	s_list
{
	vertex		*vertex;
	struct list	*next;
}				t_list;

typedef struct	s_vertex
{
	float	proba;
	t_list	*links;
	t_list	*prede;
}				vertex;

typedef struct	s_vertex_lst
{
	vertex	*tab;
	size_t	len;
}				vertex_lst;

#endif
