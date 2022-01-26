#ifndef PAGERANK_H
# define PAGERANK_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_vertex vertex;

typedef struct	s_list
{
	vertex			*vertex;
	struct s_list	*next;
}				t_list;

typedef struct	s_vertex
{
	float	proba;
	size_t	len_links;
	t_list	*links;
	t_list	*prede;
}				vertex;

typedef struct	s_vertex_lst
{
	vertex	*tab;
	size_t	len;
}				vertex_lst;


void	add_elem(t_list **alst, vertex *v);

int	parse_file(char *file, vertex_lst *v_lst);

#endif
